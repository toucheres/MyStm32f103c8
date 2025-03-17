#ifndef _MYSTM32_H_
#define _MYSTM32_H_

#include "stm32f10x.h"
extern "C"
{
#include "OLED.h"
#include <math.h>
#include <stdio.h>
#include "Delay.h"    
}

#define timer2_fun extern "C" void TIM2_IRQHandler(void)
#define timer3_fun extern "C" void TIM3_IRQHandler(void)
#define timer4_fun extern "C" void TIM4_IRQHandler(void)

// Port类声明
class Port
{
public:
    static GPIO_TypeDef *const A;
    static GPIO_TypeDef *const B;
    static GPIO_TypeDef *const C;
    static GPIO_TypeDef *const D;
    static GPIO_TypeDef *const E;
    static GPIO_TypeDef *const F;
    static GPIO_TypeDef *const G;
};

// Pin类声明
class Pin
{
public:
    static const uint16_t Pin0 = GPIO_Pin_0;
    static const uint16_t Pin1 = GPIO_Pin_1;
    static const uint16_t Pin2 = GPIO_Pin_2;
    static const uint16_t Pin3 = GPIO_Pin_3;
    static const uint16_t Pin4 = GPIO_Pin_4;
    static const uint16_t Pin5 = GPIO_Pin_5;
    static const uint16_t Pin6 = GPIO_Pin_6;
    static const uint16_t Pin7 = GPIO_Pin_7;
    static const uint16_t Pin8 = GPIO_Pin_8;
    static const uint16_t Pin9 = GPIO_Pin_9;
    static const uint16_t Pin10 = GPIO_Pin_10;
    static const uint16_t Pin11 = GPIO_Pin_11;
    static const uint16_t Pin12 = GPIO_Pin_12;
    static const uint16_t Pin13 = GPIO_Pin_13;
    static const uint16_t Pin14 = GPIO_Pin_14;
    static const uint16_t Pin15 = GPIO_Pin_15;
};

// IOMode类声明
class IOMode
{
public:
    static const GPIOMode_TypeDef AIN = GPIO_Mode_AIN;
    static const GPIOMode_TypeDef IN_FLOATING = GPIO_Mode_IN_FLOATING;
    static const GPIOMode_TypeDef IPD = GPIO_Mode_IPD;
    static const GPIOMode_TypeDef IPU = GPIO_Mode_IPU;
    static const GPIOMode_TypeDef Out_OD = GPIO_Mode_Out_OD;
    static const GPIOMode_TypeDef Out_PP = GPIO_Mode_Out_PP;
    static const GPIOMode_TypeDef AF_OD = GPIO_Mode_AF_OD;
    static const GPIOMode_TypeDef AF_PP = GPIO_Mode_AF_PP;
};

// IOSpeed类声明
class IOSpeed
{
public:
    static const GPIOSpeed_TypeDef _50MHz = GPIO_Speed_50MHz;
    static const GPIOSpeed_TypeDef _2MHz = GPIO_Speed_2MHz;
    static const GPIOSpeed_TypeDef _10MHz = GPIO_Speed_10MHz;
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
        Port_Init ProtD{Port::D};
        Port_Init ProtE{Port::E};
        Port_Init ProtF{Port::F};
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
        Port_Write ProtD{Port::D};
        Port_Write ProtE{Port::E};
        Port_Write ProtF{Port::F};
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
        Port_read ProtD{Port::D};
        Port_read ProtE{Port::E};
        Port_read ProtF{Port::F};
    } static read;

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
class time_ms
{
public:
    constexpr time_ms(uint16_t _val) : val(_val) {}
    uint16_t val;
};

class time_s
{
public:
    constexpr time_s(uint16_t _val) : val(_val) {}
    uint16_t val;
};

// 运算符重载函数声明
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
            inline Channal()=default;
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
        // uint32_t Port_to_Rcc(GPIO_TypeDef *in);
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

    // OLED_类声明 - C++风格接口封装
    // class OLED_
    // {
    // private:
    //     enum FontSize
    //     {
    //         FONT_6X8 = 6,
    //         FONT_8X16 = 8
    //     };

    //     enum FillMode
    //     {
    //         UNFILLED = 0,
    //         FILLED = 1
    //     };

    // public:
    //     OLED_();
    //     void Update();
    //     void UpdateArea(int16_t x, int16_t y, uint8_t width, uint8_t height);
    //     void Clear();
    //     void ClearArea(int16_t x, int16_t y, uint8_t width, uint8_t height);
    //     void Reverse();
    //     void ReverseArea(int16_t x, int16_t y, uint8_t width, uint8_t height);
    //     void ShowChar(int16_t x, int16_t y, char ch, uint8_t fontSize);
    //     void ShowString(int16_t x, int16_t y, const char *str, uint8_t fontSize);
    //     void ShowNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize);
    //     void ShowSignedNum(int16_t x, int16_t y, int32_t number, uint8_t length, uint8_t fontSize);
    //     void ShowHexNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize);
    //     void ShowBinNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize);
    //     void ShowFloatNum(int16_t x, int16_t y, double number, uint8_t intLength,
    //                       uint8_t fraLength, uint8_t fontSize);
    //     void ShowImage(int16_t x, int16_t y, uint8_t width, uint8_t height, const uint8_t *image);
    //     void Printf(int16_t x, int16_t y, uint8_t fontSize, const char *format, ...);
    //     void DrawPoint(int16_t x, int16_t y);
    //     bool GetPoint(int16_t x, int16_t y);
    //     void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    //     void DrawRectangle(int16_t x, int16_t y, uint8_t width, uint8_t height, bool filled = false);
    //     void DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    //                       int16_t x2, int16_t y2, bool filled = false);
    //     void DrawCircle(int16_t x, int16_t y, uint8_t radius, bool filled = false);
    //     void DrawEllipse(int16_t x, int16_t y, uint8_t a, uint8_t b, bool filled = false);
    //     void DrawArc(int16_t x, int16_t y, uint8_t radius,
    //                  int16_t startAngle, int16_t endAngle, bool filled = false);

    //     static constexpr uint8_t FONT_SIZE_6X8 = OLED_6X8;
    //     static constexpr uint8_t FONT_SIZE_8X16 = OLED_8X16;
    // };
} // namespace Device

#endif // _TP_H_
