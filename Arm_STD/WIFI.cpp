#include "WIFI.h"
#include "System.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include <cstdio>
#include <stdarg.h>
#include <string.h>
#include "Interrupt.h"

namespace Device
{
    // 构造函数初始化成员变量
    WIFI::WIFI(USART_TypeDef *_usart, uint32_t _baudRate)
        : USARTx(_usart), baudRate(_baudRate), rxIndex(0), 
          status(Status::DISCONNECTED), hasNewData(false)
    {
        // 清空接收缓冲区
        memset(rxBuffer, 0, sizeof(rxBuffer));
    }

    // 初始化WiFi模块的USART接口
    bool WIFI::init()
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
        
        // 设置中断处理
        this->setInterrupt();
        
        // 初始化WiFi模块
        clear();
        System::delay(1000_ms); // 等待模块启动
        sendString("AT\r\n");
        System::delay(2_s);

        return true;
    }

    // 发送单个字节
    void WIFI::sendByte(uint8_t byte)
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
    void WIFI::sendData(uint8_t *data, uint16_t len)
    {
        for (uint16_t i = 0; i < len; i++)
        {
            sendByte(data[i]);
        }
    }

    // 发送字符串
    void WIFI::sendString(const char *str)
    {
        while (*str)
        {
            sendByte(*str++);
        }
    }

    // 检查是否有数据可读
    bool WIFI::isDataAvailable()
    {
        return (rxIndex > 0);
    }

    // 接收单个字节
    uint8_t WIFI::receiveByte()
    {
        // 等待接收数据
        while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
            ;

        // 返回接收到的数据
        return USART_ReceiveData(USARTx);
    }

    // 处理接收到的字符的辅助函数
    void WIFI::processReceivedChar(uint8_t data)
    {
        // 对于WiFi模块，我们累积所有数据
        if (rxIndex < sizeof(rxBuffer) - 1) // 留出一个字节给字符串结束符
        {
            // 存储收到的字符
            rxBuffer[rxIndex++] = data;
            rxBuffer[rxIndex] = 0; // 始终确保字符串以0结尾
            hasNewData = true;
        }
    }

    // 接收数据块
    void WIFI::receiveData(uint8_t *buffer, uint16_t len)
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

    bool WIFI::equal(const char *const in) { return strcmp(this->getBuffer(), in) == 0; }
    
    bool WIFI::equal_case(const char *const in) 
    { 
        const char* buffer = this->getBuffer();
        
        for (size_t i = 0; in[i] != '\0'; i++)
        {
            char c1 = buffer[i];
            char c2 = in[i];
            
            // 转为小写比较
            if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
            if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
            
            if (c1 != c2 || buffer[i] == '\0')
                return false;
        }
        
        return true;
    }

    char *WIFI::getLastData()
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

    uint16_t WIFI::getNum() const
    {
        return this->rxIndex;
    }

    // 中断处理函数实现
    void WIFI::handleInterrupt()
    {
        if (USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
        {
            // 清除中断标志
            USART_ClearITPendingBit(USARTx, USART_IT_RXNE);

            // 接收数据
            uint8_t data = USART_ReceiveData(USARTx);

            // 处理接收到的数据
            processReceivedChar(data);
            
            // 如果有回调且数据已更新，触发回调
            if (callback)
            {
                callback();
            }
        }
    }

    void WIFI::setInterrupt()
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
            interruptType, [](void *self) { ((WIFI *)self)->handleInterrupt(); }, this);
    }

    // 获取缓冲区内容
    const char *WIFI::getBuffer() const
    {
        return rxBuffer;
    }

    // 获取缓冲区当前长度
    uint16_t WIFI::getBufferLength() const
    {
        return rxIndex;
    }

    // 清空缓冲区
    void WIFI::clear()
    {
        rxIndex = 0;
        rxBuffer[0] = 0;
        hasNewData = false;
    }

    // 实现格式化输出方法
    void WIFI::printf(const char *fmt, ...)
    {
        char buffer[128]; // 定义一个较大的缓冲区用于格式化
        va_list args;

        va_start(args, fmt);
        vsnprintf(buffer, sizeof(buffer), fmt, args);
        va_end(args);

        // 发送格式化后的字符串
        sendString(buffer);
    }

    // 检查接收缓冲区是否以指定前缀开头（区分大小写）
    bool WIFI::startsWith(const char* prefix) const
    {
        size_t prefixLen = strlen(prefix);
        if (prefixLen > rxIndex)
            return false;
            
        return (strncmp(rxBuffer, prefix, prefixLen) == 0);
    }

    // 检查接收缓冲区是否以指定前缀开头（不区分大小写）
    bool WIFI::startsWith_case(const char* prefix) const
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

    // 从缓冲区解析格式化输入
    int WIFI::scanArgs(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        int result = vsscanf(rxBuffer, format, args);
        va_end(args);
        return result;
    }

    // 获取去除前缀后的参数部分
    char* WIFI::getArgs(const char* prefix)
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

    // 从命令名后解析参数
    int WIFI::scanCommandArgs(const char* cmdName, const char* format, ...)
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
    
    // WiFi特有功能
    
    // 连接到WiFi网络
    bool WIFI::connect(const char* ssid, const char* password, uint32_t timeout)
    {
        char cmd[128];
        snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
        
        if (!executeCommand(cmd, "OK", timeout))
        {
            status = Status::ERROR;
            return false;
        }
        
        status = Status::CONNECTED;
        
        // 获取IP地址确认连接成功
        if (!executeCommand("AT+CIFSR\r\n", "OK", 1000))
        {
            status = Status::ERROR;
            return false;
        }
        
        status = Status::GOT_IP;
        return true;
    }
    
    // 断开WiFi连接
    bool WIFI::disconnect()
    {
        if (!executeCommand("AT+CWQAP\r\n", "OK", 1000))
        {
            return false;
        }
        
        status = Status::DISCONNECTED;
        return true;
    }
    
    // 获取当前IP地址
    bool WIFI::getIP(char* ipBuffer, uint16_t bufferSize)
    {
        if (status != Status::GOT_IP)
        {
            return false;
        }
        
        clear();
        sendString("AT+CIFSR\r\n");
        System::delay(500_ms);
        
        // 解析IP地址
        char* ipStart = strstr(rxBuffer, "STAIP,\"");
        if (ipStart != NULL)
        {
            ipStart += 7; // 跳过 "STAIP,"
            char* ipEnd = strchr(ipStart, '\"');
            if (ipEnd != NULL)
            {
                uint16_t ipLen = ipEnd - ipStart;
                if (ipLen < bufferSize)
                {
                    strncpy(ipBuffer, ipStart, ipLen);
                    ipBuffer[ipLen] = '\0';
                    return true;
                }
            }
        }
        
        return false;
    }
    
    // 建立TCP连接
    bool WIFI::connectTCP(const char* host, uint16_t port, uint32_t timeout)
    {
        char cmd[128];
        snprintf(cmd, sizeof(cmd), "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", host, port);
        
        return executeCommand(cmd, "OK", timeout);
    }
    
    // 关闭TCP连接
    bool WIFI::closeTCP()
    {
        return executeCommand("AT+CIPCLOSE\r\n", "OK", 1000);
    }

    // 执行AT命令并等待响应
    bool WIFI::executeCommand(const char* command, const char* expectedResponse, uint32_t timeout)
    {
        clear();
        sendString(command);
        
        uint32_t startTime = System::millisecond();
        while ((System::millisecond() - startTime) < timeout)
        {
            if (findInBuffer(expectedResponse))
                return true;
            
            System::delay(10_ms);
        }
        
        return false;
    }
    
    // 在缓冲区中查找指定字符串
    bool WIFI::findInBuffer(const char* str)
    {
        if (str == nullptr || rxBuffer[0] == '\0')
            return false;
        
        return (strstr(rxBuffer, str) != nullptr);
    }
} // namespace Device
