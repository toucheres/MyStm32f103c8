#ifndef _MYSTM32_H_
#define _MYSTM32_H_
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include <cstddef>
#include <cstdint>
extern "C"
{
#include <math.h>
#include <stdio.h>
}

// 如果平台不支持strcasecmp，添加自定义实现
// #ifndef strcasecmp
// int strcasecmp(const char *s1, const char *s2);
// #endif

#define timer2_fun extern "C" void TIM2_IRQHandler(void)
#define timer3_fun extern "C" void TIM3_IRQHandler(void)
#define timer4_fun extern "C" void TIM4_IRQHandler(void)
#define USART1_fun extern "C" void USART1_IRQHandler(void)
#define EXTI1_fun extern "C" void EXTI1_IRQHandler(void)

// Port类声明
class Port
{
public:
    inline static GPIO_TypeDef *const A = GPIOA;
    inline static GPIO_TypeDef *const B = GPIOB;
    inline static GPIO_TypeDef *const C = GPIOC;
};

// Pin类声明
class Pin
{
public:
    constexpr static const uint16_t Pin0 = GPIO_Pin_0;
    constexpr static const uint16_t Pin1 = GPIO_Pin_1;
    constexpr static const uint16_t Pin2 = GPIO_Pin_2;
    constexpr static const uint16_t Pin3 = GPIO_Pin_3;
    constexpr static const uint16_t Pin4 = GPIO_Pin_4;
    constexpr static const uint16_t Pin5 = GPIO_Pin_5;
    constexpr static const uint16_t Pin6 = GPIO_Pin_6;
    constexpr static const uint16_t Pin7 = GPIO_Pin_7;
    constexpr static const uint16_t Pin8 = GPIO_Pin_8;
    constexpr static const uint16_t Pin9 = GPIO_Pin_9;
    constexpr static const uint16_t Pin10 = GPIO_Pin_10;
    constexpr static const uint16_t Pin11 = GPIO_Pin_11;
    constexpr static const uint16_t Pin12 = GPIO_Pin_12;
    constexpr static const uint16_t Pin13 = GPIO_Pin_13;
    constexpr static const uint16_t Pin14 = GPIO_Pin_14;
    constexpr static const uint16_t Pin15 = GPIO_Pin_15;
};

// IOMode类声明
class IOMode
{
public:
    constexpr static const GPIOMode_TypeDef AIN = GPIO_Mode_AIN;
    constexpr static const GPIOMode_TypeDef IN_FLOATING = GPIO_Mode_IN_FLOATING;
    constexpr static const GPIOMode_TypeDef IPD = GPIO_Mode_IPD;
    constexpr static const GPIOMode_TypeDef IPU = GPIO_Mode_IPU;
    constexpr static const GPIOMode_TypeDef Out_OD = GPIO_Mode_Out_OD;
    constexpr static const GPIOMode_TypeDef Out_PP = GPIO_Mode_Out_PP;
    constexpr static const GPIOMode_TypeDef AF_OD = GPIO_Mode_AF_OD;
    constexpr static const GPIOMode_TypeDef AF_PP = GPIO_Mode_AF_PP;
};

// IOSpeed类声明
class IOSpeed
{
public:
    constexpr static const GPIOSpeed_TypeDef _50MHz = GPIO_Speed_50MHz;
    constexpr static const GPIOSpeed_TypeDef _2MHz = GPIO_Speed_2MHz;
    constexpr static const GPIOSpeed_TypeDef _10MHz = GPIO_Speed_10MHz;
};

// IO类声明
class IO
{
    static uint16_t used[3];

public:
    // static bool sign(const GPIO_TypeDef *_port, const uint16_t _pin);

    class InitHelper // 添加名称替代匿名类
    {
        GPIO_TypeDef *port;
        static void doInitPin(GPIO_TypeDef *port, uint16_t pin, GPIOMode_TypeDef mode);

    public:
        class Port_Init
        {
            GPIO_TypeDef *port;

        public:
            Port_Init(GPIO_TypeDef *_port) : port(_port) {}
            void Pin0(GPIOMode_TypeDef mode) const;
            void Pin1(GPIOMode_TypeDef mode) const;
            void Pin2(GPIOMode_TypeDef mode) const;
            void Pin3(GPIOMode_TypeDef mode) const;
            void Pin4(GPIOMode_TypeDef mode) const;
            void Pin5(GPIOMode_TypeDef mode) const;
            void Pin6(GPIOMode_TypeDef mode) const;
            void Pin7(GPIOMode_TypeDef mode) const;
            void Pin8(GPIOMode_TypeDef mode) const;
            void Pin9(GPIOMode_TypeDef mode) const;
            void Pin10(GPIOMode_TypeDef mode) const;
            void Pin11(GPIOMode_TypeDef mode) const;
            void Pin12(GPIOMode_TypeDef mode) const;
            void Pin13(GPIOMode_TypeDef mode) const;
            void Pin14(GPIOMode_TypeDef mode) const;
            void Pin15(GPIOMode_TypeDef mode) const;
        };

        Port_Init ProtA{Port::A};
        Port_Init ProtB{Port::B};
        Port_Init ProtC{Port::C};

    } static init;

    class WriteHelper // 添加名称替代匿名类
    {
        GPIO_TypeDef *port;
        static void doWritePin(GPIO_TypeDef *port, uint16_t pin, BitAction value);

    public:
        class Port_Write
        {
            GPIO_TypeDef *port;

        public:
            Port_Write(GPIO_TypeDef *_port) : port(_port) {}
            void Pin0(uint8_t value) const;
            void Pin1(uint8_t value) const;
            void Pin2(uint8_t value) const;
            void Pin3(uint8_t value) const;
            void Pin4(uint8_t value) const;
            void Pin5(uint8_t value) const;
            void Pin6(uint8_t value) const;
            void Pin7(uint8_t value) const;
            void Pin8(uint8_t value) const;
            void Pin9(uint8_t value) const;
            void Pin10(uint8_t value) const;
            void Pin11(uint8_t value) const;
            void Pin12(uint8_t value) const;
            void Pin13(uint8_t value) const;
            void Pin14(uint8_t value) const;
            void Pin15(uint8_t value) const;
        };

        Port_Write ProtA{Port::A};
        Port_Write ProtB{Port::B};
        Port_Write ProtC{Port::C};

    } static write;

    class ReadHelper // 添加名称替代匿名类
    {
        GPIO_TypeDef *port;
        static bool doReadPin(GPIO_TypeDef *port, uint16_t pin);

    public:
        class Port_read
        {
            GPIO_TypeDef *port;

        public:
            Port_read(GPIO_TypeDef *_port) : port(_port) {}
            void Pin0(uint8_t value) const;
            void Pin1(uint8_t value) const;
            void Pin2(uint8_t value) const;
            void Pin3(uint8_t value) const;
            void Pin4(uint8_t value) const;
            void Pin5(uint8_t value) const;
            void Pin6(uint8_t value) const;
            void Pin7(uint8_t value) const;
            void Pin8(uint8_t value) const;
            void Pin9(uint8_t value) const;
            void Pin10(uint8_t value) const;
            void Pin11(uint8_t value) const;
            void Pin12(uint8_t value) const;
            void Pin13(uint8_t value) const;
            void Pin14(uint8_t value) const;
            void Pin15(uint8_t value) const;
        };

        Port_read ProtA{Port::A};
        Port_read ProtB{Port::B};
        Port_read ProtC{Port::C};

    } static read;

    static void init_port(GPIO_TypeDef *port);
    static void init_pin(GPIO_TypeDef *port, uint16_t pin, GPIOMode_TypeDef mode);
    static uint16_t read_port(GPIO_TypeDef *port);
    static uint8_t read_pin(GPIO_TypeDef *port, uint16_t pin);
    static void Write_port(GPIO_TypeDef *port, uint16_t val);
    static void Write_pin(GPIO_TypeDef *port, uint16_t pin, bool val);
    static void Write_pin(GPIO_TypeDef *port, uint16_t pin, BitAction val);
    static void Change_pin(GPIO_TypeDef *port, uint16_t pin);
} static io;

// Clock类声明
class Clock
{
public:
    class RccProt
    {
    public:
        constexpr static const uint32_t AFIO_RCC = ((uint32_t)0x00000001);
        constexpr static const uint32_t GPIOA_RCC = ((uint32_t)0x00000004);
        constexpr static const uint32_t GPIOB_RCC = ((uint32_t)0x00000008);
        constexpr static const uint32_t GPIOC_RCC = ((uint32_t)0x00000010);
        constexpr static const uint32_t GPIOD_RCC = ((uint32_t)0x00000020);
        constexpr static const uint32_t GPIOE_RCC = ((uint32_t)0x00000040);
        constexpr static const uint32_t GPIOF_RCC = ((uint32_t)0x00000080);
        constexpr static const uint32_t GPIOG_RCC = ((uint32_t)0x00000100);
        constexpr static const uint32_t ADC1_RCC = ((uint32_t)0x00000200);
        constexpr static const uint32_t ADC2_RCC = ((uint32_t)0x00000400);
        constexpr static const uint32_t Timer_1_RCC = ((uint32_t)0x00000800);
        constexpr static const uint32_t SPI1_RCC = ((uint32_t)0x00001000);
        constexpr static const uint32_t TIM8_RCC = ((uint32_t)0x00002000);
        constexpr static const uint32_t USART_RCC = ((uint32_t)0x00004000);
        constexpr static const uint32_t ADC3_RCC = ((uint32_t)0x00008000);
        constexpr static const uint32_t Timer_15_RCC = ((uint32_t)0x00010000);
        constexpr static const uint32_t Timer_16_RCC = ((uint32_t)0x00020000);
        constexpr static const uint32_t Timer_17_RCC = ((uint32_t)0x00040000);
        constexpr static const uint32_t TIM9_RCC = ((uint32_t)0x00080000);
        constexpr static const uint32_t Timer_10_RCC = ((uint32_t)0x00100000);
        constexpr static const uint32_t Timer_11_RCC = ((uint32_t)0x00200000);
    } port_to_open;

    class Open
    {
    public:
        static void APB1Periph(uint32_t RCC_APB1Periph);
        static void APB2Periph(uint32_t RCC_APB2Periph);
        static void AHBPeriph(uint32_t AHBPe_RCCriph);
        static void port(GPIO_TypeDef *port);
    } open;

    class Close
    {
    public:
        static void APB1Periph(uint32_t RCC_APB1Periph);
        static void APB2Periph(uint32_t RCC_APB2Periph);
        static void AHBPeriph(uint32_t RCC_AHBPeriph);
        static void port(GPIO_TypeDef *port);
    } close;
} static clocks;

// 时间类声明
class time_us
{
public:
    constexpr time_us(uint16_t _val) : val(_val) {}
    constexpr operator uint16_t() const { return val; }
    uint16_t val;
};
class time_ms
{
public:
    constexpr time_ms(uint16_t _val) : val(_val) {}
    constexpr operator uint16_t() const { return val; }
    uint16_t val;
};
class time_s
{
public:
    constexpr time_s(uint16_t _val) : val(_val) {}
    constexpr operator uint16_t() const { return val; }
    uint16_t val;
};

// 运算符重载函数声明
inline constexpr time_us operator"" _us(unsigned long long _val)
{
    return time_us{static_cast<uint16_t>(_val)};
}
inline constexpr time_ms operator"" _ms(unsigned long long _val)
{
    return time_ms{static_cast<uint16_t>(_val)};
}
inline constexpr time_s operator"" _s(unsigned long long _val)
{
    return time_s{static_cast<uint16_t>(_val)};
}

// Device命名空间声明
namespace Device
{
    // Timer类声明
    class Timer
    {
    public:
        class Channal
        {

        public:
            uint8_t timer;
            uint8_t index;
            Channal(uint8_t _timer, uint8_t _index);
            uint32_t portRcc();
            inline Channal() = default;
            Timer::Channal &operator=(Timer::Channal &&that);
            uint16_t getPin();
            GPIO_TypeDef *getPort();

            // 动态初始化channal(标准库居然没有)
            void static TIM_OCxInit(TIM_TypeDef *TIMx,
                                    TIM_OCInitTypeDef *TIM_OCInitStruct,
                                    uint8_t channel);
            // 根据指定的通道号动态配置TIMx外设预加载寄存器
            void static TIM_OCxPreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload, uint8_t channel);

            void init();
            class ChannalType
            {
            public:
                constexpr static const uint8_t channal_1 = 0b0001;
                constexpr static const uint8_t channal_2 = 0b0010;
                constexpr static const uint8_t channal_3 = 0b0100;
                constexpr static const uint8_t channal_4 = 0b1000;
            };
        };
        class Universal_timer
        {
        public:
            class TimerType
            {
            public:
                constexpr static const uint8_t timer_2 = 0;
                constexpr static const uint8_t timer_3 = 1;
                constexpr static const uint8_t timer_4 = 2;
            };

        private:
            uint8_t index;
            TIM_TypeDef *BASIC_TIM;

        public:
            Universal_timer(uint8_t timerType, time_ms times);
            Universal_timer(uint8_t timerType, time_s times);
            void NVIC_Config();
            void TIM_Config(uint16_t ms_time);
        };

        class Advanced_timer
        {
        };
    };

    class PWM
    {
        uint8_t channals;
        uint8_t timer;
        uint16_t frequency;
        Timer::Channal channal_1;
        Timer::Channal channal_2;
        Timer::Channal channal_3;
        Timer::Channal channal_4;

    public:
        PWM(uint8_t timertype, uint8_t channals);
        void start();
        void stop();
        void change(uint8_t channal, uint16_t _frequency, uint8_t _dutyRatio);
        uint32_t getRcc();
    };
    // LED类声明
    class LED
    {
        GPIO_TypeDef *port;
        uint16_t pin;

    public:
        LED(GPIO_TypeDef *_port, uint16_t _pin,
            GPIOSpeed_TypeDef Speed = IOSpeed::_50MHz,
            GPIOMode_TypeDef mode = IOMode::Out_PP);
        void turn();
    };

    // OLED类声明
    class OLED
    {
    public:
        constexpr static const uint8_t OLED_8X16 = 8;
        constexpr static const uint8_t OLED_6X8 = 6;
        /*IsFilled参数数值*/
        constexpr static const uint8_t OLED_UNFILLED = 0;
        constexpr static const uint8_t OLED_FILLED = 1;
        GPIO_TypeDef *SCL_port;
        uint16_t SCL_pin;
        GPIO_TypeDef *SDA_port;
        uint16_t SDA_pin;
        uint8_t DisplayBuf[8][128];

        OLED(GPIO_TypeDef *_SCL_port = GPIOB, uint16_t _SCL_pin = GPIO_Pin_8,
             GPIO_TypeDef *_SDA_port = GPIOB, uint16_t _SDA_pin = GPIO_Pin_9);

        void W_SCL(uint8_t BitValue);
        void W_SDA(uint8_t BitValue);
        uint32_t GPIOX_to_RCC(GPIO_TypeDef *GPIOX);
        void OLED_GPIO_Init(void);
        void I2C_Start(void);
        void I2C_Stop(void);
        void I2C_SendByte(uint8_t Byte);
        void WriteCommand(uint8_t Command);
        void WriteData(uint8_t *Data, uint8_t Count);
        void Init(void);
        void SetCursor(uint8_t Page, uint8_t X);
        uint32_t Pow(uint32_t X, uint32_t Y);
        uint8_t pnpoly(uint8_t nvert, int16_t *vertx, int16_t *verty, int16_t testx, int16_t testy);
        uint8_t IsInAngle(int16_t X, int16_t Y, int16_t StartAngle, int16_t EndAngle);
        void Update(void);
        void UpdateArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
        void Clear(void);
        void ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
        void Reverse(void);
        void ReverseArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
        void ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize);
        void ShowString(int16_t X, int16_t Y, const char *String, uint8_t FontSize);
        void ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
        void ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
        void ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
        void ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
        void ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
        void ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
        void Printf(int16_t X, int16_t Y, uint8_t FontSize, char *format, ...);
        void DrawPoint(int16_t X, int16_t Y);
        uint8_t GetPoint(int16_t X, int16_t Y);
        void DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1);
        void DrawRectangle(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
        void DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled);
        void DrawCircle(int16_t X, int16_t Y, uint8_t Radius, uint8_t IsFilled);
        void DrawEllipse(int16_t X, int16_t Y, uint8_t A, uint8_t B, uint8_t IsFilled);
        void DrawArc(int16_t X, int16_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);
    };

    class ADC
    {
    public:
        class Mode
        {
        public:
            constexpr static const uint8_t non_continuous = 0;
            constexpr static const uint8_t continuous = 1;
            constexpr static const uint8_t non_multichannel = 0;
            constexpr static const uint8_t multichannel = 1;
            constexpr static const uint32_t T1_CC1 = ((uint32_t)0x00000000);             /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t T1_CC2 = ((uint32_t)0x00020000);             /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t T2_CC2 = ((uint32_t)0x00060000);             /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t T3_TRGO = ((uint32_t)0x00080000);            /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t T4_CC4 = ((uint32_t)0x000A0000);             /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t Ext_IT11_TIM8_TRGO = ((uint32_t)0x000C0000); /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t T1_CC3 = ((uint32_t)0x00040000);             /*!< For ADC1, ADC2 and ADC3 */
            constexpr static const uint32_t None = ((uint32_t)0x000E0000);               /*!< For ADC1, ADC2 and ADC3 */
        };
        enum Channel
        {
            Channel0 = ADC_Channel_0,   // PA0
            Channel1 = ADC_Channel_1,   // PA1
            Channel2 = ADC_Channel_2,   // PA2
            Channel3 = ADC_Channel_3,   // PA3
            Channel4 = ADC_Channel_4,   // PA4
            Channel5 = ADC_Channel_5,   // PA5
            Channel6 = ADC_Channel_6,   // PA6
            Channel7 = ADC_Channel_7,   // PA7
            Channel8 = ADC_Channel_8,   // PB0
            Channel9 = ADC_Channel_9,   // PB1
            Channel16 = ADC_Channel_16, // 内部温度传感器
            Channel17 = ADC_Channel_17  // 内部参考电压
        };
        class ADCType
        {
        public:
            inline static ADC_TypeDef *const adc1 = ADC1;
            inline static ADC_TypeDef *const adc2 = ADC2;
        };
        uint8_t iscontinuous;
        uint8_t num_channals;
        ADC_TypeDef *adcType;
        ADC(uint8_t iscontinuous, uint8_t num_channals, uint32_t triggerType, ADC_TypeDef *adc);
        void addChannal(uint8_t channal);
        uint16_t getChannal(uint8_t channal);
        float convertToTemperature(uint16_t adcValue);
    };

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
        char *
        getLastData();
        // void clear();
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

        // 接收缓冲区，增大到64字节
        char rxBuffer[64];
        bool hasNewData;

        // 添加格式化输出方法
        void printf(const char *fmt, ...);
    };
} // namespace Device

namespace System
{
    void delay(time_ms);
    void delay(time_us);
    void delay(time_s);
    class WatchDog
    {
    public:
        class IndependWatchDog
        {
        public:
            static void setTime(time_us timeus);
            static void setTime(time_ms timems);
            static void setTime(time_s times);
            static void feed(void);

        private:
            static void IWDG_Init(u8 prer, u16 rlr);
        };
    };
    class exitInterrput {
      GPIO_TypeDef *const port;
      uint16_t pin;
      void (*callback)(void);
      exitInterrput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                    EXTITrigger_TypeDef Trigger = EXTI_Trigger_Falling);
    };
    namespace power
    {
        inline void sleep_for_interrupt() { __WFI(); };
        inline void sleep_for_event() { __WFE(); };
        // STOP模式是一种低功耗模式，主要时钟停止，但RAM和寄存器内容保持不变。以下中断可以唤醒STOP模式：
        // EXTI线外部中断
        //  EXTI0-EXTI15：连接到GPIO引脚PA0-PF15的外部中断
        //  EXTI16：PVD电源电压检测器输出
        //  EXTI17：RTC闹钟中断
        //  EXTI18：USB唤醒事件（如有）
        //  EXTI19：ETH唤醒事件（如有）
        // 独立看门狗中断 (IWDG)
        // 窗口看门狗中断 (WWDG)
        // 实时时钟 (RTC) 闹钟中断
        // 外部复位引脚 (NRST)
        inline void stop()
        {
            // 使能PWR时钟
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
            // 清除唤醒标志
            PWR_ClearFlag(PWR_FLAG_WU);
            // 设置电压调节器模式
            PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
        };
        inline void stop_lpPowerControl()
        {
            // 使能PWR时钟
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
            // 清除唤醒标志
            PWR_ClearFlag(PWR_FLAG_WU);
            // 设置低功耗电压调节器模式
            PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
        };
        // 配置外部中断唤醒函数
        inline void configEXTIForWakeup(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                                        EXTITrigger_TypeDef Trigger = EXTI_Trigger_Falling)
        {
            // 使能GPIO和AFIO时钟
            if (GPIOx == GPIOA)
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
            else if (GPIOx == GPIOB)
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
            else if (GPIOx == GPIOC)
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

            // 初始化GPIO为输入模式
            GPIO_InitTypeDef GPIO_InitStructure;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 输入上拉
            GPIO_Init(GPIOx, &GPIO_InitStructure);

            // 配置EXTI线
            uint8_t GPIO_PortSource;
            uint8_t GPIO_PinSource = 0;

            // 确定PortSource
            if (GPIOx == GPIOA)
                GPIO_PortSource = GPIO_PortSourceGPIOA;
            else if (GPIOx == GPIOB)
                GPIO_PortSource = GPIO_PortSourceGPIOB;
            else if (GPIOx == GPIOC)
                GPIO_PortSource = GPIO_PortSourceGPIOC;

            // 确定PinSource
            for (uint8_t i = 0; i < 16; i++)
            {
                if (GPIO_Pin == (1 << i))
                {
                    GPIO_PinSource = i;
                    break;
                }
            }

            // 连接GPIO到EXTI线
            GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);

            // 配置EXTI
            EXTI_InitTypeDef EXTI_InitStructure;
            EXTI_InitStructure.EXTI_Line = GPIO_Pin; // EXTI线与GPIO_Pin保持一致
            EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
            EXTI_InitStructure.EXTI_Trigger = Trigger;
            EXTI_InitStructure.EXTI_LineCmd = ENABLE;
            EXTI_Init(&EXTI_InitStructure);

            // 配置NVIC
            NVIC_InitTypeDef NVIC_InitStructure;

            // 根据不同引脚配置不同的中断通道
            if (GPIO_Pin == GPIO_Pin_0)
                NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
            else if (GPIO_Pin == GPIO_Pin_1)
                NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
            else if (GPIO_Pin == GPIO_Pin_2)
                NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
            else if (GPIO_Pin == GPIO_Pin_3)
                NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
            else if (GPIO_Pin == GPIO_Pin_4)
                NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
            else if (GPIO_Pin >= GPIO_Pin_5 && GPIO_Pin <= GPIO_Pin_9)
                NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
            else if (GPIO_Pin >= GPIO_Pin_10 && GPIO_Pin <= GPIO_Pin_15)
                NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;

            NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
            NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
            NVIC_Init(&NVIC_InitStructure);
        }
        // 唤醒STANDBY模式的中断源
        // STANDBY模式是STM32最低功耗的模式，除备份域外，所有内容都会丢失。能唤醒STANDBY模式的中断源很少：

        // WKUP引脚 (PA0) 上的上升沿(必须通过PWR_WakeUpPinCmd(ENABLE)启用)
        // 实时时钟 (RTC) 闹钟事件(如果在进入STANDBY前已启用)
        // 外部复位 (NRST引脚)
        // 独立看门狗复位
        // 使用外部中断唤醒STOP模式
        inline void stopWithEXTIWakeup(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                                       EXTITrigger_TypeDef Trigger = EXTI_Trigger_Falling)
        {
            // 配置外部中断
            configEXTIForWakeup(GPIOx, GPIO_Pin, Trigger);

            // 使能PWR时钟
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

            // 清除唤醒标志
            PWR_ClearFlag(PWR_FLAG_WU);

            // 进入STOP模式
            PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);

            // 唤醒后需要重新配置系统时钟
            SystemInit();
        }
        inline void standby()
        {
            // 使能PWR时钟
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
            // 清除唤醒标志
            PWR_ClearFlag(PWR_FLAG_WU);
            // 设置唤醒引脚(如需启用，取消注释)
            PWR_WakeUpPinCmd(ENABLE);
            // 进入待机模式
            PWR_EnterSTANDBYMode();
        };
    }
    // 重要区别
    // STOP模式
    // 保留RAM内容和寄存器值
    // 唤醒后从停止点继续执行
    // 唤醒源较多
    // 功耗中等
    // STANDBY模式
    // 除备份寄存器外不保留任何内容
    // 唤醒相当于系统复位
    // 唤醒源极少
    // 功耗最低
};

#endif // _TP_H_
