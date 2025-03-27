#include "System.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_iwdg.h"
#include "Interrupt.h"
namespace System
{
    void delay(time_s time)
    {
        for (uint16_t i = 0; i < time; i++)
        {
            delay(1000_ms);
        }
    }

    void delay(time_ms time)
    {
        for (uint16_t i = 0; i < time; i++)
        {
            delay(1000_us);
        }
    }

    void delay(time_us time)
    {
        SysTick->LOAD = 72 * time;  // 设置定时器重装值
        SysTick->VAL = 0x00;        // 清空当前计数值
        SysTick->CTRL = 0x00000005; // 设置时钟源为HCLK，启动定时器
        while (!(SysTick->CTRL & 0x00010000))
            ;                       // 等待计数到0
        SysTick->CTRL = 0x00000004; // 关闭定时器
    }

    // 409500us 精度100us
    void WatchDog::IndependWatchDog::setTime(time_us timeus)
    {
        IWDG_Init(0, 10000 * timeus);
    }

    // 1628ms 精度:1/2500s(0.4ms)
    void WatchDog::IndependWatchDog::setTime(time_ms timems)
    {
        IWDG_Init(2, 2500 * timems);
    }

    // LSI时钟频率：典型值约40KHz（实际范围为30-60KHz）下
    // 预分频值最高为6（系数为4095）
    // 最大重装载值4095
    // max--26.21秒
    // 精度1/156s(0.006s)
    void WatchDog::IndependWatchDog::setTime(time_s times)
    {
        IWDG_Init(6, 156 * times);
    }

    void WatchDog::IndependWatchDog::feed(void)
    {
        IWDG_ReloadCounter();
    }

    void WatchDog::IndependWatchDog::IWDG_Init(u8 prer, u16 rlr)
    {
        // 1、取消寄存器写保护 写0x5555
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        // 2、设置独立看门狗预分频系数
        IWDG_SetPrescaler(prer);
        // 3、设置独立看门狗重装载值
        IWDG_SetReload(rlr);
        // 4、重载计数值喂狗 写0xAAAA
        IWDG_ReloadCounter();
        // 5、启动看门狗     写0xCCCC
        IWDG_Enable();
    }

    // power namespace实现
    namespace power
    {
        void sleep_for_interrupt()
        {
            __WFI();
        }

        void sleep_for_event()
        {
            __WFE();
        }

        void stop()
        {
            // 使能PWR时钟
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
            // 清除唤醒标志
            PWR_ClearFlag(PWR_FLAG_WU);
            // 设置电压调节器模式
            PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
        }

        void stop_lpPowerControl()
        {
            // 使能PWR时钟
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
            // 清除唤醒标志
            PWR_ClearFlag(PWR_FLAG_WU);
            // 设置低功耗电压调节器模式
            PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
        }

        void configEXTIForWakeup(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                                 EXTITrigger_TypeDef Trigger)
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

        void stopWithEXTIWakeup(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                                EXTITrigger_TypeDef Trigger)
        {
            // 配置外部中断
            configEXTIForWakeup(GPIOx, GPIO_Pin, Trigger);
            static uint16_t GPIO_Pin_Wakable = GPIO_Pin;
            uint16_t interruptType = System::Interrupt::formGPIOPIN2InterruptType(GPIO_Pin);
            System::Interrupt::registerHandler(interruptType, [](void *)
                                               {
              if (EXTI_GetITStatus(GPIO_Pin_Wakable) != RESET)
              {
                  EXTI_ClearITPendingBit(GPIO_Pin_Wakable);
              } });
            // 使能PWR时钟
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

            // 清除唤醒标志
            PWR_ClearFlag(PWR_FLAG_WU);

            // 进入STOP模式
            PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);

            // 唤醒后需要重新配置系统时钟
            SystemInit();
        }

        void standby()
        {
            // 使能PWR时钟
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
            // 清除唤醒标志
            PWR_ClearFlag(PWR_FLAG_WU);
            // 设置唤醒引脚(如需启用，取消注释)
            PWR_WakeUpPinCmd(ENABLE);
            // 进入待机模式
            PWR_EnterSTANDBYMode();
        }
    } // namespace power
} // namespace System
