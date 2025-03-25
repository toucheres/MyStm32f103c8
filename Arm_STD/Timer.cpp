#include "Timer.h"
#include "MyStm32.h"

Device::Timer::Channal::Channal(uint8_t _timer, uint8_t _index)
    : timer(_timer), index(_index) {}

uint32_t Device::Timer::Channal::portRcc()
{
    return 1 << ((reinterpret_cast<uint32_t>(this->getPort()) - APB2PERIPH_BASE) / 0x400);
}

Device::Timer::Channal &Device::Timer::Channal::operator=(Timer::Channal &&that)
{
    this->timer = that.timer;
    this->index = that.index;
    return *this;
}
// 返回通道的引脚的pin
uint16_t Device::Timer::Channal::getPin()
{
    switch (this->timer)
    {
    case Timer::Universal_timer::TimerType::timer_2:
        switch (this->index)
        {
        case 1:
            return Pin::Pin0;
            break;
        case 2:
            return Pin::Pin1;
            break;
        case 3:
            return Pin::Pin2;
            break;
        case 4:
            return Pin::Pin3;
            break;
        default:
            // [TODO] more
            break;
        }
        break;
    case Timer::Universal_timer::TimerType::timer_3:
        switch (this->index)
        {
        case 1:
            return Pin::Pin6;
            break;
        case 2:
            return Pin::Pin7;
            break;
        case 3:
            return Pin::Pin0;
            break;
        case 4:
            return Pin::Pin1;
            break;
        default:
            // [TODO] more
            break;
        }
        break;
    case Timer::Universal_timer::TimerType::timer_4:
        switch (this->index)
        {
        case 1:
            return Pin::Pin6;
            break;
        case 2:
            return Pin::Pin7;
            break;
        case 3:
            return Pin::Pin8;
            break;
        case 4:
            return Pin::Pin9;
            break;
        default:
            // [TODO] more
            break;
        }
        break;
    default:
        break;
    }
    return 0;
}
// 返回通道引脚的port
GPIO_TypeDef *Device::Timer::Channal::getPort()
{
    switch (this->timer)
    {
    case Timer::Universal_timer::TimerType::timer_2:
        return GPIOA;
        break;
    case Timer::Universal_timer::TimerType::timer_3:
        if (this->index == 1 || this->index == 2)
            return GPIOA;
        else if (this->index == 3 || this->index == 4)
            return GPIOB;
        break;
    case Timer::Universal_timer::TimerType::timer_4:
        return GPIOB;
        break;
    default:
        break;
    }
    // [TODO]more
    return 0;
}

void Device::Timer::Channal::TIM_OCxInit(TIM_TypeDef *TIMx,
                                         TIM_OCInitTypeDef *TIM_OCInitStruct,
                                         uint8_t channel)
{
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
    uint16_t channelOffset = (channel - 1) * 4; // 每个通道在CCER寄存器中占4位

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(channel >= 1 && channel <= 4); // 检查通道号有效性
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

    /* 禁用指定通道：重置CCxE位 */
    TIMx->CCER &= (uint16_t)(~(TIM_CCER_CC1E << channelOffset));

    /* 获取TIMx CCER寄存器值 */
    tmpccer = TIMx->CCER;
    /* 获取TIMx CR2寄存器值 */
    tmpcr2 = TIMx->CR2;

    /* 根据通道选择适当的CCMR寄存器 */
    if (channel <= 2) // 通道1和2在CCMR1中
    {
        tmpccmrx = TIMx->CCMR1;

        /* 重置输出比较模式和捕获/比较选择位 */
        if (channel == 1)
        {
            tmpccmrx &= (uint16_t)(~TIM_CCMR1_OC1M);
            tmpccmrx &= (uint16_t)(~TIM_CCMR1_CC1S);
            /* 选择输出比较模式 */
            tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
        }
        else // channel == 2
        {
            tmpccmrx &= (uint16_t)(~TIM_CCMR1_OC2M);
            tmpccmrx &= (uint16_t)(~TIM_CCMR1_CC2S);
            /* 选择输出比较模式 */
            tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);
        }

        /* 写入TIMx CCMR1 */
        TIMx->CCMR1 = tmpccmrx;
    }
    else // 通道3和4在CCMR2中
    {
        tmpccmrx = TIMx->CCMR2;

        /* 重置输出比较模式和捕获/比较选择位 */
        if (channel == 3)
        {
            tmpccmrx &= (uint16_t)(~TIM_CCMR2_OC3M);
            tmpccmrx &= (uint16_t)(~TIM_CCMR2_CC3S);
            /* 选择输出比较模式 */
            tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
        }
        else // channel == 4
        {
            tmpccmrx &= (uint16_t)(~TIM_CCMR2_OC4M);
            tmpccmrx &= (uint16_t)(~TIM_CCMR2_CC4S);
            /* 选择输出比较模式 */
            tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);
        }

        /* 写入TIMx CCMR2 */
        TIMx->CCMR2 = tmpccmrx;
    }

    /* 重置输出极性 */
    tmpccer &= (uint16_t)(~(TIM_CCER_CC1P << channelOffset));
    /* 设置输出比较极性 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << channelOffset);

    /* 设置输出状态 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << channelOffset);

    /* 处理TIM1和TIM8的特殊功能（互补输出等） */
    if ((TIMx == TIM1) || (TIMx == TIM8) ||
        ((TIMx == TIM15 || TIMx == TIM16 || TIMx == TIM17) && channel == 1))
    {
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

        /* 仅TIM1/TIM8拥有互补输出 */
        if ((TIMx == TIM1) || (TIMx == TIM8))
        {
            /* 对于通道1、2、3，处理互补输出 */
            if (channel <= 3)
            {
                assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
                assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
                assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));

                /* 重置互补输出极性 */
                tmpccer &= (uint16_t)(~(TIM_CCER_CC1NP << channelOffset));
                /* 设置互补输出极性 */
                tmpccer |=
                    (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << channelOffset);

                /* 重置互补输出状态 */
                tmpccer &= (uint16_t)(~(TIM_CCER_CC1NE << channelOffset));
                /* 设置互补输出状态 */
                tmpccer |=
                    (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << channelOffset);

                /* 重置输出比较和互补输出比较的空闲状态 */
                tmpcr2 &= (uint16_t)(~(TIM_CR2_OIS1 << (channel * 2 - 2)));
                if (channel <= 3) // 只有通道1-3有互补输出
                {
                    tmpcr2 &= (uint16_t)(~(TIM_CR2_OIS1N << (channel * 2 - 2)));
                }

                /* 设置输出空闲状态 */
                tmpcr2 |=
                    (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << (channel * 2 - 2));
                if (channel <= 3) // 只有通道1-3有互补输出
                {
                    /* 设置互补输出空闲状态 */
                    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState
                                         << (channel * 2 - 2));
                }
            }
            else // channel == 4, 只处理空闲状态
            {
                /* 重置输出比较空闲状态 */
                tmpcr2 &= (uint16_t)(~TIM_CR2_OIS4);
                /* 设置输出空闲状态 */
                tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 6);
            }
        }
        else // TIM15/16/17, 只对通道1处理空闲状态
        {
            /* 重置输出比较空闲状态 */
            tmpcr2 &= (uint16_t)(~TIM_CR2_OIS1);
            /* 设置输出空闲状态 */
            tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;
        }
    }

    /* 写入TIMx CR2 */
    TIMx->CR2 = tmpcr2;

    /* 设置捕获比较寄存器值 */
    switch (channel)
    {
    case 1:
        TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse;
        break;
    case 2:
        TIMx->CCR2 = TIM_OCInitStruct->TIM_Pulse;
        break;
    case 3:
        TIMx->CCR3 = TIM_OCInitStruct->TIM_Pulse;
        break;
    case 4:
        TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;
        break;
    }

    /* 写入TIMx CCER */
    TIMx->CCER = tmpccer;
}

void Device::Timer::Channal::TIM_OCxPreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload, uint8_t channel)
{
    uint16_t tmpccmr = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
    assert_param(channel >= 1 && channel <= 4); // 检查通道号有效性

    if (channel <= 2) // 通道1和2使用CCMR1寄存器
    {
        tmpccmr = TIMx->CCMR1;

        if (channel == 1)
        {
            /* 重置OC1PE位 */
            tmpccmr &= (uint16_t)~((uint16_t)TIM_CCMR1_OC1PE);
            /* 启用或禁用输出比较预加载功能 */
            tmpccmr |= TIM_OCPreload;
        }
        else // channel == 2
        {
            /* 重置OC2PE位 */
            tmpccmr &= (uint16_t)~((uint16_t)TIM_CCMR1_OC2PE);
            /* 启用或禁用输出比较预加载功能（注意左移8位） */
            tmpccmr |= (uint16_t)(TIM_OCPreload << 8);
        }

        /* 写入TIMx CCMR1寄存器 */
        TIMx->CCMR1 = tmpccmr;
    }
    else // 通道3和4使用CCMR2寄存器
    {
        tmpccmr = TIMx->CCMR2;

        if (channel == 3)
        {
            /* 重置OC3PE位 */
            tmpccmr &= (uint16_t)~((uint16_t)TIM_CCMR2_OC3PE);
            /* 启用或禁用输出比较预加载功能 */
            tmpccmr |= TIM_OCPreload;
        }
        else // channel == 4
        {
            /* 重置OC4PE位 */
            tmpccmr &= (uint16_t)~((uint16_t)TIM_CCMR2_OC4PE);
            /* 启用或禁用输出比较预加载功能（注意左移8位） */
            tmpccmr |= (uint16_t)(TIM_OCPreload << 8);
        }

        /* 写入TIMx CCMR2寄存器 */
        TIMx->CCMR2 = tmpccmr;
    }
}
void Device::Timer::Channal::init()
{

    RCC_APB2PeriphClockCmd(this->portRcc(), ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitStructure.GPIO_Pin =
        this->getPin();                             // 定时器TIM4的PWM输出通道1，TIM4_CH1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(this->getPort(), &GPIO_InitStructure); // 初始化GPIO

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             // 设置PWM模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0;                            //
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     // 输出极性为高
    TIM_OCxInit(
        reinterpret_cast<TIM_TypeDef *>(APB1PERIPH_BASE + this->timer * 0x400),
        &TIM_OCInitStructure, this->index);
}
