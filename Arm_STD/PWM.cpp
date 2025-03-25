#include "PWM.h"
//#include "MyStm32.h"

Device::PWM::PWM(uint8_t timertype, uint8_t _channals)
    : timer(timertype), channals(_channals), frequency(1000)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    // 使能定时器时钟，注意定时器时钟为APB1，而非APB2
    RCC_APB1PeriphClockCmd(((uint32_t)0x00000001) << (this->timer), ENABLE);
    // 使能PWM输出GPIO口时钟
    // RCC_APB2PeriphClockCmd(Port_to_Rcc(getPort()), ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 999;       // 自动重装值 (ARR)，实际周期为1000
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1; // 时钟预分频数，72MHz/(72-1+1)=1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数模式
    TIM_TimeBaseInit(reinterpret_cast<TIM_TypeDef *>(APB1PERIPH_BASE +
                                                     (this->timer * 0x400)),
                     &TIM_TimeBaseStructure);

    // 初始化各个通道
    if (channals & 0b0001)
    {
        this->channal_1 = Timer::Channal{timertype, 1};
        this->channal_1.init();
        // 启用通道1预装载
        Timer::Channal::TIM_OCxPreloadConfig(
            reinterpret_cast<TIM_TypeDef *>(APB1PERIPH_BASE + 0x0400 * this->timer),
            TIM_OCPreload_Enable, 1);
    }
    if (channals & 0b0010)
    {
        this->channal_2 = Timer::Channal{timertype, 2};
        this->channal_2.init();
        // 启用通道2预装载
        Timer::Channal::TIM_OCxPreloadConfig(
            reinterpret_cast<TIM_TypeDef *>(APB1PERIPH_BASE + 0x0400 * this->timer),
            TIM_OCPreload_Enable, 2);
    }
    if (channals & 0b0100)
    {
        this->channal_3 = Timer::Channal{timertype, 3};
        this->channal_3.init();
        // 启用通道3预装载
        Timer::Channal::TIM_OCxPreloadConfig(
            reinterpret_cast<TIM_TypeDef *>(APB1PERIPH_BASE + 0x0400 * this->timer),
            TIM_OCPreload_Enable, 3);
    }
    if (channals & 0b1000)
    {
        this->channal_4 = Timer::Channal{timertype, 4};
        this->channal_4.init();
        // 启用通道4预装载
        Timer::Channal::TIM_OCxPreloadConfig(
            reinterpret_cast<TIM_TypeDef *>(APB1PERIPH_BASE + 0x0400 * this->timer),
            TIM_OCPreload_Enable, 4);
    }

    // 启用自动重装载预装载
    TIM_ARRPreloadConfig(reinterpret_cast<TIM_TypeDef *>(APB1PERIPH_BASE + 0x0400 * this->timer), ENABLE);

    // 启动定时器
    TIM_Cmd(reinterpret_cast<TIM_TypeDef *>(APB1PERIPH_BASE + 0x0400 * this->timer), ENABLE);
}

void Device::PWM::start()
{
    // 使能定时器
    TIM_Cmd(reinterpret_cast<TIM_TypeDef *>(APB1PERIPH_BASE + 0x0400 * this->timer), ENABLE);
}

void Device::PWM::stop()
{
    // 禁用定时器
    TIM_Cmd(reinterpret_cast<TIM_TypeDef *>(APB1PERIPH_BASE + 0x0400 * this->timer), DISABLE);
}

void Device::PWM::change(uint8_t channal, uint16_t _frequency, uint8_t _dutyRatio)
{
    TIM_TypeDef *TIMx = reinterpret_cast<TIM_TypeDef *>(APB1PERIPH_BASE + 0x0400 * this->timer);

    // 更新频率（改变ARR值）
    if (_frequency != frequency)
    {
        frequency = _frequency;
        uint16_t period = 1000000 / frequency - 1; // 假设主时钟已被分频到1MHz
        TIMx->ARR = period;
    }

    // 根据占空比设置比较值
    uint16_t pulse = (TIMx->ARR + 1) - (((TIMx->ARR + 1) * _dutyRatio) / 100);

    // 根据通道设置比较值
    switch (channal)
    {
    case 1:
        TIMx->CCR1 = pulse;
        break;
    case 2:
        TIMx->CCR2 = pulse;
        break;
    case 3:
        TIMx->CCR3 = pulse;
        break;
    case 4:
        TIMx->CCR4 = pulse;
        break;
    }
}
// 返回定时器的Rcc
uint32_t Device::PWM::getRcc()
{
    return APB2PERIPH_BASE + this->timer * 0x400;
}