#include "Bluetooth.h"
#include "System.h"
#include "stm32f10x_usart.h"
#include <cstdio>
#include <stdarg.h>
#include <string.h>
#include "Interrupt.h"
// 如果平台不支持strcasecmp，添加自定义实现
// 这是一个辅助函数，提供不区分大小写的字符串比较
// #ifndef strcasecmp
// int strcasecmp(const char *s1, const char *s2)
// {
//     while (*s1 && ((*s1 | 32) == (*s2 | 32)))
//     {
//         s1++;
//         s2++;
//     }
//     return (*s1 | 32) - (*s2 | 32);
// }
// #endif

namespace Device
{

    // 构造函数初始化成员变量
    Bluetooth::Bluetooth(USART_TypeDef *_usart, uint32_t _baudRate = 9600)
        : USARTx(_usart), baudRate(_baudRate), rxIndex(0), hasNewData(false),
          hasPendingTx(false), txLength(0)
    {
        // 清空接收和发送缓冲区
        memset(rxBuffer, 0, sizeof(rxBuffer));
        memset(txBuffer, 0, sizeof(txBuffer));
    }

    // 初始化蓝牙模块的USART接口
    void Bluetooth::init()
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;
        NVIC_InitTypeDef NVIC_InitStructure;

        // 根据使用的USART确定时钟和引脚
        if (USARTx == USART1)
        {
            // 使能USART1和GPIOA时钟
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

            // 配置USART1的TX(PA9)为复用推挽输出
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOA, &GPIO_InitStructure);

            // 配置USART1的RX(PA10)为浮空输入
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if (USARTx == USART2)
        {
            // 使能USART2和GPIOA时钟
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

            // 配置USART2的TX(PA2)为复用推挽输出
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOA, &GPIO_InitStructure);

            // 配置USART2的RX(PA3)为浮空输入
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if (USARTx == USART3)
        {
            // 使能USART3和GPIOB时钟
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

            // 配置USART3的TX(PB10)为复用推挽输出
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOB, &GPIO_InitStructure);

            // 配置USART3的RX(PB11)为浮空输入
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }

        // 配置USART参数
        USART_InitStructure.USART_BaudRate = baudRate;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        USART_Init(USARTx, &USART_InitStructure);

        // 配置USART中断
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

        if (USARTx == USART1)
        {
            NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        }
        else if (USARTx == USART2)
        {
            NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
        }
        else if (USARTx == USART3)
        {
            NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
        }

        NVIC_Init(&NVIC_InitStructure);

        // 使能USART接收中断
        USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

        // 使能USART
        USART_Cmd(USARTx, ENABLE);
        this->setInterrupt();
    }

    // 发送单个字节
    void Bluetooth::sendByte(uint8_t byte)
    {
        // 等待发送数据寄存器为空
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
            ;

        // 发送数据
        USART_SendData(USARTx, byte);

        // 等待发送完成
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
            ;
    }

    // 发送数据块
    void Bluetooth::sendData(uint8_t *data, uint16_t len)
    {
        for (uint16_t i = 0; i < len; i++)
        {
            sendByte(data[i]);
        }
    }

    // 发送字符串
    void Bluetooth::sendString(const char *str)
    {
        while (*str)
        {
            sendByte(*str++);
        }
    }

    // 检查是否有数据可读
    bool Bluetooth::isDataAvailable()
    {
        return (rxIndex > 0);
    }

    // 接收单个字节
    uint8_t Bluetooth::receiveByte()
    {
        // 等待接收数据
        while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
            ;

        // 返回接收到的数据
        return USART_ReceiveData(USARTx);
    }

    // 处理接收到的字符的辅助函数
    void Device::Bluetooth::processReceivedChar(uint8_t data)
    {
        // 如果是回车或换行符
        if (data == '\r' || data == '\n')
        {
            // 只有缓冲区中有实际数据时才视为命令完成
            if (this->rxIndex > 0)
            {
                // 确保字符串以0结尾
                rxBuffer[this->rxIndex] = 0;

                // 移除末尾可能的回车换行符
                while (rxIndex > 0 && (rxBuffer[rxIndex - 1] == '\r' || rxBuffer[rxIndex - 1] == '\n'))
                {
                    rxBuffer[--rxIndex] = 0;
                }

                hasNewData = true;
                if (callback)
                {
                    callback();
                }
            }
            // 如果是空命令，直接忽略
        }
        else if (this->rxIndex < sizeof(rxBuffer) - 1) // 留出一个字节给字符串结束符
        {
            // 存储收到的字符
            rxBuffer[this->rxIndex++] = data;
            rxBuffer[this->rxIndex] = 0; // 始终确保字符串以0结尾
        }
    }

    // 接收数据块
    void Bluetooth::receiveData(uint8_t *buffer, uint16_t len)
    {
        // 如果缓冲区中有足够的数据
        if (rxIndex >= len)
        {
            // 复制数据到用户提供的缓冲区
            for (uint16_t i = 0; i < len; i++)
            {
                buffer[i] = rxBuffer[i];
            }

            // 移动剩余数据到缓冲区开始位置
            for (uint16_t i = 0; i < rxIndex - len; i++)
            {
                rxBuffer[i] = rxBuffer[i + len];
            }

            // 更新接收索引
            rxIndex -= len;

            // 确保结束符
            rxBuffer[rxIndex] = 0;
        }
        else
        {
            // 如果缓冲区中的数据不够，复制全部可用数据
            for (uint16_t i = 0; i < rxIndex; i++)
            {
                buffer[i] = rxBuffer[i];
            }

            // 将缓冲区中剩余的位置填充为0
            for (uint16_t i = rxIndex; i < len; i++)
            {
                buffer[i] = 0;
            }

            // 清空接收缓冲区
            rxIndex = 0;
            rxBuffer[0] = 0;
        }
    }

    bool Bluetooth::equal(const char *const in) { return strcmp(this->getBuffer(), in) == 0; }
    bool Bluetooth::equal_case(const char *const in) { return strcasecmp(this->getBuffer(), in) == 0; }

    char *Bluetooth::getLastData()
    {
        // 如果缓冲区为空，返回错误
        if (rxIndex == 0)
        {
            return nullptr;
        }

        // 确保字符串正确终止
        rxBuffer[rxIndex] = 0;

        // 直接返回缓冲区指针，调用方负责处理数据
        return rxBuffer;
    }

    // 进入AT命令模式
    void Bluetooth::enterATMode()
    {
        // 一般蓝牙模块需要发送"+++"并等待一段时间来进入AT命令模式
        System::delay(1000_ms); // 先暂停一段时间确保无数据传输
        sendString("+++");
        System::delay(1000_ms); // 暂停等待蓝牙模块进入AT命令模式
    }

    uint8_t Bluetooth::getNum()
    {
        return this->rxIndex;
    }
    // 退出AT命令模式
    void Bluetooth::exitATMode()
    {
        // 大多数蓝牙模块使用"AT+EXIT"命令退出AT模式
        sendString("AT+EXIT\r\n");
        System::delay(500_ms); // 等待蓝牙模块退出AT模式
    }

    // 发送AT命令并获取响应
    bool Bluetooth::sendATCommand(const char *command, char *response, uint16_t timeout)
    {
        uint32_t startTime;
        uint16_t i = 0;
        bool responseReceived = false;

        // 清空接收缓冲区
        rxIndex = 0;

        // 发送AT命令
        sendString(command);
        sendString("\r\n");

        // 获取当前时间，用于超时检测
        startTime = 0; // 这里应该使用一个计时函数，例如SysTick_GetTick()

        // 等待响应或超时
        while ((0 - startTime) < timeout)
        { // 同样，这里应该使用计时函数获取经过的时间
            if (isDataAvailable())
            {
                if (response != NULL)
                {
                    // 将数据复制到响应缓冲区
                    uint8_t byte = rxBuffer[0];
                    rxIndex = 0; // 清空接收缓冲区

                    response[i++] = byte;

                    // 检查是否接收到回车换行，表示响应结束
                    if (byte == '\n' && i > 1 && response[i - 2] == '\r')
                    {
                        response[i] = '\0'; // 添加字符串结束符
                        responseReceived = true;
                        break;
                    }
                }
            }

            // 简单延时，避免忙等待
            System::delay(1_ms);
        }

        return responseReceived;
    }

    // 中断处理函数实现
    void Device::Bluetooth::handleInterrupt()
    {
        if (USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
        {
            // 清除中断标志
            USART_ClearITPendingBit(USARTx, USART_IT_RXNE);

            // 接收数据
            uint8_t data = USART_ReceiveData(USARTx);

            // 可选：回显接收到的字符（便于调试）
            // USART_SendData(USARTx, data);

            // 处理接收到的数据
            processReceivedChar(data);
        }
    }

    void Bluetooth::setInterrupt()
    {
        uint16_t interruptType = 0;
        if (this->USARTx == USART1)
        {
            interruptType = System::Interrupt::Type::USART1_IRQHand;
        }
        else if (this->USARTx == USART2)
        {
            interruptType = System::Interrupt::Type::USART2_IRQHand;
        }
        else if (this->USARTx == USART3)
        {
            interruptType = System::Interrupt::Type::USART3_IRQHand;
        }
        System::Interrupt::registerHandler(
            interruptType, [](void *self) { ((Bluetooth *)self)->handleInterrupt(); },this);
    }

    // 获取缓冲区内容
    const char *Bluetooth::getBuffer() const
    {
        return rxBuffer;
    }

    // 获取缓冲区当前长度
    uint16_t Bluetooth::getBufferLength() const
    {
        return rxIndex;
    }

    // 获取当前数据数量
    uint16_t Bluetooth::getNum() const
    {
        return rxIndex;
    }

    // 清空缓冲区
    void Bluetooth::clear()
    {
        for (size_t i = 0; i < rxIndex; i++)
        {
            rxBuffer[i]=0;
        }
        rxIndex = 0;
        hasNewData = false;
    }

    // 实现格式化输出方法
    void Bluetooth::printf(const char *fmt, ...)
    {
        char buffer[64]; // 定义一个较大的缓冲区用于格式化
        va_list args;

        va_start(args, fmt);
        vsnprintf(buffer, sizeof(buffer), fmt, args);
        va_end(args);

        // 发送格式化后的字符串
        sendString(buffer);
    }

    // 检查接收缓冲区是否以指定前缀开头（区分大小写）
    bool Bluetooth::startsWith(const char* prefix) const
    {
        size_t prefixLen = strlen(prefix);
        if (prefixLen > rxIndex)
            return false;
            
        return (strncmp(rxBuffer, prefix, prefixLen) == 0);
    }

    // 检查接收缓冲区是否以指定前缀开头（不区分大小写）
    bool Bluetooth::startsWith_case(const char* prefix) const
    {
        size_t prefixLen = strlen(prefix);
        if (prefixLen > rxIndex)
            return false;
            
        for (size_t i = 0; i < prefixLen; i++)
        {
            char c1 = rxBuffer[i];
            char c2 = prefix[i];
            
            // 转为小写比较
            if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
            if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
            
            if (c1 != c2)
                return false;
        }
        
        return true;
    }

    // 从缓冲区解析格式化输入（类似于sscanf）
    int Bluetooth::scanArgs(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        int result = vsscanf(rxBuffer, format, args);
        va_end(args);
        return result;
    }

    // 获取去除前缀后的参数部分（用于复杂命令解析）
    char* Bluetooth::getArgs(const char* prefix)
    {
        size_t prefixLen = strlen(prefix);
        if (!startsWith_case(prefix) || rxIndex <= prefixLen)
            return nullptr;
        
        // 跳过前缀和一个可能的空格
        size_t offset = prefixLen;
        if (rxBuffer[offset] == ' ')
            offset++;
            
        return &rxBuffer[offset];
    }

    // 新增方法：从命令名后解析参数
    int Bluetooth::scanCommandArgs(const char* cmdName, const char* format, ...)
    {
        // 检查命令前缀是否匹配
        if (!startsWith_case(cmdName))
            return 0;
        
        // 创建完整格式字符串（命令名 + 格式）
        char fullFormat[128];
        snprintf(fullFormat, sizeof(fullFormat), "%s %s", cmdName, format);
        
        // 解析参数
        va_list args;
        va_start(args, format);
        int result = vsscanf(rxBuffer, fullFormat, args);
        va_end(args);
        
        // 返回实际解析的参数数量（减去命令名）
        return result > 0 ? result - 1 : 0;
    }

    // 延迟打印方法实现
    void Bluetooth::printf_late(const char *fmt, ...)
    {
        // 计算当前缓冲区已使用的长度
        int currentLength = 0;
        if (hasPendingTx) {
            currentLength = txLength;
        }
        
        // 确保缓冲区还有空间
        if (currentLength >= (int)sizeof(txBuffer) - 1) {
            // 缓冲区已满，无法追加
            return;
        }
        
        va_list args;
        va_start(args, fmt);
        // 在已有内容后追加新内容
        int appendLength = vsnprintf(txBuffer + currentLength, 
                                    sizeof(txBuffer) - currentLength - 1, 
                                    fmt, args);
        va_end(args);
        
        // 确保字符串以null结尾并更新长度
        if (appendLength >= 0 && (currentLength + appendLength) < (int)sizeof(txBuffer)) {
            txLength = currentLength + appendLength;
            txBuffer[txLength] = '\0';
        } else {
            txBuffer[sizeof(txBuffer) - 1] = '\0';
            txLength = sizeof(txBuffer) - 1;
        }
        
        hasPendingTx = true;
    }

    // 先发送缓冲区内容，再发送当前字符串
    void Bluetooth::printf_before(const char *fmt, ...)
    {
        // 先发送待发送的内容
        if (hasPendingTx) {
            sendString(txBuffer);
            hasPendingTx = false;
            txLength = 0;
        }
        
        // 再发送当前内容
        char buffer[128];
        va_list args;
        
        va_start(args, fmt);
        int length = vsnprintf(buffer, sizeof(buffer) - 1, fmt, args);
        va_end(args);
        
        // 确保字符串以null结尾
        if (length >= 0 && length < (int)sizeof(buffer)) {
            buffer[length] = '\0';
        } else {
            buffer[sizeof(buffer) - 1] = '\0';
        }
        
        sendString(buffer);
    }

    // 发送待发送的内容(在主循环中调用)
    bool Bluetooth::sendPending()
    {
        if (hasPendingTx) {
            sendString(txBuffer);
            hasPendingTx = false;
            txLength = 0;
            return true;
        }
        return false;
    }
} // namespace Device
