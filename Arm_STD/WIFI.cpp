#include "WIFI.h"
#include "System.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

namespace Device
{
    // 构造函数
    WIFI::WIFI(USART_TypeDef* usart, uint32_t baudRate)
        : usart(usart), baudRate(baudRate), status(Status::DISCONNECTED),
          mode(Mode::STATION), rxIndex(0), hasNewData(false),
          callback(nullptr, nullptr)
    {
        memset(rxBuffer, 0, RX_BUFFER_SIZE);
    }
    
    // 初始化WiFi模块
    bool WIFI::init()
    {
        // 初始化GPIO和USART
        initGPIO();
        initUSART();
        registerInterruptHandler();
        
        // 重置接收缓冲区
        clear();
        
        // 等待模块启动
        System::delay(1000_ms);
        
        // 测试AT通信
        if (!executeCommand("AT\r\n", "OK", 1000))
        {
            return false;
        }
        
        // 设置为单连接模式
        if (!executeCommand("AT+CIPMUX=0\r\n", "OK", 1000))
        {
            return false;
        }
        
        return true;
    }
    
    // 设置WiFi模式
    bool WIFI::setMode(Mode mode)
    {
        this->mode = mode;
        
        char cmd[20];
        uint8_t modeValue;
        
        switch (mode)
        {
            case Mode::STATION:
                modeValue = 1;
                break;
            case Mode::AP:
                modeValue = 2;
                break;
            case Mode::BOTH:
                modeValue = 3;
                break;
            default:
                return false;
        }
        
        sprintf(cmd, "AT+CWMODE=%d\r\n", modeValue);
        return executeCommand(cmd, "OK", 1000);
    }
    
    // 连接到WiFi网络
    bool WIFI::connect(const char* ssid, const char* password, uint32_t timeout)
    {
        char cmd[128];
        sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
        
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
        
        // 解析IP地址（简化版，实际应用需要更复杂的解析逻辑）
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
        sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", host, port);
        
        return executeCommand(cmd, "OK", timeout);
    }
    
    // 关闭TCP连接
    bool WIFI::closeTCP()
    {
        return executeCommand("AT+CIPCLOSE\r\n", "OK", 1000);
    }
    
    // 发送数据
    bool WIFI::send(const char *data, uint16_t len)
    {
        // 使用静态缓冲区避免在栈上分配内存
        static char cmd[32];
        
        // 使用snprintf代替sprintf，限制写入长度避免溢出
        snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%zu\r\n", len);
        
        // 使用sendRaw代替未声明的uart->writeString
        sendRaw(cmd, strlen(cmd));
        
        // 等待ESP8266准备好接收数据
        System::delay(100_ms);
        
        // 使用sendRaw代替未声明的uart->write
        sendRaw(data, len);
        return true;
    }
    
    // 发送字符串
    bool WIFI::sendString(const char *str)
    {
        size_t len = strlen(str);
        // 直接调用新的send方法
        return send(str, len);
    }
    
    // 格式化发送
    bool WIFI::printf(const char* format, ...)
    {
        char buffer[256];
        va_list args;
        va_start(args, format);
        int len = vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        
        if (len > 0 && len < sizeof(buffer))
        {
            return send(buffer, len);
        }
        
        return false;
    }
    
    // 检查是否有数据可读
    bool WIFI::available()
    {
        return hasNewData;
    }
    
    // 读取数据到缓冲区
    uint16_t WIFI::read(char* buffer, uint16_t len)
    {
        if (!hasNewData || rxIndex == 0)
        {
            return 0;
        }
        
        uint16_t readLen = (rxIndex < len) ? rxIndex : len;
        memcpy(buffer, rxBuffer, readLen);
        buffer[readLen] = '\0';
        
        return readLen;
    }
    
    // 清空接收缓冲区
    void WIFI::clear()
    {
        memset(rxBuffer, 0, RX_BUFFER_SIZE);
        rxIndex = 0;
        hasNewData = false;
    }
    
    // 设置接收回调函数
    void WIFI::setCallback(void (*function)(void*), void* arg)
    {
        callback.fun = function;
        callback.arg = arg;
    }
    
    // 比较接收到的数据(不区分大小写)
    bool WIFI::equal_case(const char* str)
    {
        uint16_t len = strlen(str);
        if (len > rxIndex)
        {
            return false;
        }
        
        for (uint16_t i = 0; i < len; i++)
        {
            char c1 = rxBuffer[i];
            char c2 = str[i];
            
            // 转为小写比较
            if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
            if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
            
            if (c1 != c2)
            {
                return false;
            }
        }
        
        return true;
    }
    
    // 比较接收到的数据(区分大小写)
    bool WIFI::equal(const char* str)
    {
        uint16_t len = strlen(str);
        if (len > rxIndex)
        {
            return false;
        }
        
        return (strncmp(rxBuffer, str, len) == 0);
    }
    
    // 执行AT命令并等待响应
    bool WIFI::executeCommand(const char *command, const char *expectedResponse, uint32_t timeout)
    {
        // 清空缓冲区
        clear();
        
        // 使用sendRaw代替未声明的uart->writeString
        sendRaw(command, strlen(command));
        
        // 改进的超时处理
        uint32_t maxAttempts = timeout / 10; // 根据10ms延时计算最大尝试次数
        uint32_t attempts = 0;
        
        // 使用固定次数的尝试而不是毫秒级别的计时
        while (attempts < maxAttempts)
        {
            // 处理接收数据
            if (findInBuffer(expectedResponse))
                return true;
            
            System::delay(10_ms);
            attempts++;
        }
        
        return false;
    }
    
    // 初始化GPIO引脚
    void WIFI::initGPIO()
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        
        // 根据使用的USART确定GPIO端口和引脚
        GPIO_TypeDef* GPIOx;
        uint16_t TX_Pin, RX_Pin;
        uint32_t RCC_APB2Periph_GPIOx;
        
        if (usart == USART1)
        {
            GPIOx = GPIOA;
            TX_Pin = GPIO_Pin_9;
            RX_Pin = GPIO_Pin_10;
            RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOA;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        }
        else if (usart == USART2)
        {
            GPIOx = GPIOA;
            TX_Pin = GPIO_Pin_2;
            RX_Pin = GPIO_Pin_3;
            RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOA;
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        }
        else if (usart == USART3)
        {
            GPIOx = GPIOB;
            TX_Pin = GPIO_Pin_10;
            RX_Pin = GPIO_Pin_11;
            RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOB;
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        }
        else
        {
            // 不支持的USART
            return;
        }
        
        // 使能GPIO时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx | RCC_APB2Periph_AFIO, ENABLE);
        
        // 配置TX引脚为复用推挽输出
        GPIO_InitStructure.GPIO_Pin = TX_Pin;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOx, &GPIO_InitStructure);
        
        // 配置RX引脚为浮空输入
        GPIO_InitStructure.GPIO_Pin = RX_Pin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOx, &GPIO_InitStructure);
    }
    
    // 初始化USART
    void WIFI::initUSART()
    {
        USART_InitTypeDef USART_InitStructure;
        
        // 配置USART参数
        USART_InitStructure.USART_BaudRate = baudRate;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        
        USART_Init(usart, &USART_InitStructure);
        
        // 使能接收中断
        USART_ITConfig(usart, USART_IT_RXNE, ENABLE);
        
        // 使能USART
        USART_Cmd(usart, ENABLE);
    }
    
    // 注册中断处理
    void WIFI::registerInterruptHandler()
    {
        uint16_t interruptType;
        
        // 根据使用的USART确定中断类型
        if (usart == USART1)
        {
            interruptType = System::Interrupt::USART1_IRQHand;
        }
        else if (usart == USART2)
        {
            interruptType = System::Interrupt::USART2_IRQHand;
        }
        else if (usart == USART3)
        {
            interruptType = System::Interrupt::USART3_IRQHand;
        }
        else
        {
            // 不支持的USART
            return;
        }
        
        // 注册中断处理函数
        System::Interrupt::registerHandler(
            interruptType, 
            USARTInterruptHandler,
            this
        );
    }
    
    // USART中断处理函数
    void WIFI::USARTInterruptHandler(void* arg)
    {
        WIFI* wifi = static_cast<WIFI*>(arg);
        
        if (USART_GetITStatus(wifi->usart, USART_IT_RXNE) != RESET)
        {
            // 读取接收到的数据
            uint8_t data = USART_ReceiveData(wifi->usart);
            
            // 存储到接收缓冲区
            if (wifi->rxIndex < RX_BUFFER_SIZE - 1)
            {
                wifi->rxBuffer[wifi->rxIndex++] = data;
                wifi->rxBuffer[wifi->rxIndex] = '\0';
                wifi->hasNewData = true;
            }
            
            // 如果有注册回调，则调用回调函数
            if (wifi->hasNewData && wifi->callback.fun != nullptr)
            {
                wifi->callback();
            }
        }
    }
    
    // 等待特定响应
    bool WIFI::waitForResponse(const char* expectedResponse, uint32_t timeout)
    {
        uint32_t startTime = System::millisecond();
        
        while ((System::millisecond() - startTime) < timeout)
        {
            if (strstr(rxBuffer, expectedResponse) != NULL)
            {
                return true;
            }
            System::delay(10_ms);
        }
        
        return false;
    }
    
    // 发送原始数据
    void WIFI::sendRaw(const char* data, uint16_t len)
    {
        for (uint16_t i = 0; i < len; i++)
        {
            USART_SendData(usart, data[i]);
            while (USART_GetFlagStatus(usart, USART_FLAG_TC) == RESET);
        }
    }
    
    // 在类实现中添加findInBuffer函数
    bool Device::WIFI::findInBuffer(const char* str)
    {
        if (str == nullptr || rxBuffer[0] == '\0')
            return false;
        
        return (strstr(rxBuffer, str) != nullptr);
    }
    
} // namespace Device
