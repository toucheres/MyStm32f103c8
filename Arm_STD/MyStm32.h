#include "stm32f10x.h"
extern "C"
{
#include <stdarg.h>
#include "OLED.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include "OLED_Data.h"
}
// #include "OLED.h"
#define timer2_fun extern "C" void TIM2_IRQHandler(void)
#define timer3_fun extern "C" void TIM3_IRQHandler(void)
#define timer4_fun extern "C" void TIM4_IRQHandler(void)
// #include <vector>
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
inline GPIO_TypeDef *const Port::A = GPIOA;
inline GPIO_TypeDef *const Port::B = GPIOB;
inline GPIO_TypeDef *const Port::C = GPIOC;
inline GPIO_TypeDef *const Port::D = GPIOD;
inline GPIO_TypeDef *const Port::E = GPIOE;
inline GPIO_TypeDef *const Port::F = GPIOF;
inline GPIO_TypeDef *const Port::G = GPIOG;
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
class IOSpeed
{
public:
    static const GPIOSpeed_TypeDef _50MHz = GPIO_Speed_50MHz;
    static const GPIOSpeed_TypeDef _2MHz = GPIO_Speed_2MHz;
    static const GPIOSpeed_TypeDef _10MHz = GPIO_Speed_10MHz;
};
// 前向声明
// IO类 - 零内存开销设计
class IO
{
    static uint16_t used[3];
    // IO()=default;
public:
    static bool sign(const GPIO_TypeDef *_port, const uint16_t _pin)
    {
        int index = 0;
        if (_port == Port::A)
            index = 0;
        else if (_port == Port::B)
            index = 1;
        else if (_port == Port::C)
            index = 2;
        else if (_port == Port::D)
            index = 3;
        if (used[index] & _pin)
        {
            return false;
        }
        else
        {
            used[index] &= _pin;
            return true;
        }
    }

    class
    {
        GPIO_TypeDef *port;
        static void doInitPin(GPIO_TypeDef *port, uint16_t pin,
                              GPIOMode_TypeDef mode)
        {
            GPIO_InitTypeDef GPIO_InitStructure;
            GPIO_InitStructure.GPIO_Pin = pin;
            GPIO_InitStructure.GPIO_Mode = mode;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(port, &GPIO_InitStructure);
        }

    public:
        class Port_Init
        {
            GPIO_TypeDef *port;

        public:
            Port_Init(GPIO_TypeDef *_port) : port(_port) {}
            void Pin0(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_0, mode);
            }
            void Pin1(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_1, mode);
            }
            void Pin2(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_2, mode);
            }
            void Pin3(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_3, mode);
            }
            void Pin4(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_4, mode);
            }
            void Pin5(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_5, mode);
            }
            void Pin6(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_6, mode);
            }
            void Pin7(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_7, mode);
            }
            void Pin8(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_8, mode);
            }
            void Pin9(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_9, mode);
            }
            void Pin10(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_10, mode);
            }
            void Pin11(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_11, mode);
            }
            void Pin12(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_12, mode);
            }
            void Pin13(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_13, mode);
            }
            void Pin14(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_14, mode);
            }
            void Pin15(GPIOMode_TypeDef mode) const
            {
                doInitPin(port, GPIO_Pin_15, mode);
            }
        };
        Port_Init ProtA{Port::A};
        Port_Init ProtB{Port::B};
        Port_Init ProtC{Port::C};
        Port_Init ProtD{Port::D};
        Port_Init ProtE{Port::E};
        Port_Init ProtF{Port::F};
    } static init;

    class
    {
        GPIO_TypeDef *port;
        static void doWritePin(GPIO_TypeDef *port, uint16_t pin, BitAction value)
        {
            GPIO_WriteBit(port, pin, value);
        }

    public:
        class Port_Write
        {
            GPIO_TypeDef *port;

        public:
            Port_Write(GPIO_TypeDef *_port) : port(_port) {}
            void Pin0(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_0, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin1(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_1, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin2(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_2, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin3(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_3, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin4(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_4, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin5(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_5, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin6(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_6, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin7(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_7, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin8(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_8, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin9(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_9, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin10(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_10, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin11(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_11, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin12(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_12, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin13(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_13, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin14(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_14, value != 0 ? Bit_SET : Bit_RESET);
            }
            void Pin15(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_15, value != 0 ? Bit_SET : Bit_RESET);
            }
        };
        Port_Write ProtA{Port::A};
        Port_Write ProtB{Port::B};
        Port_Write ProtC{Port::C};
        Port_Write ProtD{Port::D};
        Port_Write ProtE{Port::E};
        Port_Write ProtF{Port::F};
    } static write;

    class
    {
        Port port;
        static bool doReadPin(GPIO_TypeDef *prot, uint16_t pin)
        {
            return GPIO_ReadInputDataBit(prot, pin) != 0;
        }

    public:
        class Port_read
        {
            GPIO_TypeDef *port;

        public:
            Port_read(GPIO_TypeDef *_port) : port(_port) {}
            void Pin0(uint8_t value) const { doReadPin(port, GPIO_Pin_0); }
            void Pin1(uint8_t value) const { doReadPin(port, GPIO_Pin_1); }
            void Pin2(uint8_t value) const { doReadPin(port, GPIO_Pin_2); }
            void Pin3(uint8_t value) const { doReadPin(port, GPIO_Pin_3); }
            void Pin4(uint8_t value) const { doReadPin(port, GPIO_Pin_4); }
            void Pin5(uint8_t value) const { doReadPin(port, GPIO_Pin_5); }
            void Pin6(uint8_t value) const { doReadPin(port, GPIO_Pin_6); }
            void Pin7(uint8_t value) const { doReadPin(port, GPIO_Pin_7); }
            void Pin8(uint8_t value) const { doReadPin(port, GPIO_Pin_8); }
            void Pin9(uint8_t value) const { doReadPin(port, GPIO_Pin_9); }
            void Pin10(uint8_t value) const { doReadPin(port, GPIO_Pin_10); }
            void Pin11(uint8_t value) const { doReadPin(port, GPIO_Pin_11); }
            void Pin12(uint8_t value) const { doReadPin(port, GPIO_Pin_12); }
            void Pin13(uint8_t value) const { doReadPin(port, GPIO_Pin_13); }
            void Pin14(uint8_t value) const { doReadPin(port, GPIO_Pin_14); }
            void Pin15(uint8_t value) const { doReadPin(port, GPIO_Pin_15); }
        };
        Port_read ProtA{Port::A};
        Port_read ProtB{Port::A};
        Port_read ProtC{Port::A};
        Port_read ProtD{Port::A};
        Port_read ProtE{Port::A};
        Port_read ProtF{Port::A};
    } static read;

    static uint16_t read_port(GPIO_TypeDef *port)
    {
        return GPIO_ReadInputData(port);
    }
    static uint8_t read_pin(GPIO_TypeDef *port, uint16_t pin)
    {
        return GPIO_ReadInputDataBit(port, pin);
    }
    static void Write_port(GPIO_TypeDef *port, uint16_t val)
    {
        GPIO_Write(port, val);
    }
    static void Write_pin(GPIO_TypeDef *port, uint16_t pin, bool val)
    {
        GPIO_WriteBit(port, pin, val == true ? Bit_SET : Bit_RESET);
    }
    static void Write_pin(GPIO_TypeDef *port, uint16_t pin, BitAction val)
    {
        GPIO_WriteBit(port, pin, val);
    }
    static void Change_pin(GPIO_TypeDef *port, uint16_t pin)
    {
        IO::Write_pin(port, pin, !IO::read_pin(port, pin));
    }
} static io;
inline uint16_t IO::used[3] = {0, 0, 0};

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
        static void APB1Periph(uint32_t RCC_APB1Periph)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph, ENABLE);
        }
        static void APB2Periph(uint32_t RCC_APB2Periph)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
        }
        static void AHBPeriph(uint32_t AHBPe_RCCriph)
        {
            RCC_AHBPeriphClockCmd(AHBPe_RCCriph, ENABLE);
        }
        static void port(GPIO_TypeDef *port)
        {
            // GPIOA_BASE = APB2PERIPH_BASE + 0x0800;
            uint32_t portAddr = reinterpret_cast<uint32_t>(port);
            uint32_t offset = portAddr - APB2PERIPH_BASE;
            uint8_t index = offset / 0x0400;
            // 根据偏移量启用相应的时钟
            RCC_APB2PeriphClockCmd(1 << index, ENABLE);
        }
    } open;
    class Close
    {
    public:
        static void APB1Periph(uint32_t RCC_APB1Periph)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph, DISABLE);
        }
        static void APB2Periph(uint32_t RCC_APB2Periph)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph, DISABLE);
        }
        static void AHBPeriph(uint32_t RCC_AHBPeriph)
        {
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph, DISABLE);
        }
        static void port(GPIO_TypeDef *port)
        {
            // GPIOA_BASE = APB2PERIPH_BASE + 0x0800;
            uint32_t portAddr = reinterpret_cast<uint32_t>(port);
            uint32_t offset = portAddr - APB2PERIPH_BASE;
            uint8_t index = offset / 0x0400;
            // 根据偏移量启用相应的时钟
            RCC_APB2PeriphClockCmd(1 << index, DISABLE);
        }
    } close;
    // Timer1为总线2(高级)
    // Timer2/3/4为总线1(通用)
    // GPIO a~g 中断为总线2
} static clocks;

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

inline constexpr time_ms operator"" _ms(unsigned long long _val)
{
    return time_ms{static_cast<uint16_t>(_val)};
}
inline constexpr time_s operator"" _s(unsigned long long _val)
{
    return time_s{static_cast<uint16_t>(_val)};
}
namespace Device
{
    class Timer
    {
    public:
        class Universal_timer
        {
        public:
            class TimerType
            {
            public:
                static const uint8_t timer_2 = 0;
                static const uint8_t timer_3 = 1;
                static const uint8_t timer_4 = 2;
            };
            // 中断优先级配置
            // #define BASIC_TIM TIM4
            // #define BASIC_TIM_APBxClock_FUN RCC_APB1PeriphClockCmd
            // #define BASIC_TIM_CLK RCC_APB1Periph_TIM4
            // #define BASIC_TIM_Period (1000 - 1)
            // #define BASIC_TIM_Prescaler 71
            // #define BASIC_TIM_IRQ TIM4_IRQn // 中断来源
            // #define BASIC_TIM_IRQHandler TIM6_IRQHandler
        private:
            uint8_t index;
            TIM_TypeDef *BASIC_TIM;

        public:
            Universal_timer(uint8_t timerType, time_ms times)
                : index(timerType), BASIC_TIM((TIM_TypeDef *)(APB1PERIPH_BASE + (0x0400 * index)))
            {
                NVIC_Config();
                TIM_Config(times.val);
            };
            Universal_timer(uint8_t timerType, time_s times)
                : index(timerType), BASIC_TIM(TIM2 + (0x0400) * (index))
            {
                NVIC_Config();
                TIM_Config(times.val * 1000);
            };
            void NVIC_Config()
            {
                NVIC_InitTypeDef NVIC_InitStructure;
                // 设置中断组为0
                NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
                // 设置中断来源
                // IRQn_Type;
                NVIC_InitStructure.NVIC_IRQChannel = index + 28;
                // 设置主优先级为 0
                NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
                // 设置抢占优先级为3
                NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
                NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
                NVIC_Init(&NVIC_InitStructure);
            }

            // void TIM_Config(uint16_t ms_time)
            // {
            //     // 预分频器设为71，使得计数频率为72M/(71+1)=1MHz ，即计数一次
            //     // 1MHz = 10**6Hz
            //     uint16_t BASIC_TIM_Prescaler = 72*10-1;

            //     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

            //     // 开启定时器时钟,即内部时钟CK_INT=72M
            //     RCC_APB1PeriphClockCmd(((uint32_t)0x00000001) << (index), ENABLE);

            //     // 将毫秒转换为微秒，作为周期值
            //     // 例如：10ms = 10 * 1000us = 10000us，对应Period=9999
            //     TIM_TimeBaseStructure.TIM_Period = (ms_time*100) - 1;

            //     // 时钟预分频数
            //     TIM_TimeBaseStructure.TIM_Prescaler = BASIC_TIM_Prescaler;

            //     // 时钟分频因子，基本定时器没有，不用管
            //     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

            //     // 计数器计数模式，基本定时器只能向上计数，没有计数模式的设置
            //     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

            //     // 重复计数器的值，基本定时器没有，不用管
            //     TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

            //     // 初始化定时器
            //     TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);

            //     // 清除计数器中断标志位
            //     TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);

            //     // 开启计数器中断
            //     TIM_ITConfig(BASIC_TIM, TIM_IT_Update, ENABLE);

            //     // 使能计数器
            //     TIM_Cmd(BASIC_TIM, ENABLE);
            // }
            void TIM_Config(uint16_t ms_time)
            {
                // 两级分频方式来实现毫秒级定时
                // 第一级：72MHz / (71+1) = 1MHz（每微秒计数一次）
                uint16_t BASIC_TIM_Prescaler = 72 * 100 - 1;

                TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

                // 开启定时器时钟
                RCC_APB1PeriphClockCmd(((uint32_t)0x00000001) << (index), ENABLE);

                // 第二级：使用 Period 值设置中断周期
                // 例如设置 ms_time=500，则 Period=500-1=499
                // 表示500ms触发一次中断
                TIM_TimeBaseStructure.TIM_Period = ms_time * 10 - 1;

                // 预分频值（72分频得到1MHz计数频率）
                TIM_TimeBaseStructure.TIM_Prescaler = BASIC_TIM_Prescaler;

                // 时钟分频因子
                TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

                // 向上计数模式
                TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

                // 不使用重复计数
                TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

                // 初始化定时器
                TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);

                // 清除计数器中断标志位
                TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);

                // 开启计数器中断
                TIM_ITConfig(BASIC_TIM, TIM_IT_Update, ENABLE);

                // 使能计数器
                TIM_Cmd(BASIC_TIM, ENABLE);
            }
        };
        class Advanced_timer
        {
        };
    };
    class LED
    {
        GPIO_TypeDef *port;
        uint16_t pin;

    public:
        LED(GPIO_TypeDef *_port, uint16_t _pin,
            GPIOSpeed_TypeDef Speed = IOSpeed::_50MHz,
            GPIOMode_TypeDef mode = IOMode::Out_PP)
            : pin(_pin), port(_port)
        {
            if (io.sign(_port, _pin))
            {
                clocks.open.port(Port::A);
                GPIO_InitTypeDef GPIO_InitStructure;
                GPIO_InitStructure.GPIO_Pin = pin;
                GPIO_InitStructure.GPIO_Mode = mode;
                GPIO_InitStructure.GPIO_Speed = Speed;
                GPIO_Init(port, &GPIO_InitStructure);
                io.Write_pin(port, pin, 0);
            }
        }
        void turn() { io.Change_pin(this->port, this->pin); }
    };

    /***************************************************************************************
     * 本程序由江协科技创建并免费开源共享
     * 你可以任意查看、使用和修改，并应用到自己的项目之中
     * 程序版权归江协科技所有，任何人或组织不得将其据为己有
     *
     * 程序名称：				0.96寸OLED显示屏驱动程序（4针脚I2C接口）
     * 程序创建时间：			2023.10.24
     * 当前程序版本：			V2.0
     * 当前版本发布时间：		2024.10.20
     *
     * 江协科技官方网站：		jiangxiekeji.com
     * 江协科技官方淘宝店：	jiangxiekeji.taobao.com
     * 程序介绍及更新动态：	jiangxiekeji.com/tutorial/oled.html
     *
     * 如果你发现程序中的漏洞或者笔误，可通过邮件向我们反馈：feedback@jiangxiekeji.com
     * 发送邮件之前，你可以先到更新动态页面查看最新程序，如果此问题已经修改，则无需再发邮件
     ***************************************************************************************
     */

    /**
     * 数据存储格式：
     * 纵向8点，高位在下，先从左到右，再从上到下
     * 每一个Bit对应一个像素点
     *
     *      B0 B0                  B0 B0
     *      B1 B1                  B1 B1
     *      B2 B2                  B2 B2
     *      B3 B3  ------------->  B3 B3 --
     *      B4 B4                  B4 B4  |
     *      B5 B5                  B5 B5  |
     *      B6 B6                  B6 B6  |
     *      B7 B7                  B7 B7  |
     *                                    |
     *  -----------------------------------
     *  |
     *  |   B0 B0                  B0 B0
     *  |   B1 B1                  B1 B1
     *  |   B2 B2                  B2 B2
     *  --> B3 B3  ------------->  B3 B3
     *      B4 B4                  B4 B4
     *      B5 B5                  B5 B5
     *      B6 B6                  B6 B6
     *      B7 B7                  B7 B7
     *
     * 坐标轴定义：
     * 左上角为(0, 0)点
     * 横向向右为X轴，取值范围：0~127
     * 纵向向下为Y轴，取值范围：0~63
     *
     *       0             X轴           127
     *      .------------------------------->
     *    0 |
     *      |
     *      |
     *      |
     *  Y轴 |
     *      |
     *      |
     *      |
     *   63 |
     *      v
     *
     */
    class OLED
    {
    public:
        /*全局变量*********************/

        /**
         * OLED显存数组
         * 所有的显示函数，都只是对此显存数组进行读写
         * 随后调用Update函数或UpdateArea函数
         * 才会将显存数组的数据发送到OLED硬件，进行显示
         */
        GPIO_TypeDef *SCL_port;
        uint16_t SCL_pin;
        GPIO_TypeDef *SDA_port;
        uint16_t SDA_pin;
        uint8_t DisplayBuf[8][128];

        /*********************全局变量*/

        /*引脚配置*********************/

        /**
         * 函    数：OLED写SCL高低电平
         * 参    数：要写入SCL的电平值，范围：0/1
         * 返 回 值：无
         * 说    明：当上层函数需要写SCL时，此函数会被调用
         *           用户需要根据参数传入的值，将SCL置为高电平或者低电平
         *           当参数传入0时，置SCL为低电平，当参数传入1时，置SCL为高电平
         */

        OLED(GPIO_TypeDef *_SCL_port = GPIOB, uint16_t _SCL_pin = GPIO_Pin_8,
             GPIO_TypeDef *_SDA_port = GPIOB, uint16_t _SDA_pin = GPIO_Pin_9)
            : SCL_port(_SCL_port), SCL_pin(_SCL_pin), SDA_port(_SDA_port), SDA_pin(_SDA_pin)
        {
        }

        void W_SCL(uint8_t BitValue)
        {
            /*根据BitValue的值，将SCL置高电平或者低电平*/
            GPIO_WriteBit(SCL_port, SCL_pin, (BitAction)BitValue);

            /*如果单片机速度过快，可在此添加适量延时，以避免超出I2C通信的最大速度*/
            //...
        }

        /**
         * 函    数：OLED写SDA高低电平
         * 参    数：要写入SDA的电平值，范围：0/1
         * 返 回 值：无
         * 说    明：当上层函数需要写SDA时，此函数会被调用
         *           用户需要根据参数传入的值，将SDA置为高电平或者低电平
         *           当参数传入0时，置SDA为低电平，当参数传入1时，置SDA为高电平
         */
        void W_SDA(uint8_t BitValue)
        {
            /*根据BitValue的值，将SDA置高电平或者低电平*/
            GPIO_WriteBit(SDA_port, SDA_pin, (BitAction)BitValue);

            /*如果单片机速度过快，可在此添加适量延时，以避免超出I2C通信的最大速度*/
            //...
        }

        /**
         * 函    数：OLED引脚初始化
         * 参    数：无
         * 返 回 值：无
         * 说    明：当上层函数需要初始化时，此函数会被调用
         *           用户需要将SCL和SDA引脚初始化为开漏模式，并释放引脚
         */
        uint32_t GPIOX_to_RCC(GPIO_TypeDef *GPIOX)
        {

            //  (GPIOA)APB2PERIPH_BASE + 0x0800 RCC_APB2Periph_GPIOA((uint32_t)0x00000004)
            //  (GPIOB)APB2PERIPH_BASE + 0x0C00 RCC_APB2Periph_GPIOB((uint32_t)0x00000008)
            return 1 << (reinterpret_cast<uint32_t>(GPIOX) - APB2PERIPH_BASE) / (0x0400);
        }
        void OLED_GPIO_Init(void)
        {
            uint32_t i, j;

            /*在初始化前，加入适量延时，待OLED供电稳定*/
            for (i = 0; i < 1000; i++)
            {
                for (j = 0; j < 1000; j++)
                    ;
            }

            /*将SCL和SDA引脚初始化为开漏模式*/
            RCC_APB2PeriphClockCmd(GPIOX_to_RCC(SCL_port), ENABLE);
            RCC_APB2PeriphClockCmd(GPIOX_to_RCC(SDA_port), ENABLE);

            GPIO_InitTypeDef GPIO_InitStructure;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Pin = SCL_pin;
            GPIO_Init(SCL_port, &GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = SDA_pin;
            GPIO_Init(SDA_port, &GPIO_InitStructure);

            /*释放SCL和SDA*/
            W_SCL(1);
            W_SDA(1);
        }

        /*********************引脚配置*/

        /*通信协议*********************/

        /**
         * 函    数：I2C起始
         * 参    数：无
         * 返 回 值：无
         */
        void I2C_Start(void)
        {
            W_SDA(1); // 释放SDA，确保SDA为高电平
            W_SCL(1); // 释放SCL，确保SCL为高电平
            W_SDA(0); // 在SCL高电平期间，拉低SDA，产生起始信号
            W_SCL(0); // 起始后把SCL也拉低，即为了占用总线，也为了方便总线时序的拼接
        }

        /**
         * 函    数：I2C终止
         * 参    数：无
         * 返 回 值：无
         */
        void I2C_Stop(void)
        {
            W_SDA(0); // 拉低SDA，确保SDA为低电平
            W_SCL(1); // 释放SCL，使SCL呈现高电平
            W_SDA(1); // 在SCL高电平期间，释放SDA，产生终止信号
        }

        /**
         * 函    数：I2C发送一个字节
         * 参    数：Byte 要发送的一个字节数据，范围：0x00~0xFF
         * 返 回 值：无
         */
        void I2C_SendByte(uint8_t Byte)
        {
            uint8_t i;

            /*循环8次，主机依次发送数据的每一位*/
            for (i = 0; i < 8; i++)
            {
                /*使用掩码的方式取出Byte的指定一位数据并写入到SDA线*/
                /*两个!的作用是，让所有非零的值变为1*/
                W_SDA(!!(Byte & (0x80 >> i)));
                W_SCL(1); // 释放SCL，从机在SCL高电平期间读取SDA
                W_SCL(0); // 拉低SCL，主机开始发送下一位数据
            }

            W_SCL(1); // 额外的一个时钟，不处理应答信号
            W_SCL(0);
        }

        /**
         * 函    数：OLED写命令
         * 参    数：Command 要写入的命令值，范围：0x00~0xFF
         * 返 回 值：无
         */
        void WriteCommand(uint8_t Command)
        {
            I2C_Start();           // I2C起始
            I2C_SendByte(0x78);    // 发送OLED的I2C从机地址
            I2C_SendByte(0x00);    // 控制字节，给0x00，表示即将写命令
            I2C_SendByte(Command); // 写入指定的命令
            I2C_Stop();            // I2C终止
        }

        /**
         * 函    数：OLED写数据
         * 参    数：Data 要写入数据的起始地址
         * 参    数：Count 要写入数据的数量
         * 返 回 值：无
         */
        void WriteData(uint8_t *Data, uint8_t Count)
        {
            uint8_t i;

            I2C_Start();        // I2C起始
            I2C_SendByte(0x78); // 发送OLED的I2C从机地址
            I2C_SendByte(0x40); // 控制字节，给0x40，表示即将写数据
            /*循环Count次，进行连续的数据写入*/
            for (i = 0; i < Count; i++)
            {
                I2C_SendByte(Data[i]); // 依次发送Data的每一个数据
            }
            I2C_Stop(); // I2C终止
        }

        /*********************通信协议*/

        /*硬件配置*********************/

        /**
         * 函    数：OLED初始化
         * 参    数：无
         * 返 回 值：无
         * 说    明：使用前，需要调用此初始化函数
         */
        void Init(void)
        {
            OLED_GPIO_Init(); // 先调用底层的端口初始化

            /*写入一系列的命令，对OLED进行初始化配置*/
            WriteCommand(0xAE); // 设置显示开启/关闭，0xAE关闭，0xAF开启

            WriteCommand(0xD5); // 设置显示时钟分频比/振荡器频率
            WriteCommand(0x80); // 0x00~0xFF

            WriteCommand(0xA8); // 设置多路复用率
            WriteCommand(0x3F); // 0x0E~0x3F

            WriteCommand(0xD3); // 设置显示偏移
            WriteCommand(0x00); // 0x00~0x7F

            WriteCommand(0x40); // 设置显示开始行，0x40~0x7F

            WriteCommand(0xA1); // 设置左右方向，0xA1正常，0xA0左右反置

            WriteCommand(0xC8); // 设置上下方向，0xC8正常，0xC0上下反置

            WriteCommand(0xDA); // 设置COM引脚硬件配置
            WriteCommand(0x12);

            WriteCommand(0x81); // 设置对比度
            WriteCommand(0xCF); // 0x00~0xFF

            WriteCommand(0xD9); // 设置预充电周期
            WriteCommand(0xF1);

            WriteCommand(0xDB); // 设置VCOMH取消选择级别
            WriteCommand(0x30);

            WriteCommand(0xA4); // 设置整个显示打开/关闭

            WriteCommand(0xA6); // 设置正常/反色显示，0xA6正常，0xA7反色

            WriteCommand(0x8D); // 设置充电泵
            WriteCommand(0x14);

            WriteCommand(0xAF); // 开启显示

            Clear();  // 清空显存数组
            Update(); // 更新显示，清屏，防止初始化后未显示内容时花屏
        }

        /**
         * 函    数：OLED设置显示光标位置
         * 参    数：Page 指定光标所在的页，范围：0~7
         * 参    数：X 指定光标所在的X轴坐标，范围：0~127
         * 返 回 值：无
         * 说    明：OLED默认的Y轴，只能8个Bit为一组写入，即1页等于8个Y轴坐标
         */
        void SetCursor(uint8_t Page, uint8_t X)
        {
            /*如果使用此程序驱动1.3寸的OLED显示屏，则需要解除此注释*/
            /*因为1.3寸的OLED驱动芯片（SH1106）有132列*/
            /*屏幕的起始列接在了第2列，而不是第0列*/
            /*所以需要将X加2，才能正常显示*/
            //	X += 2;

            /*通过指令设置页地址和列地址*/
            WriteCommand(0xB0 | Page);              // 设置页位置
            WriteCommand(0x10 | ((X & 0xF0) >> 4)); // 设置X位置高4位
            WriteCommand(0x00 | (X & 0x0F));        // 设置X位置低4位
        }

        /*********************硬件配置*/

        /*工具函数*********************/

        /*工具函数仅供内部部分函数使用*/

        /**
         * 函    数：次方函数
         * 参    数：X 底数
         * 参    数：Y 指数
         * 返 回 值：等于X的Y次方
         */
        uint32_t Pow(uint32_t X, uint32_t Y)
        {
            uint32_t Result = 1; // 结果默认为1
            while (Y--)          // 累乘Y次
            {
                Result *= X; // 每次把X累乘到结果上
            }
            return Result;
        }

        /**
         * 函    数：判断指定点是否在指定多边形内部
         * 参    数：nvert 多边形的顶点数
         * 参    数：vertx verty 包含多边形顶点的x和y坐标的数组
         * 参    数：testx testy 测试点的X和y坐标
         * 返 回 值：指定点是否在指定多边形内部，1：在内部，0：不在内部
         */
        uint8_t pnpoly(uint8_t nvert, int16_t *vertx, int16_t *verty, int16_t testx, int16_t testy)
        {
            int16_t i, j, c = 0;

            /*此算法由W. Randolph Franklin提出*/
            /*参考链接：https://wrfranklin.org/Research/Short_Notes/pnpoly.html*/
            for (i = 0, j = nvert - 1; i < nvert; j = i++)
            {
                if (((verty[i] > testy) != (verty[j] > testy)) &&
                    (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
                {
                    c = !c;
                }
            }
            return c;
        }

        /**
         * 函    数：判断指定点是否在指定角度内部
         * 参    数：X Y 指定点的坐标
         * 参    数：StartAngle EndAngle 起始角度和终止角度，范围：-180~180
         *           水平向右为0度，水平向左为180度或-180度，下方为正数，上方为负数，顺时针旋转
         * 返 回 值：指定点是否在指定角度内部，1：在内部，0：不在内部
         */
        uint8_t IsInAngle(int16_t X, int16_t Y, int16_t StartAngle, int16_t EndAngle)
        {
            int16_t PointAngle;
            PointAngle = atan2(Y, X) / 3.14 * 180; // 计算指定点的弧度，并转换为角度表示
            if (StartAngle < EndAngle)             // 起始角度小于终止角度的情况
            {
                /*如果指定角度在起始终止角度之间，则判定指定点在指定角度*/
                if (PointAngle >= StartAngle && PointAngle <= EndAngle)
                {
                    return 1;
                }
            }
            else // 起始角度大于于终止角度的情况
            {
                /*如果指定角度大于起始角度或者小于终止角度，则判定指定点在指定角度*/
                if (PointAngle >= StartAngle || PointAngle <= EndAngle)
                {
                    return 1;
                }
            }
            return 0; // 不满足以上条件，则判断判定指定点不在指定角度
        }

        /*********************工具函数*/

        /*功能函数*********************/

        /**
         * 函    数：将OLED显存数组更新到OLED屏幕
         * 参    数：无
         * 返 回 值：无
         * 说    明：所有的显示函数，都只是对OLED显存数组进行读写
         *           随后调用Update函数或UpdateArea函数
         *           才会将显存数组的数据发送到OLED硬件，进行显示
         *           故调用显示函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void Update(void)
        {
            uint8_t j;
            /*遍历每一页*/
            for (j = 0; j < 8; j++)
            {
                /*设置光标位置为每一页的第一列*/
                SetCursor(j, 0);
                /*连续写入128个数据，将显存数组的数据写入到OLED硬件*/
                WriteData(DisplayBuf[j], 128);
            }
        }

        /**
         * 函    数：将OLED显存数组部分更新到OLED屏幕
         * 参    数：X 指定区域左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定区域左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Width 指定区域的宽度，范围：0~128
         * 参    数：Height 指定区域的高度，范围：0~64
         * 返 回 值：无
         * 说    明：此函数会至少更新参数指定的区域
         *           如果更新区域Y轴只包含部分页，则同一页的剩余部分会跟随一起更新
         * 说    明：所有的显示函数，都只是对OLED显存数组进行读写
         *           随后调用Update函数或UpdateArea函数
         *           才会将显存数组的数据发送到OLED硬件，进行显示
         *           故调用显示函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void UpdateArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height)
        {
            int16_t j;
            int16_t Page, Page1;

            /*负数坐标在计算页地址时需要加一个偏移*/
            /*(Y + Height - 1) / 8 + 1的目的是(Y + Height) / 8并向上取整*/
            Page = Y / 8;
            Page1 = (Y + Height - 1) / 8 + 1;
            if (Y < 0)
            {
                Page -= 1;
                Page1 -= 1;
            }

            /*遍历指定区域涉及的相关页*/
            for (j = Page; j < Page1; j++)
            {
                if (X >= 0 && X <= 127 && j >= 0 && j <= 7) // 超出屏幕的内容不显示
                {
                    /*设置光标位置为相关页的指定列*/
                    SetCursor(j, X);
                    /*连续写入Width个数据，将显存数组的数据写入到OLED硬件*/
                    WriteData(&DisplayBuf[j][X], Width);
                }
            }
        }

        /**
         * 函    数：将OLED显存数组全部清零
         * 参    数：无
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void Clear(void)
        {
            uint8_t i, j;
            for (j = 0; j < 8; j++) // 遍历8页
            {
                for (i = 0; i < 128; i++) // 遍历128列
                {
                    DisplayBuf[j][i] = 0x00; // 将显存数组数据全部清零
                }
            }
        }

        /**
         * 函    数：将OLED显存数组部分清零
         * 参    数：X 指定区域左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定区域左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Width 指定区域的宽度，范围：0~128
         * 参    数：Height 指定区域的高度，范围：0~64
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height)
        {
            int16_t i, j;

            for (j = Y; j < Y + Height; j++) // 遍历指定页
            {
                for (i = X; i < X + Width; i++) // 遍历指定列
                {
                    if (i >= 0 && i <= 127 && j >= 0 && j <= 63) // 超出屏幕的内容不显示
                    {
                        DisplayBuf[j / 8][i] &= ~(0x01 << (j % 8)); // 将显存数组指定数据清零
                    }
                }
            }
        }

        /**
         * 函    数：将OLED显存数组全部取反
         * 参    数：无
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void Reverse(void)
        {
            uint8_t i, j;
            for (j = 0; j < 8; j++) // 遍历8页
            {
                for (i = 0; i < 128; i++) // 遍历128列
                {
                    DisplayBuf[j][i] ^= 0xFF; // 将显存数组数据全部取反
                }
            }
        }

        /**
         * 函    数：将OLED显存数组部分取反
         * 参    数：X 指定区域左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定区域左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Width 指定区域的宽度，范围：0~128
         * 参    数：Height 指定区域的高度，范围：0~64
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void ReverseArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height)
        {
            int16_t i, j;

            for (j = Y; j < Y + Height; j++) // 遍历指定页
            {
                for (i = X; i < X + Width; i++) // 遍历指定列
                {
                    if (i >= 0 && i <= 127 && j >= 0 && j <= 63) // 超出屏幕的内容不显示
                    {
                        DisplayBuf[j / 8][i] ^= 0x01 << (j % 8); // 将显存数组指定数据取反
                    }
                }
            }
        }

        /**
         * 函    数：OLED显示一个字符
         * 参    数：X 指定字符左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定字符左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Char 指定要显示的字符，范围：ASCII码可见字符
         * 参    数：FontSize 指定字体大小
         *           范围：8X16		宽8像素，高16像素
         *                 6X8		宽6像素，高8像素
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize)
        {
            if (FontSize == OLED_8X16) // 字体为宽8像素，高16像素
            {
                /*将ASCII字模库F8x16的指定数据以8*16的图像格式显示*/
                ShowImage(X, Y, 8, 16, OLED_F8x16[Char - ' ']);
            }
            else if (FontSize == OLED_6X8) // 字体为宽6像素，高8像素
            {
                /*将ASCII字模库F6x8的指定数据以6*8的图像格式显示*/
                ShowImage(X, Y, 6, 8, OLED_F6x8[Char - ' ']);
            }
        }

        /**
         * 函    数：OLED显示字符串（支持ASCII码和中文混合写入）
         * 参    数：X 指定字符串左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定字符串左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：String 指定要显示的字符串，范围：ASCII码可见字符或中文字符组成的字符串
         * 参    数：FontSize 指定字体大小
         *           范围：8X16		宽8像素，高16像素
         *                 6X8		宽6像素，高8像素
         * 返 回 值：无
         * 说    明：显示的中文字符需要在Data.c里的CF16x16数组定义
         *           未找到指定中文字符时，会显示默认图形（一个方框，内部一个问号）
         *           当字体大小为8X16时，中文字符以16*16点阵正常显示
         *           当字体大小为6X8时，中文字符以6*8点阵显示'?'
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void ShowString(int16_t X, int16_t Y, char *String, uint8_t FontSize)
        {
            uint16_t i = 0;
            char SingleChar[5];
            uint8_t CharLength = 0;
            uint16_t XOffset = 0;
            uint16_t pIndex;

            while (String[i] != '\0') // 遍历字符串
            {

#ifdef CHARSET_UTF8 // 定义字符集为UTF8
                /*此段代码的目的是，提取UTF8字符串中的一个字符，转存到SingleChar子字符串中*/
                /*判断UTF8编码第一个字节的标志位*/
                if ((String[i] & 0x80) == 0x00) // 第一个字节为0xxxxxxx
                {
                    CharLength = 1;              // 字符为1字节
                    SingleChar[0] = String[i++]; // 将第一个字节写入SingleChar第0个位置，随后i指向下一个字节
                    SingleChar[1] = '\0';        // 为SingleChar添加字符串结束标志位
                }
                else if ((String[i] & 0xE0) == 0xC0) // 第一个字节为110xxxxx
                {
                    CharLength = 2;              // 字符为2字节
                    SingleChar[0] = String[i++]; // 将第一个字节写入SingleChar第0个位置，随后i指向下一个字节
                    if (String[i] == '\0')
                    {
                        break;
                    } // 意外情况，跳出循环，结束显示
                    SingleChar[1] = String[i++]; // 将第二个字节写入SingleChar第1个位置，随后i指向下一个字节
                    SingleChar[2] = '\0';        // 为SingleChar添加字符串结束标志位
                }
                else if ((String[i] & 0xF0) == 0xE0) // 第一个字节为1110xxxx
                {
                    CharLength = 3; // 字符为3字节
                    SingleChar[0] = String[i++];
                    if (String[i] == '\0')
                    {
                        break;
                    }
                    SingleChar[1] = String[i++];
                    if (String[i] == '\0')
                    {
                        break;
                    }
                    SingleChar[2] = String[i++];
                    SingleChar[3] = '\0';
                }
                else if ((String[i] & 0xF8) == 0xF0) // 第一个字节为11110xxx
                {
                    CharLength = 4; // 字符为4字节
                    SingleChar[0] = String[i++];
                    if (String[i] == '\0')
                    {
                        break;
                    }
                    SingleChar[1] = String[i++];
                    if (String[i] == '\0')
                    {
                        break;
                    }
                    SingleChar[2] = String[i++];
                    if (String[i] == '\0')
                    {
                        break;
                    }
                    SingleChar[3] = String[i++];
                    SingleChar[4] = '\0';
                }
                else
                {
                    i++; // 意外情况，i指向下一个字节，忽略此字节，继续判断下一个字节
                    continue;
                }
#endif

#ifdef CHARSET_GB2312 // 定义字符集为GB2312
                /*此段代码的目的是，提取GB2312字符串中的一个字符，转存到SingleChar子字符串中*/
                /*判断GB2312字节的最高位标志位*/
                if ((String[i] & 0x80) == 0x00) // 最高位为0
                {
                    CharLength = 1;              // 字符为1字节
                    SingleChar[0] = String[i++]; // 将第一个字节写入SingleChar第0个位置，随后i指向下一个字节
                    SingleChar[1] = '\0';        // 为SingleChar添加字符串结束标志位
                }
                else // 最高位为1
                {
                    CharLength = 2;              // 字符为2字节
                    SingleChar[0] = String[i++]; // 将第一个字节写入SingleChar第0个位置，随后i指向下一个字节
                    if (String[i] == '\0')
                    {
                        break;
                    } // 意外情况，跳出循环，结束显示
                    SingleChar[1] = String[i++]; // 将第二个字节写入SingleChar第1个位置，随后i指向下一个字节
                    SingleChar[2] = '\0';        // 为SingleChar添加字符串结束标志位
                }
#endif

                /*显示上述代码提取到的SingleChar*/
                if (CharLength == 1) // 如果是单字节字符
                {
                    /*使用ShowChar显示此字符*/
                    ShowChar(X + XOffset, Y, SingleChar[0], FontSize);
                    XOffset += FontSize;
                }
                else // 否则，即多字节字符
                {
                    /*遍历整个字模库，从字模库中寻找此字符的数据*/
                    /*如果找到最后一个字符（定义为空字符串），则表示字符未在字模库定义，停止寻找*/
                    for (pIndex = 0; strcmp(OLED_CF16x16[pIndex].Index, "") != 0; pIndex++)
                    {
                        /*找到匹配的字符*/
                        if (strcmp(OLED_CF16x16[pIndex].Index, SingleChar) == 0)
                        {
                            break; // 跳出循环，此时pIndex的值为指定字符的索引
                        }
                    }
                    if (FontSize == OLED_8X16) // 给定字体为8*16点阵
                    {
                        /*将字模库CF16x16的指定数据以16*16的图像格式显示*/
                        ShowImage(X + XOffset, Y, 16, 16, OLED_CF16x16[pIndex].Data);
                        XOffset += 16;
                    }
                    else if (FontSize == OLED_6X8) // 给定字体为6*8点阵
                    {
                        /*空间不足，此位置显示'?'*/
                        ShowChar(X + XOffset, Y, '?', OLED_6X8);
                        XOffset += OLED_6X8;
                    }
                }
            }
        }

        /**
         * 函    数：OLED显示数字（十进制，正整数）
         * 参    数：X 指定数字左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定数字左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Number 指定要显示的数字，范围：0~4294967295
         * 参    数：Length 指定数字的长度，范围：0~10
         * 参    数：FontSize 指定字体大小
         *           范围：8X16		宽8像素，高16像素
         *                 6X8		宽6像素，高8像素
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
        {
            uint8_t i;
            for (i = 0; i < Length; i++) // 遍历数字的每一位
            {
                /*调用ShowChar函数，依次显示每个数字*/
                /*Number / Pow(10, Length - i - 1) % 10 可以十进制提取数字的每一位*/
                /*+ '0' 可将数字转换为字符格式*/
                ShowChar(X + i * FontSize, Y, Number / Pow(10, Length - i - 1) % 10 + '0', FontSize);
            }
        }

        /**
         * 函    数：OLED显示有符号数字（十进制，整数）
         * 参    数：X 指定数字左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定数字左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Number 指定要显示的数字，范围：-2147483648~2147483647
         * 参    数：Length 指定数字的长度，范围：0~10
         * 参    数：FontSize 指定字体大小
         *           范围：8X16		宽8像素，高16像素
         *                 6X8		宽6像素，高8像素
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize)
        {
            uint8_t i;
            uint32_t Number1;

            if (Number >= 0) // 数字大于等于0
            {
                ShowChar(X, Y, '+', FontSize); // 显示+号
                Number1 = Number;              // Number1直接等于Number
            }
            else // 数字小于0
            {
                ShowChar(X, Y, '-', FontSize); // 显示-号
                Number1 = -Number;             // Number1等于Number取负
            }

            for (i = 0; i < Length; i++) // 遍历数字的每一位
            {
                /*调用ShowChar函数，依次显示每个数字*/
                /*Number1 / Pow(10, Length - i - 1) % 10 可以十进制提取数字的每一位*/
                /*+ '0' 可将数字转换为字符格式*/
                ShowChar(X + (i + 1) * FontSize, Y, Number1 / Pow(10, Length - i - 1) % 10 + '0', FontSize);
            }
        }

        /**
         * 函    数：OLED显示十六进制数字（十六进制，正整数）
         * 参    数：X 指定数字左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定数字左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Number 指定要显示的数字，范围：0x00000000~0xFFFFFFFF
         * 参    数：Length 指定数字的长度，范围：0~8
         * 参    数：FontSize 指定字体大小
         *           范围：8X16		宽8像素，高16像素
         *                 6X8		宽6像素，高8像素
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
        {
            uint8_t i, SingleNumber;
            for (i = 0; i < Length; i++) // 遍历数字的每一位
            {
                /*以十六进制提取数字的每一位*/
                SingleNumber = Number / Pow(16, Length - i - 1) % 16;

                if (SingleNumber < 10) // 单个数字小于10
                {
                    /*调用ShowChar函数，显示此数字*/
                    /*+ '0' 可将数字转换为字符格式*/
                    ShowChar(X + i * FontSize, Y, SingleNumber + '0', FontSize);
                }
                else // 单个数字大于10
                {
                    /*调用ShowChar函数，显示此数字*/
                    /*+ 'A' 可将数字转换为从A开始的十六进制字符*/
                    ShowChar(X + i * FontSize, Y, SingleNumber - 10 + 'A', FontSize);
                }
            }
        }

        /**
         * 函    数：OLED显示二进制数字（二进制，正整数）
         * 参    数：X 指定数字左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定数字左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Number 指定要显示的数字，范围：0x00000000~0xFFFFFFFF
         * 参    数：Length 指定数字的长度，范围：0~16
         * 参    数：FontSize 指定字体大小
         *           范围：8X16		宽8像素，高16像素
         *                 6X8		宽6像素，高8像素
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
        {
            uint8_t i;
            for (i = 0; i < Length; i++) // 遍历数字的每一位
            {
                /*调用ShowChar函数，依次显示每个数字*/
                /*Number / Pow(2, Length - i - 1) % 2 可以二进制提取数字的每一位*/
                /*+ '0' 可将数字转换为字符格式*/
                ShowChar(X + i * FontSize, Y, Number / Pow(2, Length - i - 1) % 2 + '0', FontSize);
            }
        }

        /**
         * 函    数：OLED显示浮点数字（十进制，小数）
         * 参    数：X 指定数字左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定数字左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Number 指定要显示的数字，范围：-4294967295.0~4294967295.0
         * 参    数：IntLength 指定数字的整数位长度，范围：0~10
         * 参    数：FraLength 指定数字的小数位长度，范围：0~9，小数进行四舍五入显示
         * 参    数：FontSize 指定字体大小
         *           范围：8X16		宽8像素，高16像素
         *                 6X8		宽6像素，高8像素
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize)
        {
            uint32_t PowNum, IntNum, FraNum;

            if (Number >= 0) // 数字大于等于0
            {
                ShowChar(X, Y, '+', FontSize); // 显示+号
            }
            else // 数字小于0
            {
                ShowChar(X, Y, '-', FontSize); // 显示-号
                Number = -Number;              // Number取负
            }

            /*提取整数部分和小数部分*/
            IntNum = Number;                 // 直接赋值给整型变量，提取整数
            Number -= IntNum;                // 将Number的整数减掉，防止之后将小数乘到整数时因数过大造成错误
            PowNum = Pow(10, FraLength);     // 根据指定小数的位数，确定乘数
            FraNum = round(Number * PowNum); // 将小数乘到整数，同时四舍五入，避免显示误差
            IntNum += FraNum / PowNum;       // 若四舍五入造成了进位，则需要再加给整数

            /*显示整数部分*/
            ShowNum(X + FontSize, Y, IntNum, IntLength, FontSize);

            /*显示小数点*/
            ShowChar(X + (IntLength + 1) * FontSize, Y, '.', FontSize);

            /*显示小数部分*/
            ShowNum(X + (IntLength + 2) * FontSize, Y, FraNum, FraLength, FontSize);
        }

        /**
         * 函    数：OLED显示图像
         * 参    数：X 指定图像左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定图像左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Width 指定图像的宽度，范围：0~128
         * 参    数：Height 指定图像的高度，范围：0~64
         * 参    数：Image 指定要显示的图像
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image)
        {
            uint8_t i = 0, j = 0;
            int16_t Page, Shift;

            /*将图像所在区域清空*/
            ClearArea(X, Y, Width, Height);

            /*遍历指定图像涉及的相关页*/
            /*(Height - 1) / 8 + 1的目的是Height / 8并向上取整*/
            for (j = 0; j < (Height - 1) / 8 + 1; j++)
            {
                /*遍历指定图像涉及的相关列*/
                for (i = 0; i < Width; i++)
                {
                    if (X + i >= 0 && X + i <= 127) // 超出屏幕的内容不显示
                    {
                        /*负数坐标在计算页地址和移位时需要加一个偏移*/
                        Page = Y / 8;
                        Shift = Y % 8;
                        if (Y < 0)
                        {
                            Page -= 1;
                            Shift += 8;
                        }

                        if (Page + j >= 0 && Page + j <= 7) // 超出屏幕的内容不显示
                        {
                            /*显示图像在当前页的内容*/
                            DisplayBuf[Page + j][X + i] |= Image[j * Width + i] << (Shift);
                        }

                        if (Page + j + 1 >= 0 && Page + j + 1 <= 7) // 超出屏幕的内容不显示
                        {
                            /*显示图像在下一页的内容*/
                            DisplayBuf[Page + j + 1][X + i] |= Image[j * Width + i] >> (8 - Shift);
                        }
                    }
                }
            }
        }

        /**
         * 函    数：OLED使用printf函数打印格式化字符串（支持ASCII码和中文混合写入）
         * 参    数：X 指定格式化字符串左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定格式化字符串左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：FontSize 指定字体大小
         *           范围：8X16		宽8像素，高16像素
         *                 6X8		宽6像素，高8像素
         * 参    数：format 指定要显示的格式化字符串，范围：ASCII码可见字符或中文字符组成的字符串
         * 参    数：... 格式化字符串参数列表
         * 返 回 值：无
         * 说    明：显示的中文字符需要在Data.c里的CF16x16数组定义
         *           未找到指定中文字符时，会显示默认图形（一个方框，内部一个问号）
         *           当字体大小为8X16时，中文字符以16*16点阵正常显示
         *           当字体大小为6X8时，中文字符以6*8点阵显示'?'
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void Printf(int16_t X, int16_t Y, uint8_t FontSize, char *format, ...)
        {
            char String[256];                   // 定义字符数组
            va_list arg;                        // 定义可变参数列表数据类型的变量arg
            va_start(arg, format);              // 从format开始，接收参数列表到arg变量
            vsprintf(String, format, arg);      // 使用vsprintf打印格式化字符串和参数列表到字符数组中
            va_end(arg);                        // 结束变量arg
            ShowString(X, Y, String, FontSize); // OLED显示字符数组（字符串）
        }

        /**
         * 函    数：OLED在指定位置画一个点
         * 参    数：X 指定点的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定点的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void DrawPoint(int16_t X, int16_t Y)
        {
            if (X >= 0 && X <= 127 && Y >= 0 && Y <= 63) // 超出屏幕的内容不显示
            {
                /*将显存数组指定位置的一个Bit数据置1*/
                DisplayBuf[Y / 8][X] |= 0x01 << (Y % 8);
            }
        }

        /**
         * 函    数：OLED获取指定位置点的值
         * 参    数：X 指定点的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定点的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 返 回 值：指定位置点是否处于点亮状态，1：点亮，0：熄灭
         */
        uint8_t GetPoint(int16_t X, int16_t Y)
        {
            if (X >= 0 && X <= 127 && Y >= 0 && Y <= 63) // 超出屏幕的内容不读取
            {
                /*判断指定位置的数据*/
                if (DisplayBuf[Y / 8][X] & 0x01 << (Y % 8))
                {
                    return 1; // 为1，返回1
                }
            }

            return 0; // 否则，返回0
        }

        /**
         * 函    数：OLED画线
         * 参    数：X0 指定一个端点的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y0 指定一个端点的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：X1 指定另一个端点的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y1 指定另一个端点的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1)
        {
            int16_t x, y, dx, dy, d, incrE, incrNE, temp;
            int16_t x0 = X0, y0 = Y0, x1 = X1, y1 = Y1;
            uint8_t yflag = 0, xyflag = 0;

            if (y0 == y1) // 横线单独处理
            {
                /*0号点X坐标大于1号点X坐标，则交换两点X坐标*/
                if (x0 > x1)
                {
                    temp = x0;
                    x0 = x1;
                    x1 = temp;
                }

                /*遍历X坐标*/
                for (x = x0; x <= x1; x++)
                {
                    DrawPoint(x, y0); // 依次画点
                }
            }
            else if (x0 == x1) // 竖线单独处理
            {
                /*0号点Y坐标大于1号点Y坐标，则交换两点Y坐标*/
                if (y0 > y1)
                {
                    temp = y0;
                    y0 = y1;
                    y1 = temp;
                }

                /*遍历Y坐标*/
                for (y = y0; y <= y1; y++)
                {
                    DrawPoint(x0, y); // 依次画点
                }
            }
            else // 斜线
            {
                /*使用Bresenham算法画直线，可以避免耗时的浮点运算，效率更高*/
                /*参考文档：https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
                /*参考教程：https://www.bilibili.com/video/BV1364y1d7Lo*/

                if (x0 > x1) // 0号点X坐标大于1号点X坐标
                {
                    /*交换两点坐标*/
                    /*交换后不影响画线，但是画线方向由第一、二、三、四象限变为第一、四象限*/
                    temp = x0;
                    x0 = x1;
                    x1 = temp;
                    temp = y0;
                    y0 = y1;
                    y1 = temp;
                }

                if (y0 > y1) // 0号点Y坐标大于1号点Y坐标
                {
                    /*将Y坐标取负*/
                    /*取负后影响画线，但是画线方向由第一、四象限变为第一象限*/
                    y0 = -y0;
                    y1 = -y1;

                    /*置标志位yflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
                    yflag = 1;
                }

                if (y1 - y0 > x1 - x0) // 画线斜率大于1
                {
                    /*将X坐标与Y坐标互换*/
                    /*互换后影响画线，但是画线方向由第一象限0~90度范围变为第一象限0~45度范围*/
                    temp = x0;
                    x0 = y0;
                    y0 = temp;
                    temp = x1;
                    x1 = y1;
                    y1 = temp;

                    /*置标志位xyflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
                    xyflag = 1;
                }

                /*以下为Bresenham算法画直线*/
                /*算法要求，画线方向必须为第一象限0~45度范围*/
                dx = x1 - x0;
                dy = y1 - y0;
                incrE = 2 * dy;
                incrNE = 2 * (dy - dx);
                d = 2 * dy - dx;
                x = x0;
                y = y0;

                /*画起始点，同时判断标志位，将坐标换回来*/
                if (yflag && xyflag)
                {
                    DrawPoint(y, -x);
                }
                else if (yflag)
                {
                    DrawPoint(x, -y);
                }
                else if (xyflag)
                {
                    DrawPoint(y, x);
                }
                else
                {
                    DrawPoint(x, y);
                }

                while (x < x1) // 遍历X轴的每个点
                {
                    x++;
                    if (d < 0) // 下一个点在当前点东方
                    {
                        d += incrE;
                    }
                    else // 下一个点在当前点东北方
                    {
                        y++;
                        d += incrNE;
                    }

                    /*画每一个点，同时判断标志位，将坐标换回来*/
                    if (yflag && xyflag)
                    {
                        DrawPoint(y, -x);
                    }
                    else if (yflag)
                    {
                        DrawPoint(x, -y);
                    }
                    else if (xyflag)
                    {
                        DrawPoint(y, x);
                    }
                    else
                    {
                        DrawPoint(x, y);
                    }
                }
            }
        }

        /**
         * 函    数：OLED矩形
         * 参    数：X 指定矩形左上角的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定矩形左上角的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Width 指定矩形的宽度，范围：0~128
         * 参    数：Height 指定矩形的高度，范围：0~64
         * 参    数：IsFilled 指定矩形是否填充
         *           范围：UNFILLED		不填充
         *                 FILLED			填充
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void DrawRectangle(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled)
        {
            int16_t i, j;
            if (!IsFilled) // 指定矩形不填充
            {
                /*遍历上下X坐标，画矩形上下两条线*/
                for (i = X; i < X + Width; i++)
                {
                    DrawPoint(i, Y);
                    DrawPoint(i, Y + Height - 1);
                }
                /*遍历左右Y坐标，画矩形左右两条线*/
                for (i = Y; i < Y + Height; i++)
                {
                    DrawPoint(X, i);
                    DrawPoint(X + Width - 1, i);
                }
            }
            else // 指定矩形填充
            {
                /*遍历X坐标*/
                for (i = X; i < X + Width; i++)
                {
                    /*遍历Y坐标*/
                    for (j = Y; j < Y + Height; j++)
                    {
                        /*在指定区域画点，填充满矩形*/
                        DrawPoint(i, j);
                    }
                }
            }
        }

        /**
         * 函    数：OLED三角形
         * 参    数：X0 指定第一个端点的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y0 指定第一个端点的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：X1 指定第二个端点的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y1 指定第二个端点的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：X2 指定第三个端点的横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y2 指定第三个端点的纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：IsFilled 指定三角形是否填充
         *           范围：UNFILLED		不填充
         *                 FILLED			填充
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled)
        {
            int16_t minx = X0, miny = Y0, maxx = X0, maxy = Y0;
            int16_t i, j;
            int16_t vx[] = {X0, X1, X2};
            int16_t vy[] = {Y0, Y1, Y2};

            if (!IsFilled) // 指定三角形不填充
            {
                /*调用画线函数，将三个点用直线连接*/
                DrawLine(X0, Y0, X1, Y1);
                DrawLine(X0, Y0, X2, Y2);
                DrawLine(X1, Y1, X2, Y2);
            }
            else // 指定三角形填充
            {
                /*找到三个点最小的X、Y坐标*/
                if (X1 < minx)
                {
                    minx = X1;
                }
                if (X2 < minx)
                {
                    minx = X2;
                }
                if (Y1 < miny)
                {
                    miny = Y1;
                }
                if (Y2 < miny)
                {
                    miny = Y2;
                }

                /*找到三个点最大的X、Y坐标*/
                if (X1 > maxx)
                {
                    maxx = X1;
                }
                if (X2 > maxx)
                {
                    maxx = X2;
                }
                if (Y1 > maxy)
                {
                    maxy = Y1;
                }
                if (Y2 > maxy)
                {
                    maxy = Y2;
                }

                /*最小最大坐标之间的矩形为可能需要填充的区域*/
                /*遍历此区域中所有的点*/
                /*遍历X坐标*/
                for (i = minx; i <= maxx; i++)
                {
                    /*遍历Y坐标*/
                    for (j = miny; j <= maxy; j++)
                    {
                        /*调用pnpoly，判断指定点是否在指定三角形之中*/
                        /*如果在，则画点，如果不在，则不做处理*/
                        if (pnpoly(3, vx, vy, i, j))
                        {
                            DrawPoint(i, j);
                        }
                    }
                }
            }
        }

        /**
         * 函    数：OLED画圆
         * 参    数：X 指定圆的圆心横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定圆的圆心纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Radius 指定圆的半径，范围：0~255
         * 参    数：IsFilled 指定圆是否填充
         *           范围：UNFILLED		不填充
         *                 FILLED			填充
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void DrawCircle(int16_t X, int16_t Y, uint8_t Radius, uint8_t IsFilled)
        {
            int16_t x, y, d, j;

            /*使用Bresenham算法画圆，可以避免耗时的浮点运算，效率更高*/
            /*参考文档：https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
            /*参考教程：https://www.bilibili.com/video/BV1VM4y1u7wJ*/

            d = 1 - Radius;
            x = 0;
            y = Radius;

            /*画每个八分之一圆弧的起始点*/
            DrawPoint(X + x, Y + y);
            DrawPoint(X - x, Y - y);
            DrawPoint(X + y, Y + x);
            DrawPoint(X - y, Y - x);

            if (IsFilled) // 指定圆填充
            {
                /*遍历起始点Y坐标*/
                for (j = -y; j < y; j++)
                {
                    /*在指定区域画点，填充部分圆*/
                    DrawPoint(X, Y + j);
                }
            }

            while (x < y) // 遍历X轴的每个点
            {
                x++;
                if (d < 0) // 下一个点在当前点东方
                {
                    d += 2 * x + 1;
                }
                else // 下一个点在当前点东南方
                {
                    y--;
                    d += 2 * (x - y) + 1;
                }

                /*画每个八分之一圆弧的点*/
                DrawPoint(X + x, Y + y);
                DrawPoint(X + y, Y + x);
                DrawPoint(X - x, Y - y);
                DrawPoint(X - y, Y - x);
                DrawPoint(X + x, Y - y);
                DrawPoint(X + y, Y - x);
                DrawPoint(X - x, Y + y);
                DrawPoint(X - y, Y + x);

                if (IsFilled) // 指定圆填充
                {
                    /*遍历中间部分*/
                    for (j = -y; j < y; j++)
                    {
                        /*在指定区域画点，填充部分圆*/
                        DrawPoint(X + x, Y + j);
                        DrawPoint(X - x, Y + j);
                    }

                    /*遍历两侧部分*/
                    for (j = -x; j < x; j++)
                    {
                        /*在指定区域画点，填充部分圆*/
                        DrawPoint(X - y, Y + j);
                        DrawPoint(X + y, Y + j);
                    }
                }
            }
        }

        /**
         * 函    数：OLED画椭圆
         * 参    数：X 指定椭圆的圆心横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定椭圆的圆心纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：A 指定椭圆的横向半轴长度，范围：0~255
         * 参    数：B 指定椭圆的纵向半轴长度，范围：0~255
         * 参    数：IsFilled 指定椭圆是否填充
         *           范围：UNFILLED		不填充
         *                 FILLED			填充
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void DrawEllipse(int16_t X, int16_t Y, uint8_t A, uint8_t B, uint8_t IsFilled)
        {
            int16_t x, y, j;
            int16_t a = A, b = B;
            float d1, d2;

            /*使用Bresenham算法画椭圆，可以避免部分耗时的浮点运算，效率更高*/
            /*参考链接：https://blog.csdn.net/myf_666/article/details/128167392*/

            x = 0;
            y = b;
            d1 = b * b + a * a * (-b + 0.5);

            if (IsFilled) // 指定椭圆填充
            {
                /*遍历起始点Y坐标*/
                for (j = -y; j < y; j++)
                {
                    /*在指定区域画点，填充部分椭圆*/
                    DrawPoint(X, Y + j);
                    DrawPoint(X, Y + j);
                }
            }

            /*画椭圆弧的起始点*/
            DrawPoint(X + x, Y + y);
            DrawPoint(X - x, Y - y);
            DrawPoint(X - x, Y + y);
            DrawPoint(X + x, Y - y);

            /*画椭圆中间部分*/
            while (b * b * (x + 1) < a * a * (y - 0.5))
            {
                if (d1 <= 0) // 下一个点在当前点东方
                {
                    d1 += b * b * (2 * x + 3);
                }
                else // 下一个点在当前点东南方
                {
                    d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
                    y--;
                }
                x++;

                if (IsFilled) // 指定椭圆填充
                {
                    /*遍历中间部分*/
                    for (j = -y; j < y; j++)
                    {
                        /*在指定区域画点，填充部分椭圆*/
                        DrawPoint(X + x, Y + j);
                        DrawPoint(X - x, Y + j);
                    }
                }

                /*画椭圆中间部分圆弧*/
                DrawPoint(X + x, Y + y);
                DrawPoint(X - x, Y - y);
                DrawPoint(X - x, Y + y);
                DrawPoint(X + x, Y - y);
            }

            /*画椭圆两侧部分*/
            d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;

            while (y > 0)
            {
                if (d2 <= 0) // 下一个点在当前点东方
                {
                    d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
                    x++;
                }
                else // 下一个点在当前点东南方
                {
                    d2 += a * a * (-2 * y + 3);
                }
                y--;

                if (IsFilled) // 指定椭圆填充
                {
                    /*遍历两侧部分*/
                    for (j = -y; j < y; j++)
                    {
                        /*在指定区域画点，填充部分椭圆*/
                        DrawPoint(X + x, Y + j);
                        DrawPoint(X - x, Y + j);
                    }
                }

                /*画椭圆两侧部分圆弧*/
                DrawPoint(X + x, Y + y);
                DrawPoint(X - x, Y - y);
                DrawPoint(X - x, Y + y);
                DrawPoint(X + x, Y - y);
            }
        }

        /**
         * 函    数：OLED画圆弧
         * 参    数：X 指定圆弧的圆心横坐标，范围：-32768~32767，屏幕区域：0~127
         * 参    数：Y 指定圆弧的圆心纵坐标，范围：-32768~32767，屏幕区域：0~63
         * 参    数：Radius 指定圆弧的半径，范围：0~255
         * 参    数：StartAngle 指定圆弧的起始角度，范围：-180~180
         *           水平向右为0度，水平向左为180度或-180度，下方为正数，上方为负数，顺时针旋转
         * 参    数：EndAngle 指定圆弧的终止角度，范围：-180~180
         *           水平向右为0度，水平向左为180度或-180度，下方为正数，上方为负数，顺时针旋转
         * 参    数：IsFilled 指定圆弧是否填充，填充后为扇形
         *           范围：UNFILLED		不填充
         *                 FILLED			填充
         * 返 回 值：无
         * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
         */
        void DrawArc(int16_t X, int16_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled)
        {
            int16_t x, y, d, j;

            /*此函数借用Bresenham算法画圆的方法*/

            d = 1 - Radius;
            x = 0;
            y = Radius;

            /*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
            if (IsInAngle(x, y, StartAngle, EndAngle))
            {
                DrawPoint(X + x, Y + y);
            }
            if (IsInAngle(-x, -y, StartAngle, EndAngle))
            {
                DrawPoint(X - x, Y - y);
            }
            if (IsInAngle(y, x, StartAngle, EndAngle))
            {
                DrawPoint(X + y, Y + x);
            }
            if (IsInAngle(-y, -x, StartAngle, EndAngle))
            {
                DrawPoint(X - y, Y - x);
            }

            if (IsFilled) // 指定圆弧填充
            {
                /*遍历起始点Y坐标*/
                for (j = -y; j < y; j++)
                {
                    /*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
                    if (IsInAngle(0, j, StartAngle, EndAngle))
                    {
                        DrawPoint(X, Y + j);
                    }
                }
            }

            while (x < y) // 遍历X轴的每个点
            {
                x++;
                if (d < 0) // 下一个点在当前点东方
                {
                    d += 2 * x + 1;
                }
                else // 下一个点在当前点东南方
                {
                    y--;
                    d += 2 * (x - y) + 1;
                }

                /*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
                if (IsInAngle(x, y, StartAngle, EndAngle))
                {
                    DrawPoint(X + x, Y + y);
                }
                if (IsInAngle(y, x, StartAngle, EndAngle))
                {
                    DrawPoint(X + y, Y + x);
                }
                if (IsInAngle(-x, -y, StartAngle, EndAngle))
                {
                    DrawPoint(X - x, Y - y);
                }
                if (IsInAngle(-y, -x, StartAngle, EndAngle))
                {
                    DrawPoint(X - y, Y - x);
                }
                if (IsInAngle(x, -y, StartAngle, EndAngle))
                {
                    DrawPoint(X + x, Y - y);
                }
                if (IsInAngle(y, -x, StartAngle, EndAngle))
                {
                    DrawPoint(X + y, Y - x);
                }
                if (IsInAngle(-x, y, StartAngle, EndAngle))
                {
                    DrawPoint(X - x, Y + y);
                }
                if (IsInAngle(-y, x, StartAngle, EndAngle))
                {
                    DrawPoint(X - y, Y + x);
                }

                if (IsFilled) // 指定圆弧填充
                {
                    /*遍历中间部分*/
                    for (j = -y; j < y; j++)
                    {
                        /*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
                        if (IsInAngle(x, j, StartAngle, EndAngle))
                        {
                            DrawPoint(X + x, Y + j);
                        }
                        if (IsInAngle(-x, j, StartAngle, EndAngle))
                        {
                            DrawPoint(X - x, Y + j);
                        }
                    }

                    /*遍历两侧部分*/
                    for (j = -x; j < x; j++)
                    {
                        /*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
                        if (IsInAngle(-y, j, StartAngle, EndAngle))
                        {
                            DrawPoint(X - y, Y + j);
                        }
                        if (IsInAngle(y, j, StartAngle, EndAngle))
                        {
                            DrawPoint(X + y, Y + j);
                        }
                    }
                }
            }
        }
    };
    /*********************功能函数*/

    /*****************江协科技|版权所有****************/
    /*****************jiangxiekeji.com*****************/
    class OLED_
    {
    private:
        // 封装的字体大小常量
        enum FontSize
        {
            FONT_6X8 = 6, // 对应OLED_6X8
            FONT_8X16 = 8 // 对应OLED_8X16
        };

        // 填充模式
        enum FillMode
        {
            UNFILLED = 0,
            FILLED = 1
        };

    public:
        // 构造函数 - 初始化OLED
        OLED_()
        {
            OLED_Init();
        }

        // 更新函数
        void Update()
        {
            OLED_Update();
        }

        void UpdateArea(int16_t x, int16_t y, uint8_t width, uint8_t height)
        {
            OLED_UpdateArea(x, y, width, height);
        }

        // 显存控制函数
        void Clear()
        {
            OLED_Clear();
        }

        void ClearArea(int16_t x, int16_t y, uint8_t width, uint8_t height)
        {
            OLED_ClearArea(x, y, width, height);
        }

        void Reverse()
        {
            OLED_Reverse();
        }

        void ReverseArea(int16_t x, int16_t y, uint8_t width, uint8_t height)
        {
            OLED_ReverseArea(x, y, width, height);
        }

        // 显示函数
        void ShowChar(int16_t x, int16_t y, char ch, uint8_t fontSize)
        {
            OLED_ShowChar(x, y, ch, fontSize);
        }

        void ShowString(int16_t x, int16_t y, const char *str, uint8_t fontSize)
        {
            // 注意：使用const修饰字符串参数，避免C++11警告
            OLED_ShowString(x, y, const_cast<char *>(str), fontSize);
        }

        void ShowNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize)
        {
            OLED_ShowNum(x, y, number, length, fontSize);
        }

        void ShowSignedNum(int16_t x, int16_t y, int32_t number, uint8_t length, uint8_t fontSize)
        {
            OLED_ShowSignedNum(x, y, number, length, fontSize);
        }

        void ShowHexNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize)
        {
            OLED_ShowHexNum(x, y, number, length, fontSize);
        }

        void ShowBinNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize)
        {
            OLED_ShowBinNum(x, y, number, length, fontSize);
        }

        void ShowFloatNum(int16_t x, int16_t y, double number, uint8_t intLength,
                          uint8_t fraLength, uint8_t fontSize)
        {
            OLED_ShowFloatNum(x, y, number, intLength, fraLength, fontSize);
        }

        void ShowImage(int16_t x, int16_t y, uint8_t width, uint8_t height, const uint8_t *image)
        {
            OLED_ShowImage(x, y, width, height, image);
        }

        void Printf(int16_t x, int16_t y, uint8_t fontSize, const char *format, ...)
        {
            va_list args;
            va_start(args, format);
            // 因为va_list不能直接传递，需要创建一个包装函数或在此处展开实现
            // 这里简化处理，只传递格式和参数列表给原始函数
            OLED_Printf(x, y, fontSize, const_cast<char *>(format), args);
            va_end(args);
        }

        // 绘图函数
        void DrawPoint(int16_t x, int16_t y)
        {
            OLED_DrawPoint(x, y);
        }

        bool GetPoint(int16_t x, int16_t y)
        {
            return OLED_GetPoint(x, y) != 0;
        }

        void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
        {
            OLED_DrawLine(x0, y0, x1, y1);
        }

        void DrawRectangle(int16_t x, int16_t y, uint8_t width, uint8_t height, bool filled = false)
        {
            OLED_DrawRectangle(x, y, width, height, filled ? FILLED : UNFILLED);
        }

        void DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                          int16_t x2, int16_t y2, bool filled = false)
        {
            OLED_DrawTriangle(x0, y0, x1, y1, x2, y2, filled ? FILLED : UNFILLED);
        }

        void DrawCircle(int16_t x, int16_t y, uint8_t radius, bool filled = false)
        {
            OLED_DrawCircle(x, y, radius, filled ? FILLED : UNFILLED);
        }

        void DrawEllipse(int16_t x, int16_t y, uint8_t a, uint8_t b, bool filled = false)
        {
            OLED_DrawEllipse(x, y, a, b, filled ? FILLED : UNFILLED);
        }

        void DrawArc(int16_t x, int16_t y, uint8_t radius,
                     int16_t startAngle, int16_t endAngle, bool filled = false)
        {
            OLED_DrawArc(x, y, radius, startAngle, endAngle, filled ? FILLED : UNFILLED);
        }

        // 常量定义 - 与OLED.h中的宏定义保持一致
        static constexpr uint8_t FONT_SIZE_6X8 = OLED_6X8;
        static constexpr uint8_t FONT_SIZE_8X16 = OLED_8X16;
    };
}; // namespace Device
