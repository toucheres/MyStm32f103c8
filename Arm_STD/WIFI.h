#ifndef _WIFI_H_
#define _WIFI_H_

#include "stm32f10x.h"
#include <cstdint>
#include <cstring>
#include <cstdarg>
#include "Interrupt.h"

namespace Device
{
    class WIFI
    {
    private:
        USART_TypeDef *USARTx;
        uint32_t baudRate;
        uint16_t rxIndex;
        
        // 帮助函数，处理接收到的字符
        void processReceivedChar(uint8_t data);

    public:
        // 连接状态枚举
        enum class Status
        {
            DISCONNECTED,  // 断开连接
            CONNECTED,     // 已连接
            GOT_IP,        // 已获取IP
            ERROR          // 错误状态
        };
        
        Status status;     // 当前状态
        
        System::Interrupt::RunAble callback{nullptr, this};
        
        // 构造函数
        WIFI(USART_TypeDef *_usart, uint32_t _baudRate);
        
        // 初始化函数
        bool init();
        
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
        
        // 获取当前缓冲区内数据的数量
        uint16_t getNum() const;
        
        // 清空缓冲区
        void clear();
        
        // 中断处理函数
        void handleInterrupt();
        void setInterrupt();
        
        // 接收缓冲区，增大到1024字节以适应WiFi通信
        char rxBuffer[1024];
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
        
        // WiFi特有功能
        bool connect(const char* ssid, const char* password, uint32_t timeout = 10000);
        bool disconnect();
        bool getIP(char* ipBuffer, uint16_t bufferSize);
        Status getStatus() const { return status; }
        bool connectTCP(const char* host, uint16_t port, uint32_t timeout = 5000);
        bool closeTCP();
        

        // 执行AT命令并等待响应
        bool executeCommand(const char* command, const char* expectedResponse, uint32_t timeout);
        bool executeCommand_(const char* command, const char* expectedResponse, uint32_t timeout);

    private:
        // 在缓冲区中查找指定字符串
        bool findInBuffer(const char* str);
    };
} // namespace Device

#endif // _WIFI_H_