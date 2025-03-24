#include "MyStm32.h"
#include "stm32f10x_rcc.h"

// Port类静态成员实现

// IO类静态成员实现
uint16_t IO::used[3] = {0, 0, 0};

// sign方法实现
// bool IO::sign(const GPIO_TypeDef *_port, const uint16_t _pin)
// {
//     int index = 0;
//     if (_port == Port::A)
//         index = 0;
//     else if (_port == Port::B)
//         index = 1;
//     else if (_port == Port::C)
//         index = 2;
//     else if (_port == Port::D)
//         index = 3;
//     if (used[index] & _pin)
//     {
//         return false;
//     }
//     else
//     {
//         used[index] &= _pin;
//         return true;
//     }
// }

// IO::init类实现
void IO::InitHelper::doInitPin(GPIO_TypeDef *port, uint16_t pin, GPIOMode_TypeDef mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(port, &GPIO_InitStructure);
}

// Port_Init类方法实现
void IO::InitHelper::Port_Init::Pin0(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_0, mode);
}

void IO::InitHelper::Port_Init::Pin1(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_1, mode);
}

void IO::InitHelper::Port_Init::Pin2(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_2, mode);
}

void IO::InitHelper::Port_Init::Pin3(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_3, mode);
}

void IO::InitHelper::Port_Init::Pin4(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_4, mode);
}

void IO::InitHelper::Port_Init::Pin5(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_5, mode);
}

void IO::InitHelper::Port_Init::Pin6(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_6, mode);
}

void IO::InitHelper::Port_Init::Pin7(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_7, mode);
}

void IO::InitHelper::Port_Init::Pin8(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_8, mode);
}

void IO::InitHelper::Port_Init::Pin9(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_9, mode);
}

void IO::InitHelper::Port_Init::Pin10(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_10, mode);
}

void IO::InitHelper::Port_Init::Pin11(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_11, mode);
}

void IO::InitHelper::Port_Init::Pin12(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_12, mode);
}

void IO::InitHelper::Port_Init::Pin13(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_13, mode);
}

void IO::InitHelper::Port_Init::Pin14(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_14, mode);
}

void IO::InitHelper::Port_Init::Pin15(GPIOMode_TypeDef mode) const
{
    doInitPin(port, GPIO_Pin_15, mode);
}

// IO::write类实现
void IO::WriteHelper::doWritePin(GPIO_TypeDef *port, uint16_t pin, BitAction value)
{
    GPIO_WriteBit(port, pin, value);
}

// Port_Write类方法实现
void IO::WriteHelper::Port_Write::Pin0(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_0, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin1(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_1, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin2(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_2, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin3(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_3, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin4(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_4, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin5(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_5, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin6(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_6, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin7(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_7, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin8(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_8, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin9(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_9, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin10(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_10, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin11(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_11, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin12(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_12, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin13(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_13, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin14(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_14, value != 0 ? Bit_SET : Bit_RESET);
}

void IO::WriteHelper::Port_Write::Pin15(uint8_t value) const
{
    doWritePin(port, GPIO_Pin_15, value != 0 ? Bit_SET : Bit_RESET);
}

// IO::read类实现
bool IO::ReadHelper::doReadPin(GPIO_TypeDef *port, uint16_t pin)
{
    return GPIO_ReadInputDataBit(port, pin) != 0;
}

// Port_read类方法实现
void IO::ReadHelper::Port_read::Pin0(uint8_t value) const { doReadPin(port, GPIO_Pin_0); }
void IO::ReadHelper::Port_read::Pin1(uint8_t value) const { doReadPin(port, GPIO_Pin_1); }
void IO::ReadHelper::Port_read::Pin2(uint8_t value) const { doReadPin(port, GPIO_Pin_2); }
void IO::ReadHelper::Port_read::Pin3(uint8_t value) const { doReadPin(port, GPIO_Pin_3); }
void IO::ReadHelper::Port_read::Pin4(uint8_t value) const { doReadPin(port, GPIO_Pin_4); }
void IO::ReadHelper::Port_read::Pin5(uint8_t value) const { doReadPin(port, GPIO_Pin_5); }
void IO::ReadHelper::Port_read::Pin6(uint8_t value) const { doReadPin(port, GPIO_Pin_6); }
void IO::ReadHelper::Port_read::Pin7(uint8_t value) const { doReadPin(port, GPIO_Pin_7); }
void IO::ReadHelper::Port_read::Pin8(uint8_t value) const { doReadPin(port, GPIO_Pin_8); }
void IO::ReadHelper::Port_read::Pin9(uint8_t value) const { doReadPin(port, GPIO_Pin_9); }
void IO::ReadHelper::Port_read::Pin10(uint8_t value) const { doReadPin(port, GPIO_Pin_10); }
void IO::ReadHelper::Port_read::Pin11(uint8_t value) const { doReadPin(port, GPIO_Pin_11); }
void IO::ReadHelper::Port_read::Pin12(uint8_t value) const { doReadPin(port, GPIO_Pin_12); }
void IO::ReadHelper::Port_read::Pin13(uint8_t value) const { doReadPin(port, GPIO_Pin_13); }
void IO::ReadHelper::Port_read::Pin14(uint8_t value) const { doReadPin(port, GPIO_Pin_14); }
void IO::ReadHelper::Port_read::Pin15(uint8_t value) const { doReadPin(port, GPIO_Pin_15); }

void IO::init_port(GPIO_TypeDef *port)
{
    clocks.open.port(port);
}

void IO::init_pin(GPIO_TypeDef *port, uint16_t pin, GPIOMode_TypeDef mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(port, &GPIO_InitStructure);
}

// IO静态辅助方法实现
uint16_t IO::read_port(GPIO_TypeDef *port)
{
    return GPIO_ReadInputData(port);
}

uint8_t IO::read_pin(GPIO_TypeDef *port, uint16_t pin)
{
    return GPIO_ReadInputDataBit(port, pin);
}

void IO::Write_port(GPIO_TypeDef *port, uint16_t val)
{
    GPIO_Write(port, val);
}

void IO::Write_pin(GPIO_TypeDef *port, uint16_t pin, bool val)
{
    GPIO_WriteBit(port, pin, val == true ? Bit_SET : Bit_RESET);
}

void IO::Write_pin(GPIO_TypeDef *port, uint16_t pin, BitAction val)
{
    GPIO_WriteBit(port, pin, val);
}

void IO::Change_pin(GPIO_TypeDef *port, uint16_t pin)
{
    IO::Write_pin(port, pin, !IO::read_pin(port, pin));
}

// 初始化静态实例
// IO io;

// Clock类方法实现
void Clock::Open::APB1Periph(uint32_t RCC_APB1Periph)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph, ENABLE);
}

void Clock::Open::APB2Periph(uint32_t RCC_APB2Periph)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
}

void Clock::Open::AHBPeriph(uint32_t AHBPe_RCCriph)
{
    RCC_AHBPeriphClockCmd(AHBPe_RCCriph, ENABLE);
}

void Clock::Open::port(GPIO_TypeDef *port)
{
    // GPIOA_BASE = APB2PERIPH_BASE + 0x0800;
    uint32_t portAddr = reinterpret_cast<uint32_t>(port);
    uint32_t offset = portAddr - APB2PERIPH_BASE;
    uint8_t index = offset / 0x0400;
    // 根据偏移量启用相应的时钟
    RCC_APB2PeriphClockCmd(1 << index, ENABLE);
}

void Clock::Close::APB1Periph(uint32_t RCC_APB1Periph)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph, DISABLE);
}

void Clock::Close::APB2Periph(uint32_t RCC_APB2Periph)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, DISABLE);
}

void Clock::Close::AHBPeriph(uint32_t RCC_AHBPeriph)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph, DISABLE);
}

void Clock::Close::port(GPIO_TypeDef *port)
{
    // GPIOA_BASE = APB2PERIPH_BASE + 0x0800;
    uint32_t portAddr = reinterpret_cast<uint32_t>(port);
    uint32_t offset = portAddr - APB2PERIPH_BASE;
    uint8_t index = offset / 0x0400;
    // 根据偏移量关闭相应的时钟
    RCC_APB2PeriphClockCmd(1 << index, DISABLE);
}

// 初始化静态实例
// Clock clocks;

// Device::Timer类实现
Device::Timer::Universal_timer::Universal_timer(uint8_t timerType, time_ms times)
    : index(timerType), BASIC_TIM((TIM_TypeDef *)(APB1PERIPH_BASE + (0x0400 * index)))
{
    NVIC_Config();
    TIM_Config(times.val);
}

Device::Timer::Universal_timer::Universal_timer(uint8_t timerType, time_s times)
    : index(timerType), BASIC_TIM(TIM2 + (0x0400) * (index))
{
    NVIC_Config();
    TIM_Config(times.val * 1000);
}

void Device::Timer::Universal_timer::NVIC_Config()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    // 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = index + 28;
    // 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void Device::Timer::Universal_timer::TIM_Config(uint16_t ms_time)
{
    // 两级分频方式来实现毫秒级定时
    // 第一级：72MHz / (71+1) = 1MHz（每微秒计数一次）
    uint16_t BASIC_TIM_Prescaler = 72 * 100 - 1;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    // 开启定时器时钟
    RCC_APB1PeriphClockCmd(((uint32_t)0x00000001) << (index), ENABLE);

    // 第二级：使用 Period 值设置中断周期
    // 例如设置 ms_time=500，则 Period=500-1=499
    // 表示500ms触发一次中断
    TIM_TimeBaseStructure.TIM_Period = ms_time * 10 - 1;

    // 预分频值（72分频得到1MHz计数频率）
    TIM_TimeBaseStructure.TIM_Prescaler = BASIC_TIM_Prescaler;

    // 时钟分频因子
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    // 向上计数模式
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    // 不使用重复计数
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    // 初始化定时器
    TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);

    // 清除计数器中断标志位
    TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);

    // 开启计数器中断
    TIM_ITConfig(BASIC_TIM, TIM_IT_Update, ENABLE);

    // 使能计数器
    TIM_Cmd(BASIC_TIM, ENABLE);
}

// Device::LED类实现
Device::LED::LED(GPIO_TypeDef *_port, uint16_t _pin,
                 GPIOSpeed_TypeDef Speed, GPIOMode_TypeDef mode)
    : pin(_pin), port(_port)
{
    // if (io.sign(_port, _pin))
    {
        clocks.open.port(_port);
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = pin;
        GPIO_InitStructure.GPIO_Mode = mode;
        GPIO_InitStructure.GPIO_Speed = Speed;
        GPIO_Init(port, &GPIO_InitStructure);
        io.Write_pin(port, pin, 0);
    }
}

void Device::LED::turn()
{
    io.Change_pin(this->port, this->pin);
}

void System::delay(time_s time)
{
    for (uint16_t i = 0; i < time; i++)
    {
        delay(1000_ms);
    }
}
void System::delay(time_ms time)
{
    for (uint16_t i = 0; i < time; i++)
    {
        delay(1000_us);
    }
}
void System::delay(time_us time)
{
    SysTick->LOAD = 72 * time;  // 设置定时器重装值
    SysTick->VAL = 0x00;        // 清空当前计数值
    SysTick->CTRL = 0x00000005; // 设置时钟源为HCLK，启动定时器
    while (!(SysTick->CTRL & 0x00010000))
        ;                       // 等待计数到0
    SysTick->CTRL = 0x00000004; // 关闭定时器
}
// 409500us 精度100us
void System::WatchDog::IndependWatchDog::setTime(time_us timeus) {
    IWDG_Init(0, 10000*timeus);
}
// 1628ms 精度:1/2500s(0.4ms)
void System::WatchDog::IndependWatchDog::setTime(time_ms timems) {
    IWDG_Init(2, 2500 * timems);
}
// LSI时钟频率：典型值约40KHz（实际范围为30-60KHz）下
// 预分频值最高为6（系数为4095）
// 最大重装载值4095
// max--26.21秒
// 精度1/156s(0.006s)
void System::WatchDog::IndependWatchDog::setTime(time_s times) {
  IWDG_Init(6, 156 * times);
}


void System::WatchDog::IndependWatchDog::feed(void) {
    IWDG_ReloadCounter();
}

void System::WatchDog::IndependWatchDog::IWDG_Init(u8 prer, u16 rlr)
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
