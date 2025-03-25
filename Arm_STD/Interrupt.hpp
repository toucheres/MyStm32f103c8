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

#define USART2_fun                                                                         \
    void USART2_Handler_Func(void);                                                        \
    namespace                                                                              \
    {                                                                                      \
        struct USART2_Handler_Init                                                         \
        {                                                                                  \
            USART2_Handler_Init()                                                          \
            {                                                                              \
                System::Interrupt::registerHandler(System::Interrupt::USART2_IRQHand,      \
                                                   [](void *) { USART2_Handler_Func(); }); \
            }                                                                              \
        } USART2_Handler_Init_instance;                                                    \
    }                                                                                      \
    void USART2_Handler_Func(void)

#define USART3_fun                                                                         \
    void USART3_Handler_Func(void);                                                        \
    namespace                                                                              \
    {                                                                                      \
        struct USART3_Handler_Init                                                         \
        {                                                                                  \
            USART3_Handler_Init()                                                          \
            {                                                                              \
                System::Interrupt::registerHandler(System::Interrupt::USART3_IRQHand,      \
                                                   [](void *) { USART3_Handler_Func(); }); \
            }                                                                              \
        } USART3_Handler_Init_instance;                                                    \
    }                                                                                      \
    void USART3_Handler_Func(void)

#define EXTI0_fun                                                                         \
    void EXTI0_Handler_Func(void);                                                        \
    namespace                                                                             \
    {                                                                                     \
        struct EXTI0_Handler_Init                                                         \
        {                                                                                 \
            EXTI0_Handler_Init()                                                          \
            {                                                                             \
                System::Interrupt::registerHandler(System::Interrupt::EXTI0_IRQHand,      \
                                                   [](void *) { EXTI0_Handler_Func(); }); \
            }                                                                             \
        } EXTI0_Handler_Init_instance;                                                    \
    }                                                                                     \
    void EXTI0_Handler_Func(void)

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

#define EXTI2_fun                                                                         \
    void EXTI2_Handler_Func(void);                                                        \
    namespace                                                                             \
    {                                                                                     \
        struct EXTI2_Handler_Init                                                         \
        {                                                                                 \
            EXTI2_Handler_Init()                                                          \
            {                                                                             \
                System::Interrupt::registerHandler(System::Interrupt::EXTI2_IRQHand,      \
                                                   [](void *) { EXTI2_Handler_Func(); }); \
            }                                                                             \
        } EXTI2_Handler_Init_instance;                                                    \
    }                                                                                     \
    void EXTI2_Handler_Func(void)

#define EXTI3_fun                                                                         \
    void EXTI3_Handler_Func(void);                                                        \
    namespace                                                                             \
    {                                                                                     \
        struct EXTI3_Handler_Init                                                         \
        {                                                                                 \
            EXTI3_Handler_Init()                                                          \
            {                                                                             \
                System::Interrupt::registerHandler(System::Interrupt::EXTI3_IRQHand,      \
                                                   [](void *) { EXTI3_Handler_Func(); }); \
            }                                                                             \
        } EXTI3_Handler_Init_instance;                                                    \
    }                                                                                     \
    void EXTI3_Handler_Func(void)

#define EXTI4_fun                                                                         \
    void EXTI4_Handler_Func(void);                                                        \
    namespace                                                                             \
    {                                                                                     \
        struct EXTI4_Handler_Init                                                         \
        {                                                                                 \
            EXTI4_Handler_Init()                                                          \
            {                                                                             \
                System::Interrupt::registerHandler(System::Interrupt::EXTI4_IRQHand,      \
                                                   [](void *) { EXTI4_Handler_Func(); }); \
            }                                                                             \
        } EXTI4_Handler_Init_instance;                                                    \
    }                                                                                     \
    void EXTI4_Handler_Func(void)

#define EXTI9_5_fun                                                                         \
    void EXTI9_5_Handler_Func(void);                                                        \
    namespace                                                                               \
    {                                                                                       \
        struct EXTI9_5_Handler_Init                                                         \
        {                                                                                    \
            EXTI9_5_Handler_Init()                                                          \
            {                                                                               \
                System::Interrupt::registerHandler(System::Interrupt::EXTI9_5_IRQHand,      \
                                                   [](void *) { EXTI9_5_Handler_Func(); }); \
            }                                                                               \
        } EXTI9_5_Handler_Init_instance;                                                    \
    }                                                                                       \
    void EXTI9_5_Handler_Func(void)

#define EXTI15_10_fun                                                                         \
    void EXTI15_10_Handler_Func(void);                                                        \
    namespace                                                                                 \
    {                                                                                         \
        struct EXTI15_10_Handler_Init                                                         \
        {                                                                                      \
            EXTI15_10_Handler_Init()                                                          \
            {                                                                                 \
                System::Interrupt::registerHandler(System::Interrupt::EXTI15_10_IRQHand,      \
                                                   [](void *) { EXTI15_10_Handler_Func(); }); \
            }                                                                                 \
        } EXTI15_10_Handler_Init_instance;                                                    \
    }                                                                                         \
    void EXTI15_10_Handler_Func(void)

#define TIM1_BRK_fun                                                                         \
    void TIM1_BRK_Handler_Func(void);                                                        \
    namespace                                                                                \
    {                                                                                        \
        struct TIM1_BRK_Handler_Init                                                         \
        {                                                                                    \
            TIM1_BRK_Handler_Init()                                                          \
            {                                                                                \
                System::Interrupt::registerHandler(System::Interrupt::TIM1_BRK_IRQHand,      \
                                                   [](void *) { TIM1_BRK_Handler_Func(); }); \
            }                                                                                \
        } TIM1_BRK_Handler_Init_instance;                                                    \
    }                                                                                        \
    void TIM1_BRK_Handler_Func(void)

#define TIM1_UP_fun                                                                         \
    void TIM1_UP_Handler_Func(void);                                                        \
    namespace                                                                               \
    {                                                                                       \
        struct TIM1_UP_Handler_Init                                                         \
        {                                                                                   \
            TIM1_UP_Handler_Init()                                                          \
            {                                                                               \
                System::Interrupt::registerHandler(System::Interrupt::TIM1_UP_IRQHand,      \
                                                   [](void *) { TIM1_UP_Handler_Func(); }); \
            }                                                                               \
        } TIM1_UP_Handler_Init_instance;                                                    \
    }                                                                                       \
    void TIM1_UP_Handler_Func(void)

#define TIM1_TRG_COM_fun                                                                         \
    void TIM1_TRG_COM_Handler_Func(void);                                                        \
    namespace                                                                                    \
    {                                                                                            \
        struct TIM1_TRG_COM_Handler_Init                                                         \
        {                                                                                        \
            TIM1_TRG_COM_Handler_Init()                                                          \
            {                                                                                    \
                System::Interrupt::registerHandler(System::Interrupt::TIM1_TRG_COM_IRQHand,      \
                                                   [](void *) { TIM1_TRG_COM_Handler_Func(); }); \
            }                                                                                    \
        } TIM1_TRG_COM_Handler_Init_instance;                                                    \
    }                                                                                            \
    void TIM1_TRG_COM_Handler_Func(void)

#define TIM1_CC_fun                                                                         \
    void TIM1_CC_Handler_Func(void);                                                        \
    namespace                                                                               \
    {                                                                                       \
        struct TIM1_CC_Handler_Init                                                         \
        {                                                                                   \
            TIM1_CC_Handler_Init()                                                          \
            {                                                                               \
                System::Interrupt::registerHandler(System::Interrupt::TIM1_CC_IRQHand,      \
                                                   [](void *) { TIM1_CC_Handler_Func(); }); \
            }                                                                               \
        } TIM1_CC_Handler_Init_instance;                                                    \
    }                                                                                       \
    void TIM1_CC_Handler_Func(void)

#define TIM2_fun                                                                         \
    void TIM2_Handler_Func(void);                                                        \
    namespace                                                                            \
    {                                                                                    \
        struct TIM2_Handler_Init                                                         \
        {                                                                                \
            TIM2_Handler_Init()                                                          \
            {                                                                            \
                System::Interrupt::registerHandler(System::Interrupt::TIM2_IRQHand,      \
                                                   [](void *) { TIM2_Handler_Func(); }); \
            }                                                                            \
        } TIM2_Handler_Init_instance;                                                    \
    }                                                                                    \
    void TIM2_Handler_Func(void)

#define TIM3_fun                                                                         \
    void TIM3_Handler_Func(void);                                                        \
    namespace                                                                            \
    {                                                                                    \
        struct TIM3_Handler_Init                                                         \
        {                                                                                \
            TIM3_Handler_Init()                                                          \
            {                                                                            \
                System::Interrupt::registerHandler(System::Interrupt::TIM3_IRQHand,      \
                                                   [](void *) { TIM3_Handler_Func(); }); \
            }                                                                            \
        } TIM3_Handler_Init_instance;                                                    \
    }                                                                                    \
    void TIM3_Handler_Func(void)

#define TIM4_fun                                                                         \
    void TIM4_Handler_Func(void);                                                        \
    namespace                                                                            \
    {                                                                                    \
        struct TIM4_Handler_Init                                                         \
        {                                                                                \
            TIM4_Handler_Init()                                                          \
            {                                                                            \
                System::Interrupt::registerHandler(System::Interrupt::TIM4_IRQHand,      \
                                                   [](void *) { TIM4_Handler_Func(); }); \
            }                                                                            \
        } TIM4_Handler_Init_instance;                                                    \
    }                                                                                    \
    void TIM4_Handler_Func(void)

// 定义剩余中断处理宏...（I2C，SPI，DMA等）
#define I2C1_EV_fun                                                                         \
    void I2C1_EV_Handler_Func(void);                                                        \
    namespace                                                                               \
    {                                                                                       \
        struct I2C1_EV_Handler_Init                                                         \
        {                                                                                   \
            I2C1_EV_Handler_Init()                                                          \
            {                                                                               \
                System::Interrupt::registerHandler(System::Interrupt::I2C1_EV_IRQHand,      \
                                                   [](void *) { I2C1_EV_Handler_Func(); }); \
            }                                                                               \
        } I2C1_EV_Handler_Init_instance;                                                    \
    }                                                                                       \
    void I2C1_EV_Handler_Func(void)

#define I2C1_ER_fun                                                                         \
    void I2C1_ER_Handler_Func(void);                                                        \
    namespace                                                                               \
    {                                                                                       \
        struct I2C1_ER_Handler_Init                                                         \
        {                                                                                   \
            I2C1_ER_Handler_Init()                                                          \
            {                                                                               \
                System::Interrupt::registerHandler(System::Interrupt::I2C1_ER_IRQHand,      \
                                                   [](void *) { I2C1_ER_Handler_Func(); }); \
            }                                                                               \
        } I2C1_ER_Handler_Init_instance;                                                    \
    }                                                                                       \
    void I2C1_ER_Handler_Func(void)

#define I2C2_EV_fun                                                                         \
    void I2C2_EV_Handler_Func(void);                                                        \
    namespace                                                                               \
    {                                                                                       \
        struct I2C2_EV_Handler_Init                                                         \
        {                                                                                   \
            I2C2_EV_Handler_Init()                                                          \
            {                                                                               \
                System::Interrupt::registerHandler(System::Interrupt::I2C2_EV_IRQHand,      \
                                                   [](void *) { I2C2_EV_Handler_Func(); }); \
            }                                                                               \
        } I2C2_EV_Handler_Init_instance;                                                    \
    }                                                                                       \
    void I2C2_EV_Handler_Func(void)

#define I2C2_ER_fun                                                                         \
    void I2C2_ER_Handler_Func(void);                                                        \
    namespace                                                                               \
    {                                                                                       \
        struct I2C2_ER_Handler_Init                                                         \
        {                                                                                   \
            I2C2_ER_Handler_Init()                                                          \
            {                                                                               \
                System::Interrupt::registerHandler(System::Interrupt::I2C2_ER_IRQHand,      \
                                                   [](void *) { I2C2_ER_Handler_Func(); }); \
            }                                                                               \
        } I2C2_ER_Handler_Init_instance;                                                    \
    }                                                                                       \
    void I2C2_ER_Handler_Func(void)

#define SPI1_fun                                                                         \
    void SPI1_Handler_Func(void);                                                        \
    namespace                                                                            \
    {                                                                                    \
        struct SPI1_Handler_Init                                                         \
        {                                                                                \
            SPI1_Handler_Init()                                                          \
            {                                                                            \
                System::Interrupt::registerHandler(System::Interrupt::SPI1_IRQHand,      \
                                                   [](void *) { SPI1_Handler_Func(); }); \
            }                                                                            \
        } SPI1_Handler_Init_instance;                                                    \
    }                                                                                    \
    void SPI1_Handler_Func(void)

#define SPI2_fun                                                                         \
    void SPI2_Handler_Func(void);                                                        \
    namespace                                                                            \
    {                                                                                    \
        struct SPI2_Handler_Init                                                         \
        {                                                                                \
            SPI2_Handler_Init()                                                          \
            {                                                                            \
                System::Interrupt::registerHandler(System::Interrupt::SPI2_IRQHand,      \
                                                   [](void *) { SPI2_Handler_Func(); }); \
            }                                                                            \
        } SPI2_Handler_Init_instance;                                                    \
    }                                                                                    \
    void SPI2_Handler_Func(void)

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

    inline void USART2_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USART2_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USART2_IRQHand]();
        }
    }

    inline void USART3_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USART3_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USART3_IRQHand]();
        }
    }

    inline void EXTI0_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI0_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI0_IRQHand]();
        }
    }

    inline void EXTI1_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI1_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI1_IRQHand]();
        }
    }

    inline void EXTI2_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI2_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI2_IRQHand]();
        }
    }

    inline void EXTI3_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI3_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI3_IRQHand]();
        }
    }

    inline void EXTI4_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI4_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI4_IRQHand]();
        }
    }

    inline void EXTI9_5_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI9_5_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI9_5_IRQHand]();
        }
    }

    inline void EXTI15_10_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI15_10_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI15_10_IRQHand]();
        }
    }

    inline void TIM1_BRK_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM1_BRK_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM1_BRK_IRQHand]();
        }
    }

    inline void TIM1_UP_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM1_UP_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM1_UP_IRQHand]();
        }
    }

    inline void TIM1_TRG_COM_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM1_TRG_COM_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM1_TRG_COM_IRQHand]();
        }
    }

    inline void TIM1_CC_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM1_CC_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM1_CC_IRQHand]();
        }
    }

    inline void TIM2_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM2_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM2_IRQHand]();
        }
    }

    inline void TIM3_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM3_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM3_IRQHand]();
        }
    }

    inline void TIM4_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM4_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM4_IRQHand]();
        }
    }

    inline void I2C1_EV_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::I2C1_EV_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::I2C1_EV_IRQHand]();
        }
    }

    inline void I2C1_ER_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::I2C1_ER_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::I2C1_ER_IRQHand]();
        }
    }

    inline void I2C2_EV_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::I2C2_EV_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::I2C2_EV_IRQHand]();
        }
    }

    inline void I2C2_ER_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::I2C2_ER_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::I2C2_ER_IRQHand]();
        }
    }

    inline void SPI1_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::SPI1_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::SPI1_IRQHand]();
        }
    }

    inline void SPI2_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::SPI2_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::SPI2_IRQHand]();
        }
    }

    inline void DMA1_Channel1_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel1_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::DMA1_Channel1_IRQHand]();
        }
    }

    inline void DMA1_Channel2_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel2_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::DMA1_Channel2_IRQHand]();
        }
    }

    inline void DMA1_Channel3_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel3_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::DMA1_Channel3_IRQHand]();
        }
    }

    inline void DMA1_Channel4_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel4_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::DMA1_Channel4_IRQHand]();
        }
    }

    inline void DMA1_Channel5_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel5_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::DMA1_Channel5_IRQHand]();
        }
    }

    inline void DMA1_Channel6_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel6_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::DMA1_Channel6_IRQHand]();
        }
    }

    inline void DMA1_Channel7_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel7_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::DMA1_Channel7_IRQHand]();
        }
    }

    inline void ADC1_2_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::ADC1_2_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::ADC1_2_IRQHand]();
        }
    }

    inline void RTCAlarm_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::RTCAlarm_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::RTCAlarm_IRQHand]();
        }
    }

    inline void USBWakeUp_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USBWakeUp_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USBWakeUp_IRQHand]();
        }
    }

    inline void USB_HP_CAN1_TX_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USB_HP_CAN1_TX_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USB_HP_CAN1_TX_IRQHand]();
        }
    }

    inline void USB_LP_CAN1_RX0_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USB_LP_CAN1_RX0_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USB_LP_CAN1_RX0_IRQHand]();
        }
    }

    inline void CAN1_RX1_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::CAN1_RX1_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::CAN1_RX1_IRQHand]();
        }
    }

    inline void CAN1_SCE_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::CAN1_SCE_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::CAN1_SCE_IRQHand]();
        }
    }

    inline void WWDG_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::WWDG_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::WWDG_IRQHand]();
        }
    }

    inline void PVD_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::PVD_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::PVD_IRQHand]();
        }
    }

    inline void TAMPER_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TAMPER_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TAMPER_IRQHand]();
        }
    }

    inline void RTC_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::RTC_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::RTC_IRQHand]();
        }
    }

    inline void FLASH_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::FLASH_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::FLASH_IRQHand]();
        }
    }

    inline void RCC_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::RCC_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::RCC_IRQHand]();
        }
    }
}
#endif // __INTERPUT_H__
