#ifndef _MYSTM32_H_
#define _MYSTM32_H_
#include "stm32f10x.h"
#include <cstddef>
#include <cstdint>

// 中断处理函数宏定义
#define timer2_fun extern "C" void TIM2_IRQHandler(void)
#define timer3_fun extern "C" void TIM3_IRQHandler(void)
#define timer4_fun extern "C" void TIM4_IRQHandler(void)
//#define USART1_fun extern "C" void USART1_IRQHandler(void)
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

// 所有设备类已移动到各自的头文件
// System命名空间已移动到System.h

#endif // _MYSTM32_H_
