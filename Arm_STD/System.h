#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include <cstdint>
#include "MyStm32.h" // 包含time_us, time_ms, time_s等基本类型定义
#include "Interrupt.h"

namespace System
{
    void delay(time_ms);
    void delay(time_us);
    void delay(time_s);
    uint32_t millisecond();
    uint32_t getTick(); // 添加getTick函数声明
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
        void sleep_for_interrupt();
        void sleep_for_event();
        void stop();
        void stop_lpPowerControl();
        void setEXTIWakeup(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                           EXTITrigger_TypeDef Trigger = EXTI_Trigger_Falling);
        void configEXTIForWakeup(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                                               EXTITrigger_TypeDef Trigger = EXTI_Trigger_Falling);
        void stop(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                  EXTITrigger_TypeDef Trigger);
            // void stopWithEXTIWakeup(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
            //                        EXTITrigger_TypeDef Trigger = EXTI_Trigger_Falling);
            void standby();
    }
} // namespace System

#endif // _SYSTEM_H_
