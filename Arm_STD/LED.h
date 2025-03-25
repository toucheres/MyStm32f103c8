#ifndef _LED_H_
#define _LED_H_

#include "stm32f10x.h"
#include "MyStm32.h" // 包含IO, Port等基类定义

namespace Device
{
    class LED
    {
    private:
        GPIO_TypeDef *port;
        uint16_t pin;

    public:
        LED(GPIO_TypeDef *_port, uint16_t _pin,
            GPIOSpeed_TypeDef Speed = IOSpeed::_50MHz,
            GPIOMode_TypeDef mode = IOMode::Out_PP);
        
        // 切换LED状态
        void turn();
        
        // 设置LED状态
        void set(bool state);
        
        // 获取LED状态
        bool get() const;
    };
} // namespace Device

#endif // _LED_H_
