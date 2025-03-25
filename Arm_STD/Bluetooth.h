#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include "stm32f10x.h"
#include <cstdint>
#include "Interrupt.hpp"
namespace Device
{
    class Bluetooth
    {
    private:
        USART_TypeDef *USARTx;
        uint32_t baudRate;
        uint16_t rxIndex;

        // 帮助函数，处理接收到的字符
        void processReceivedChar(uint8_t data);

    public:
        void (*callback)(Bluetooth *self) = nullptr;
        // 构造函数
        Bluetooth(USART_TypeDef *_usart, uint32_t _baudRate);

        // 初始化函数
        void init();

        // 发送函数
        void sendByte(uint8_t byte);
        void sendData(uint8_t *data, uint16_t len);
        void sendString(const char *str);

        bool isDataAvailable();

        uint8_t receiveByte();

        void receiveData(uint8_t *buffer, uint16_t len);
        bool equal(const char *const in);
        bool equal_case(const char *const in);
        
        // 获取最后接收的完整行数据
        char *getLastData();
        
        // 获取接收缓冲区内容
        const char *getBuffer() const;

        // 获取当前接收缓冲区长度
        uint16_t getBufferLength() const;

        void enterATMode();
        uint8_t getNum();
        void exitATMode();

        // 获取当前缓冲区内数据的数量
        uint16_t getNum() const;

        // 清空缓冲区
        void clear();

        bool sendATCommand(const char *command, char *response, uint16_t timeout);

        // 中断处理函数
        void handleInterrupt();
        void setInterrupt();

        // 接收缓冲区，增大到64字节
        char rxBuffer[64];
        bool hasNewData;

        // 添加格式化输出方法
        void printf(const char *fmt, ...);
    };
} // namespace Device

#endif // _BLUETOOTH_H_
