#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include "stm32f10x.h"
#include <cstdint>
#include "Interrupt.h"
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

        // 添加发送缓冲区和状态标志
        char txBuffer[256];       // 延迟发送缓冲区
        bool hasPendingTx;        // 是否有待发送数据
        uint16_t txLength;        // 缓冲区中的数据长度

    public:
        // void (*callback)(Bluetooth *self) = nullptr;
        System::Interrupt::RunAble callback{nullptr, this};
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

        // 添加前缀匹配方法
        bool startsWith(const char* prefix) const;
        bool startsWith_case(const char* prefix) const;
        
        // 从缓冲区解析格式化输入
        int scanArgs(const char* format, ...);
        
        // 获取去除前缀后的参数部分
        char* getArgs(const char* prefix);

        // 从命令名后解析参数
        int scanCommandArgs(const char* cmdName, const char* format, ...);

        // 延迟打印方法 - 安全地在中断中调用
        void printf_late(const char *fmt, ...);
    
        // 先发送缓冲区内容，再发送当前字符串
        void printf_before(const char *fmt, ...);
    
        // 发送待发送的内容(在主循环中调用)
        bool sendPending();
    
        // 获取是否有待发送内容
        bool hasPending() const { return hasPendingTx; }
    };
} // namespace Device

#endif // _BLUETOOTH_H_
