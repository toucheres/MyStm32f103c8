#include "Interrupt.h"
// 实现所有中断处理函数
System::Interrupt::RunAble System::Interrupt::interrupts[NUM_Type] = {nullptr};
uint16_t System::Interrupt::formGPIOPIN2InterruptType(uint16_t GPIO_Pin)
{ // 查找引脚位置
    uint8_t pinPosition = 0;
    for (uint8_t i = 0; i < 16; i++)
    {
        if (GPIO_Pin == (1 << i))
        {
            pinPosition = i;
            break;
        }
    }

    // 根据引脚位置确定中断类型
    if (pinPosition <= 4)
    {
        // EXTI0 - EXTI4 对应单独的中断类型
        return static_cast<uint16_t>(EXTI0_IRQHand + pinPosition);
    }
    else if (pinPosition <= 9)
    {
        // EXTI5 - EXTI9 共享EXTI9_5中断
        return static_cast<uint16_t>(EXTI9_5_IRQHand);
    }
    else if (pinPosition <= 15)
    {
        // EXTI10 - EXTI15 共享EXTI15_10中断
        return static_cast<uint16_t>(EXTI15_10_IRQHand);
    }

    // 无效的引脚值
    return 0xFFFF;
}
void System::Interrupt::registerHandler(uint16_t type, void (*fun)(void *),
                                        void *arg) {
  System::Interrupt::interrupts[type] = RunAble(fun, arg);
}
extern "C"
{
    void USART1_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USART1_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USART1_IRQHand]();
        }
    }

    void USART2_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USART2_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USART2_IRQHand]();
        }
    }

    void USART3_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USART3_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USART3_IRQHand]();
        }
    }

    void EXTI0_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI0_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI0_IRQHand]();
        }
    }

    void EXTI1_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI1_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI1_IRQHand]();
        }
    }

    void EXTI2_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI2_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI2_IRQHand]();
        }
    }

    void EXTI3_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI3_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI3_IRQHand]();
        }
    }

    void EXTI4_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI4_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI4_IRQHand]();
        }
    }

    void EXTI9_5_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI9_5_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI9_5_IRQHand]();
        }
    }

    void EXTI15_10_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::EXTI15_10_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::EXTI15_10_IRQHand]();
        }
    }

    void TIM1_BRK_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM1_BRK_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM1_BRK_IRQHand]();
        }
    }

    void TIM1_UP_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM1_UP_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM1_UP_IRQHand]();
        }
    }

    void TIM1_TRG_COM_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM1_TRG_COM_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM1_TRG_COM_IRQHand]();
        }
    }

    void TIM1_CC_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM1_CC_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM1_CC_IRQHand]();
        }
    }

    void TIM2_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM2_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM2_IRQHand]();
        }
    }

    void TIM3_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM3_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM3_IRQHand]();
        }
    }

    void TIM4_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TIM4_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TIM4_IRQHand]();
        }
    }

    void I2C1_EV_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::I2C1_EV_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::I2C1_EV_IRQHand]();
        }
    }

    void I2C1_ER_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::I2C1_ER_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::I2C1_ER_IRQHand]();
        }
    }

    void I2C2_EV_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::I2C2_EV_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::I2C2_EV_IRQHand]();
        }
    }

    void I2C2_ER_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::I2C2_ER_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::I2C2_ER_IRQHand]();
        }
    }

    void SPI1_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::SPI1_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::SPI1_IRQHand]();
        }
    }

    void SPI2_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::SPI2_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::SPI2_IRQHand]();
        }
    }

    // void DMA1_Channel1_IRQHandler(void)
    // {
    //     if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel1_IRQHand])
    //     {
    //         System::Interrupt::interrupts[System::Interrupt::DMA1_Channel1_IRQHand]();
    //     }
    // }

    // void DMA1_Channel2_IRQHandler(void)
    // {
    //     if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel2_IRQHand])
    //     {
    //         System::Interrupt::interrupts[System::Interrupt::DMA1_Channel2_IRQHand]();
    //     }
    // }

    // void DMA1_Channel3_IRQHandler(void)
    // {
    //     if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel3_IRQHand])
    //     {
    //         System::Interrupt::interrupts[System::Interrupt::DMA1_Channel3_IRQHand]();
    //     }
    // }

    // void DMA1_Channel4_IRQHandler(void)
    // {
    //     if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel4_IRQHand])
    //     {
    //         System::Interrupt::interrupts[System::Interrupt::DMA1_Channel4_IRQHand]();
    //     }
    // }

    // void DMA1_Channel5_IRQHandler(void)
    // {
    //     if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel5_IRQHand])
    //     {
    //         System::Interrupt::interrupts[System::Interrupt::DMA1_Channel5_IRQHand]();
    //     }
    // }

    // void DMA1_Channel6_IRQHandler(void)
    // {
    //     if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel6_IRQHand])
    //     {
    //         System::Interrupt::interrupts[System::Interrupt::DMA1_Channel6_IRQHand]();
    //     }
    // }

    // void DMA1_Channel7_IRQHandler(void)
    // {
    //     if (System::Interrupt::interrupts[System::Interrupt::DMA1_Channel7_IRQHand])
    //     {
    //         System::Interrupt::interrupts[System::Interrupt::DMA1_Channel7_IRQHand]();
    //     }
    // }

    void ADC1_2_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::ADC1_2_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::ADC1_2_IRQHand]();
        }
    }

    void RTCAlarm_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::RTCAlarm_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::RTCAlarm_IRQHand]();
        }
    }

    void USBWakeUp_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USBWakeUp_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USBWakeUp_IRQHand]();
        }
    }

    void USB_HP_CAN1_TX_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USB_HP_CAN1_TX_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USB_HP_CAN1_TX_IRQHand]();
        }
    }

    void USB_LP_CAN1_RX0_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::USB_LP_CAN1_RX0_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::USB_LP_CAN1_RX0_IRQHand]();
        }
    }

    void CAN1_RX1_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::CAN1_RX1_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::CAN1_RX1_IRQHand]();
        }
    }

    void CAN1_SCE_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::CAN1_SCE_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::CAN1_SCE_IRQHand]();
        }
    }

    void WWDG_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::WWDG_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::WWDG_IRQHand]();
        }
    }

    void PVD_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::PVD_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::PVD_IRQHand]();
        }
    }

    void TAMPER_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::TAMPER_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::TAMPER_IRQHand]();
        }
    }

    void RTC_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::RTC_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::RTC_IRQHand]();
        }
        RTC_ClearITPendingBit(RTC_IT_SEC);
    }

    void FLASH_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::FLASH_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::FLASH_IRQHand]();
        }
    }

    void RCC_IRQHandler(void)
    {
        if (System::Interrupt::interrupts[System::Interrupt::RCC_IRQHand])
        {
            System::Interrupt::interrupts[System::Interrupt::RCC_IRQHand]();
        }
    }
}
