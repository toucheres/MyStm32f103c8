#ifndef __INTERPUT_H__
#define __INTERPUT_H__
#include "stm32f10x.h"
#include <stdint.h>
namespace System
{
    class Interrupt
    {
    public:
        enum Type
        {

            EXTI0_IRQHand,
            EXTI1_IRQHand,
            EXTI2_IRQHand,
            EXTI3_IRQHand,
            EXTI4_IRQHand,
            EXTI9_5_IRQHand,
            EXTI15_10_IRQHand,
            TIM1_BRK_IRQHand,
            TIM1_UP_IRQHand,
            TIM1_TRG_COM_IRQHand,
            TIM1_CC_IRQHand,
            TIM2_IRQHand,
            TIM3_IRQHand,
            TIM4_IRQHand,
            I2C1_EV_IRQHand,
            I2C1_ER_IRQHand,
            I2C2_EV_IRQHand,
            I2C2_ER_IRQHand,
            SPI1_IRQHand,
            SPI2_IRQHand,
            USART1_IRQHand,
            USART2_IRQHand,
            USART3_IRQHand,

            DMA1_Channel1_IRQHand,
            DMA1_Channel2_IRQHand,
            DMA1_Channel3_IRQHand,
            DMA1_Channel4_IRQHand,
            DMA1_Channel5_IRQHand,
            DMA1_Channel6_IRQHand,
            DMA1_Channel7_IRQHand,
            ADC1_2_IRQHand,

            RTCAlarm_IRQHand,
            USBWakeUp_IRQHand,
            USB_HP_CAN1_TX_IRQHand,
            USB_LP_CAN1_RX0_IRQHand,
            CAN1_RX1_IRQHand,
            CAN1_SCE_IRQHand,
            WWDG_IRQHand,
            PVD_IRQHand,
            TAMPER_IRQHand,
            RTC_IRQHand,
            FLASH_IRQHand,
            RCC_IRQHand,
            NUM_Type
        };

        // typedef void (*callback)(void *);
        class callback
        {
            void (*fun)(void *);
            void *arg;

        public:
            callback()
            {
                this->fun = nullptr;
                this->arg = nullptr;
            }
            callback(void (*fun)(void *), void *arg = nullptr)
            {
                this->fun = fun;
                this->arg = arg;
            }
            operator bool() { return this->fun != nullptr; }
            void operator()()
            {
                if (this->fun != nullptr)
                    this->fun(this->arg);
            }
        };
        inline static callback interrupts[NUM_Type] = {};

        static void registerHandler(std::uint16_t type, void (*fun)(void *), void *arg = nullptr)
        {
            interrupts[type] = {fun, arg};
        }

        void sign(uint16_t type, callback callback);
    };
};

// 重新定义中断处理宏
#define USART1_fun                                                                         \
    void USART1_Handler_Func(void);                                                        \
    namespace                                                                              \
    {                                                                                      \
        struct USART1_Handler_Init                                                         \
        {                                                                                  \
            USART1_Handler_Init()                                                          \
            {                                                                              \
                System::Interrupt::registerHandler(System::Interrupt::USART1_IRQHand,      \
                                                   [](void *) { USART1_Handler_Func(); }); \
            }                                                                              \
        } USART1_Handler_Init_instance;                                                    \
    }                                                                                      \
    void USART1_Handler_Func(void)

// 其他中断处理宏类似定义
#define EXTI1_fun                                                                         \
    void EXTI1_Handler_Func(void);                                                        \
    namespace                                                                             \
    {                                                                                     \
        struct EXTI1_Handler_Init                                                         \
        {                                                                                 \
            EXTI1_Handler_Init()                                                          \
            {                                                                             \
                System::Interrupt::registerHandler(System::Interrupt::EXTI1_IRQHand,      \
                                                   [](void *) { EXTI1_Handler_Func(); }); \
            }                                                                             \
        } EXTI1_Handler_Init_instance;                                                    \
    }                                                                                     \
    void EXTI1_Handler_Func(void)

// 实现所有中断处理函数
extern "C"
{
    inline void USART1_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USART1_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USART1_IRQHand]();
        }
    }

    inline void EXTI1_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI1_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI1_IRQHand]();
        }
    }

    // ... 其他中断处理函数 ...
}
#endif // __INTERPUT_H__
