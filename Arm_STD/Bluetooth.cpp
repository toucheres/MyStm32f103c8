#include "MyStm32.h"
#include "stm32f10x_usart.h"
#include <stdarg.h>
#include <string.h>

namespace Device
{

    // 构造函数初始化成员变量
    Bluetooth::Bluetooth(USART_TypeDef *_usart, uint32_t _baudRate = 9600)
        : USARTx(_usart), baudRate(_baudRate), rxIndex(0), hasNewData(false)
    {
        // 清空接收缓冲区
        for (uint16_t i = 0; i < sizeof(rxBuffer); i++)
        {
            rxBuffer[i] = 0;
        }
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
                    callback(this);
                    hasNewData = false;
                    this->clear();
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
        rxIndex = 0;
        rxBuffer[0] = 0;
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

    // USART中断处理函数应该在外部定义，例如在main.cpp中
    // 对于USART1中断处理程序如下：/*
    // extern "C" void USART1_IRQHandler(void) {
    //     if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
    //         // 清除中断标志
    //         USART_ClearITPendingBit(USART1, USART_IT_RXNE);

    //         // 获取接收到的数据
    //         uint8_t data = USART_ReceiveData(USART1);

    //         // 需要一个全局的Bluetooth对象来存储数据
    //         // 例如：globalBluetoothObject->rxBuffer[globalBluetoothObject->rxIndex++] = data;
    //     }
    // }

} // namespace Device
