#include "stm32f10x.h"
// #include <vector>
class Port
{
public:
    static GPIO_TypeDef *PortA;
    static GPIO_TypeDef *PortB;
    static GPIO_TypeDef *PortC;
    static GPIO_TypeDef *PortD;
    static GPIO_TypeDef *PortE;
    static GPIO_TypeDef *PortF;
    static GPIO_TypeDef *PortG;
};
GPIO_TypeDef *Port::PortA = GPIOA;
GPIO_TypeDef *Port::PortB = GPIOB;
GPIO_TypeDef *Port::PortC = GPIOC;
GPIO_TypeDef *Port::PortD = GPIOD;
GPIO_TypeDef *Port::PortE = GPIOE;
GPIO_TypeDef *Port::PortF = GPIOF;
GPIO_TypeDef *Port::PortG = GPIOG;
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
        if (_port == Port::PortA)
            index = 0;
        else if (_port == Port::PortB)
            index = 1;
        else if (_port == Port::PortC)
            index = 2;
        else if (_port == Port::PortD)
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
        static void doInitPin(GPIO_TypeDef *port, uint16_t pin, GPIOMode_TypeDef mode)
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
            void Pin0(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_0, mode); }
            void Pin1(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_1, mode); }
            void Pin2(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_2, mode); }
            void Pin3(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_3, mode); }
            void Pin4(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_4, mode); }
            void Pin5(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_5, mode); }
            void Pin6(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_6, mode); }
            void Pin7(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_7, mode); }
            void Pin8(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_8, mode); }
            void Pin9(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_9, mode); }
            void Pin10(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_10, mode); }
            void Pin11(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_11, mode); }
            void Pin12(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_12, mode); }
            void Pin13(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_13, mode); }
            void Pin14(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_14, mode); }
            void Pin15(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_15, mode); }
        };
        Port_Init ProtA{Port::PortA};
        Port_Init ProtB{Port::PortB};
        Port_Init ProtC{Port::PortC};
        Port_Init ProtD{Port::PortD};
        Port_Init ProtE{Port::PortE};
        Port_Init ProtF{Port::PortF};
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
            void Pin0(uint8_t value) const { doWritePin(port, GPIO_Pin_0, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin1(uint8_t value) const { doWritePin(port, GPIO_Pin_1, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin2(uint8_t value) const { doWritePin(port, GPIO_Pin_2, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin3(uint8_t value) const { doWritePin(port, GPIO_Pin_3, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin4(uint8_t value) const { doWritePin(port, GPIO_Pin_4, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin5(uint8_t value) const { doWritePin(port, GPIO_Pin_5, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin6(uint8_t value) const { doWritePin(port, GPIO_Pin_6, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin7(uint8_t value) const { doWritePin(port, GPIO_Pin_7, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin8(uint8_t value) const { doWritePin(port, GPIO_Pin_8, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin9(uint8_t value) const { doWritePin(port, GPIO_Pin_9, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin10(uint8_t value) const { doWritePin(port, GPIO_Pin_10, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin11(uint8_t value) const { doWritePin(port, GPIO_Pin_11, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin12(uint8_t value) const { doWritePin(port, GPIO_Pin_12, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin13(uint8_t value) const { doWritePin(port, GPIO_Pin_13, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin14(uint8_t value) const { doWritePin(port, GPIO_Pin_14, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin15(uint8_t value) const { doWritePin(port, GPIO_Pin_15, value != 0 ? Bit_SET : Bit_RESET); }
        };
        Port_Write ProtA{Port::PortA};
        Port_Write ProtB{Port::PortB};
        Port_Write ProtC{Port::PortC};
        Port_Write ProtD{Port::PortD};
        Port_Write ProtE{Port::PortE};
        Port_Write ProtF{Port::PortF};
    } static write;

    class
    {
        Port port;
        static bool doReadPin(const GPIO_TypeDef *prot, uint16_t pin)
        {
            return GPIO_ReadInputDataBit(const_cast<GPIO_TypeDef *>(prot), pin) != 0;
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
        Port_read ProtA{Port::PortA};
        Port_read ProtB{Port::PortA};
        Port_read ProtC{Port::PortA};
        Port_read ProtD{Port::PortA};
        Port_read ProtE{Port::PortA};
        Port_read ProtF{Port::PortA};
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
uint16_t IO::used[3] = {0, 0, 0};

class Clock
{
public:
    class RccProt
    {
    public:
        static const uint32_t AFIO_RCC = ((uint32_t)0x00000001);
        static const uint32_t GPIOA_RCC = ((uint32_t)0x00000004);
        static const uint32_t GPIOB_RCC = ((uint32_t)0x00000008);
        static const uint32_t GPIOC_RCC = ((uint32_t)0x00000010);
        static const uint32_t GPIOD_RCC = ((uint32_t)0x00000020);
        static const uint32_t GPIOE_RCC = ((uint32_t)0x00000040);
        static const uint32_t GPIOF_RCC = ((uint32_t)0x00000080);
        static const uint32_t GPIOG_RCC = ((uint32_t)0x00000100);
        static const uint32_t ADC1_RCC = ((uint32_t)0x00000200);
        static const uint32_t ADC2_RCC = ((uint32_t)0x00000400);
        static const uint32_t Timer_1_RCC = ((uint32_t)0x00000800);
        static const uint32_t SPI1_RCC = ((uint32_t)0x00001000);
        static const uint32_t TIM8_RCC = ((uint32_t)0x00002000);
        static const uint32_t USART_RCC = ((uint32_t)0x00004000);
        static const uint32_t ADC3_RCC = ((uint32_t)0x00008000);
        static const uint32_t Timer_15_RCC = ((uint32_t)0x00010000);
        static const uint32_t Timer_16_RCC = ((uint32_t)0x00020000);
        static const uint32_t Timer_17_RCC = ((uint32_t)0x00040000);
        static const uint32_t TIM9_RCC = ((uint32_t)0x00080000);
        static const uint32_t Timer_10_RCC = ((uint32_t)0x00100000);
        static const uint32_t Timer_11_RCC = ((uint32_t)0x00200000);
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
    } close;
    // Timer1为总线2(高级)
    // Timer2/3/4为总线1(通用)
    // GPIO a~g 中断为总线2
} static clocks;

namespace Device
{
    // 默认低电平
    class Timer
    {
        class TimerType
        {
            class Universal
            {
            public:
                static const uint8_t timer_2 = 0;
                static const uint8_t timer_3 = 1;                              
                static const uint8_t timer_4 = 2;
            } static const universal;
        } static const timerType;

    public:
        class Universal_timer
        {
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
            Universal_timer(uint8_t timerType,uint16_t times) : index(timerType), BASIC_TIM(TIM2 + (0x0400) * (index)) 
            {
                NVIC_Config();
                TIM_Config(times);
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

            void TIM_Config(uint16_t limits)
            {

                uint16_t BASIC_TIM_Prescaler = 71;
                TIM_TypeDef *timer = 0;

                TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

                // 开启定时器时钟,即内部时钟CK_INT=72M
                RCC_APB1PeriphClockCmd(((uint32_t)0x00000001) << (index), ENABLE);
                // RCC_APB1Periph_TIM4;
                // 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
                // uint16_t limits = 1000 - 1;
                TIM_TimeBaseStructure.TIM_Period = limits;
                // 时钟预分频数为
                TIM_TimeBaseStructure.TIM_Prescaler = BASIC_TIM_Prescaler;

                // 时钟分频因子 ，基本定时器没有，不用管
                TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

                // 计数器计数模式，基本定时器只能向上计数，没有计数模式的设置
                TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

                // 重复计数器的值，基本定时器没有，不用管
                TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

                // 初始化定时器
                TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);

                // 清除计数器中断标志位
                TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);

                // 开启计数器中断：计数器溢出、产生更新事件、计数器的更新事件能够产生中断、并被使能
                TIM_ITConfig(BASIC_TIM, TIM_IT_Update, ENABLE);

                // 使能计数器
                TIM_Cmd(BASIC_TIM, ENABLE);
            }

            void BASIC_TIM_Init(void)
            {
                NVIC_Config();
                TIM_Config(6);
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
        // std::vector<int> a;

    public:
        LED(GPIO_TypeDef *_port, uint16_t _pin, GPIOSpeed_TypeDef Speed = IOSpeed::_50MHz, GPIOMode_TypeDef mode = IOMode::Out_PP)
            : pin(_pin), port(_port)
        {
            if (io.sign(_port, _pin))
            {
                clocks.open.APB2Periph(clocks.port_to_open.GPIOA_RCC);
                GPIO_InitTypeDef GPIO_InitStructure;
                GPIO_InitStructure.GPIO_Pin = pin;
                GPIO_InitStructure.GPIO_Mode = mode;
                GPIO_InitStructure.GPIO_Speed = Speed;
                GPIO_Init(port, &GPIO_InitStructure);
                io.Write_pin(port, pin, 0);
            }
        }
        void turn()
        {
            io.Change_pin(this->port, this->pin);
        }
    };
};
