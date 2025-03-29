#ifndef _WIFI_H_
#define _WIFI_H_
#include "stm32f10x.h"
#include <cstdint>
#include "Interrupt.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace Device
{
    class WIFI
    {
    public:
        // 命令执行超时时间(毫秒)
        static constexpr uint32_t DEFAULT_TIMEOUT = 5000;
        // 接收缓冲区大小
        static constexpr uint16_t RX_BUFFER_SIZE = 1024;
        
        // WiFi模式枚举
        enum class Mode
        {
            STATION,     // 客户端模式
            AP,          // 接入点模式
            BOTH         // 两种模式同时启用
        };
        
        // 连接状态枚举
        enum class Status
        {
            DISCONNECTED,  // 断开连接
            CONNECTED,     // 已连接
            GOT_IP,        // 已获取IP
            ERROR          // 错误状态
        };
        
        // 构造函数(指定使用的USART接口和波特率)
        WIFI(USART_TypeDef* usart = USART2, uint32_t baudRate = 115200);
        
        // 初始化WiFi模块
        bool init();
        
        // 设置WiFi模式(客户端/AP/两者)
        bool setMode(Mode mode);
        
        // 连接到WiFi网络
        bool connect(const char* ssid, const char* password, uint32_t timeout = DEFAULT_TIMEOUT);
        
        // 断开WiFi连接
        bool disconnect();
        
        // 获取当前IP地址
        bool getIP(char* ipBuffer, uint16_t bufferSize);
        
        // 建立TCP连接
        bool connectTCP(const char* host, uint16_t port, uint32_t timeout = DEFAULT_TIMEOUT);
        
        // 关闭TCP连接
        bool closeTCP();
        
        // 发送数据
        bool send(const char* data, uint16_t len);
        
        // 发送字符串
        bool sendString(const char* str);
        
        // 格式化发送(类似printf)
        bool printf(const char* format, ...);
        
        // 检查是否有数据可读
        bool available();
        
        // 读取数据到缓冲区
        uint16_t read(char* buffer, uint16_t len);
        
        // 清空接收缓冲区
        void clear();
        
        // 设置接收回调函数
        void setCallback(void (*function)(void*), void* arg = nullptr);
        
        // 获取缓冲区数据
        const char* getBuffer() const { return rxBuffer; }
        
        // 比较接收到的数据(不区分大小写)
        bool equal_case(const char* str);
        
        // 比较接收到的数据(区分大小写)
        bool equal(const char* str);
        
        // 获取当前状态
        Status getStatus() const { return status; }
        
        // 执行AT命令并等待响应
        bool executeCommand(const char* command, const char* expectedResponse, 
                           uint32_t timeout = DEFAULT_TIMEOUT);
        
        // 数据接收标志
        volatile bool hasNewData;
        
        // 回调实例
        System::Interrupt::RunAble callback;
        
    private:
        USART_TypeDef* usart;      // 使用的USART接口
        uint32_t baudRate;         // 波特率
        Status status;             // 当前状态
        Mode mode;                 // 当前模式
        
        char rxBuffer[RX_BUFFER_SIZE]; // 接收缓冲区
        volatile uint16_t rxIndex;     // 接收索引
        
        // 初始化GPIO引脚
        void initGPIO();
        
        // 初始化USART
        void initUSART();
        
        // 注册中断处理
        void registerInterruptHandler();
        
        // USART中断处理函数
        static void USARTInterruptHandler(void* arg);
        
        // 等待特定响应
        bool waitForResponse(const char* expectedResponse, uint32_t timeout);
        
        // 发送原始数据
        void sendRaw(const char* data, uint16_t len);
    };
} // namespace Device

#endif //_WIFI_H_