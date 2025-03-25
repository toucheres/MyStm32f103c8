#include "LED.h"

namespace Device
{
    LED::LED(GPIO_TypeDef *_port, uint16_t _pin,
             GPIOSpeed_TypeDef Speed, GPIOMode_TypeDef mode)
        : pin(_pin), port(_port)
    {
        // 使能GPIO端口时钟
        clocks.open.port(_port);
        
        // 初始化GPIO
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = pin;
        GPIO_InitStructure.GPIO_Mode = mode;
        GPIO_InitStructure.GPIO_Speed = Speed;
        GPIO_Init(port, &GPIO_InitStructure);
        
        // 默认LED关闭
        io.Write_pin(port, pin, 0);
    }

    void LED::turn()
    {
        io.Change_pin(this->port, this->pin);
    }
    
    void LED::set(bool state)
    {
        io.Write_pin(port, pin, state);
    }
    
    bool LED::get() const
    {
        return io.read_pin(port, pin) != 0;
    }
} // namespace Device
