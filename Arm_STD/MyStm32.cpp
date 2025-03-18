#include "MyStm32.h"
#include <stdarg.h>
#include <string.h>
extern "C"
{
#include "OLED_Data.h"
}
// Port类静态成员实现
GPIO_TypeDef *const Port::A = GPIOA;
GPIO_TypeDef *const Port::B = GPIOB;
GPIO_TypeDef *const Port::C = GPIOC;
GPIO_TypeDef *const Port::D = GPIOD;
GPIO_TypeDef *const Port::E = GPIOE;
GPIO_TypeDef *const Port::F = GPIOF;
GPIO_TypeDef *const Port::G = GPIOG;

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

// Device::OLED类实现 - 基础部分
Device::OLED::OLED(GPIO_TypeDef *_SCL_port, uint16_t _SCL_pin,
                   GPIO_TypeDef *_SDA_port, uint16_t _SDA_pin)
    : SCL_port(_SCL_port), SCL_pin(_SCL_pin), SDA_port(_SDA_port), SDA_pin(_SDA_pin)
{
}

void Device::OLED::W_SCL(uint8_t BitValue)
{
    GPIO_WriteBit(SCL_port, SCL_pin, (BitAction)BitValue);
}

void Device::OLED::W_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(SDA_port, SDA_pin, (BitAction)BitValue);
}

uint32_t Device::OLED::GPIOX_to_RCC(GPIO_TypeDef *GPIOX)
{
    return 1 << ((reinterpret_cast<uint32_t>(GPIOX) - APB2PERIPH_BASE) / 0x0400);
}

void Device::OLED::OLED_GPIO_Init(void)
{
    uint32_t i, j;

    // 初始化前延时，等待OLED供电稳定
    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 1000; j++)
            ;
    }

    // 将SCL和SDA初始化为开漏模式
    RCC_APB2PeriphClockCmd(GPIOX_to_RCC(SCL_port), ENABLE);
    RCC_APB2PeriphClockCmd(GPIOX_to_RCC(SDA_port), ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = SCL_pin;
    GPIO_Init(SCL_port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = SDA_pin;
    GPIO_Init(SDA_port, &GPIO_InitStructure);

    // 释放SCL和SDA
    W_SCL(1);
    W_SDA(1);
}

// I2C通信协议实现
void Device::OLED::I2C_Start(void)
{
    W_SDA(1); // 释放SDA
    W_SCL(1); // 释放SCL
    W_SDA(0); // 在SCL高电平期间，拉低SDA，产生起始信号
    W_SCL(0); // 起始后拉低SCL，占用总线
}

void Device::OLED::I2C_Stop(void)
{
    W_SDA(0); // 拉低SDA
    W_SCL(1); // 释放SCL
    W_SDA(1); // 在SCL高电平期间，释放SDA，产生终止信号
}

void Device::OLED::I2C_SendByte(uint8_t Byte)
{
    uint8_t i;

    // 依次发送每一位数据
    for (i = 0; i < 8; i++)
    {
        W_SDA(!!(Byte & (0x80 >> i)));
        W_SCL(1); // 释放SCL，从机在SCL高电平期间读取SDA
        W_SCL(0); // 拉低SCL，准备发送下一位
    }

    W_SCL(1); // 额外的一个时钟，不处理应答信号
    W_SCL(0);
}

void Device::OLED::WriteCommand(uint8_t Command)
{
    I2C_Start();           // I2C起始
    I2C_SendByte(0x78);    // 发送OLED的I2C从机地址
    I2C_SendByte(0x00);    // 控制字节，表示即将写命令
    I2C_SendByte(Command); // 写入指定的命令
    I2C_Stop();            // I2C终止
}

void Device::OLED::WriteData(uint8_t *Data, uint8_t Count)
{
    uint8_t i;

    I2C_Start();        // I2C起始
    I2C_SendByte(0x78); // 发送OLED的I2C从机地址
    I2C_SendByte(0x40); // 控制字节，表示即将写数据

    // 连续写入指定数量的数据
    for (i = 0; i < Count; i++)
    {
        I2C_SendByte(Data[i]);
    }
    I2C_Stop(); // I2C终止
}

void Device::OLED::Init(void)
{
    OLED_GPIO_Init(); // 先调用端口初始化

    // 发送一系列初始化命令
    WriteCommand(0xAE); // 关闭显示

    WriteCommand(0xD5); // 设置显示时钟分频比/振荡器频率
    WriteCommand(0x80);

    WriteCommand(0xA8); // 设置多路复用率
    WriteCommand(0x3F);

    WriteCommand(0xD3); // 设置显示偏移
    WriteCommand(0x00);

    WriteCommand(0x40); // 设置显示开始行

    WriteCommand(0xA1); // 设置左右方向，0xA1正常，0xA0左右反置

    WriteCommand(0xC8); // 设置上下方向，0xC8正常，0xC0上下反置

    WriteCommand(0xDA); // 设置COM引脚硬件配置
    WriteCommand(0x12);

    WriteCommand(0x81); // 设置对比度
    WriteCommand(0xCF);

    WriteCommand(0xD9); // 设置预充电周期
    WriteCommand(0xF1);

    WriteCommand(0xDB); // 设置VCOMH取消选择级别
    WriteCommand(0x30);

    WriteCommand(0xA4); // 设置整个显示打开/关闭

    WriteCommand(0xA6); // 设置正常/反色显示，0xA6正常，0xA7反色

    WriteCommand(0x8D); // 设置充电泵
    WriteCommand(0x14);

    WriteCommand(0xAF); // 开启显示

    Clear();  // 清空显存数组
    Update(); // 更新显示，清屏
}

void Device::OLED::SetCursor(uint8_t Page, uint8_t X)
{
    // 通过指令设置页地址和列地址
    WriteCommand(0xB0 | Page);              // 设置页位置
    WriteCommand(0x10 | ((X & 0xF0) >> 4)); // 设置X位置高4位
    WriteCommand(0x00 | (X & 0x0F));        // 设置X位置低4位
}

// 工具函数实现
uint32_t Device::OLED::Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--)
    {
        Result *= X;
    }
    return Result;
}

uint8_t Device::OLED::pnpoly(uint8_t nvert, int16_t *vertx, int16_t *verty, int16_t testx, int16_t testy)
{
    int16_t i, j, c = 0;

    // W. Randolph Franklin点包含算法
    for (i = 0, j = nvert - 1; i < nvert; j = i++)
    {
        if (((verty[i] > testy) != (verty[j] > testy)) &&
            (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
        {
            c = !c;
        }
    }
    return c;
}

uint8_t Device::OLED::IsInAngle(int16_t X, int16_t Y, int16_t StartAngle, int16_t EndAngle)
{
    int16_t PointAngle;
    PointAngle = atan2(Y, X) / 3.14 * 180; // 计算指定点的角度

    if (StartAngle < EndAngle) // 起始角度小于终止角度
    {
        // 如果点角度在起始和终止角度之间，则在指定角度内
        if (PointAngle >= StartAngle && PointAngle <= EndAngle)
        {
            return 1;
        }
    }
    else // 起始角度大于终止角度
    {
        // 如果点角度大于起始角度或小于终止角度，则在指定角度内
        if (PointAngle >= StartAngle || PointAngle <= EndAngle)
        {
            return 1;
        }
    }
    return 0; // 不满足条件，不在指定角度内
}

// 显示控制实现
void Device::OLED::Update(void)
{
    uint8_t j;
    // 遍历每一页，发送显存数据
    for (j = 0; j < 8; j++)
    {
        SetCursor(j, 0);
        WriteData(DisplayBuf[j], 128);
    }
}

void Device::OLED::UpdateArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height)
{
    int16_t j;
    int16_t Page, Page1;

    // 计算起始页和结束页
    Page = Y / 8;
    Page1 = (Y + Height - 1) / 8 + 1;
    if (Y < 0)
    {
        Page -= 1;
        Page1 -= 1;
    }

    // 遍历相关页，更新指定区域显示
    for (j = Page; j < Page1; j++)
    {
        if (X >= 0 && X <= 127 && j >= 0 && j <= 7)
        {
            SetCursor(j, X);
            WriteData(&DisplayBuf[j][X], Width);
        }
    }
}

// OLED显示控制方法实现
void Device::OLED::Clear(void)
{
    uint8_t i, j;
    for (j = 0; j < 8; j++) // 遍历8页
    {
        for (i = 0; i < 128; i++) // 遍历128列
        {
            DisplayBuf[j][i] = 0x00; // 将显存数组数据全部清零
        }
    }
}

void Device::OLED::ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height)
{
    int16_t i, j;

    for (j = Y; j < Y + Height; j++) // 遍历指定页
    {
        for (i = X; i < X + Width; i++) // 遍历指定列
        {
            if (i >= 0 && i <= 127 && j >= 0 && j <= 63) // 超出屏幕的内容不显示
            {
                DisplayBuf[j / 8][i] &= ~(0x01 << (j % 8)); // 将显存数组指定数据清零
            }
        }
    }
}

void Device::OLED::Reverse(void)
{
    uint8_t i, j;
    for (j = 0; j < 8; j++) // 遍历8页
    {
        for (i = 0; i < 128; i++) // 遍历128列
        {
            DisplayBuf[j][i] ^= 0xFF; // 将显存数组数据全部取反
        }
    }
}

void Device::OLED::ReverseArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height)
{
    int16_t i, j;

    for (j = Y; j < Y + Height; j++) // 遍历指定页
    {
        for (i = X; i < X + Width; i++) // 遍历指定列
        {
            if (i >= 0 && i <= 127 && j >= 0 && j <= 63) // 超出屏幕的内容不显示
            {
                DisplayBuf[j / 8][i] ^= 0x01 << (j % 8); // 将显存数组指定数据取反
            }
        }
    }
}

// OLED文本显示方法实现
void Device::OLED::ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize)
{
    if (FontSize == OLED_8X16) // 字体为宽8像素，高16像素
    {
        /*将ASCII字模库F8x16的指定数据以8*16的图像格式显示*/
        ShowImage(X, Y, 8, 16, OLED_F8x16[Char - ' ']);
    }
    else if (FontSize == OLED_6X8) // 字体为宽6像素，高8像素
    {
        /*将ASCII字模库F6x8的指定数据以6*8的图像格式显示*/
        ShowImage(X, Y, 6, 8, OLED_F6x8[Char - ' ']);
    }
}

void Device::OLED::ShowString(int16_t X, int16_t Y, const char *String, uint8_t FontSize)
{
    uint16_t i = 0;
    char SingleChar[5];
    uint8_t CharLength = 0;
    uint16_t XOffset = 0;
    uint16_t pIndex;

    while (String[i] != '\0') // 遍历字符串
    {
        /*此段代码的目的是，提取GB2312字符串中的一个字符，转存到SingleChar子字符串中*/
        /*判断GB2312字节的最高位标志位*/
        if ((String[i] & 0x80) == 0x00) // 最高位为0
        {
            CharLength = 1;              // 字符为1字节
            SingleChar[0] = String[i++]; // 将第一个字节写入SingleChar第0个位置，随后i指向下一个字节
            SingleChar[1] = '\0';        // 为SingleChar添加字符串结束标志位
        }
        else // 最高位为1
        {
            CharLength = 2;              // 字符为2字节
            SingleChar[0] = String[i++]; // 将第一个字节写入SingleChar第0个位置，随后i指向下一个字节
            if (String[i] == '\0')
            {
                break;
            } // 意外情况，跳出循环，结束显示
            SingleChar[1] = String[i++]; // 将第二个字节写入SingleChar第1个位置，随后i指向下一个字节
            SingleChar[2] = '\0';        // 为SingleChar添加字符串结束标志位
        }

        /*显示上述代码提取到的SingleChar*/
        if (CharLength == 1) // 如果是单字节字符
        {
            /*使用ShowChar显示此字符*/
            ShowChar(X + XOffset, Y, SingleChar[0], FontSize);
            XOffset += FontSize;
        }
        else // 否则，即多字节字符
        {
            /*遍历整个字模库，从字模库中寻找此字符的数据*/
            /*如果找到最后一个字符（定义为空字符串），则表示字符未在字模库定义，停止寻找*/
            for (pIndex = 0; strcmp(OLED_CF16x16[pIndex].Index, "") != 0; pIndex++)
            {
                /*找到匹配的字符*/
                if (strcmp(OLED_CF16x16[pIndex].Index, SingleChar) == 0)
                {
                    break; // 跳出循环，此时pIndex的值为指定字符的索引
                }
            }
            if (FontSize == OLED_8X16) // 给定字体为8*16点阵
            {
                /*将字模库CF16x16的指定数据以16*16的图像格式显示*/
                ShowImage(X + XOffset, Y, 16, 16, OLED_CF16x16[pIndex].Data);
                XOffset += 16;
            }
            else if (FontSize == OLED_6X8) // 给定字体为6*8点阵
            {
                /*空间不足，此位置显示'?'*/
                ShowChar(X + XOffset, Y, '?', OLED_6X8);
                XOffset += OLED_6X8;
            }
        }
    }
}

void Device::OLED::ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
    uint8_t i;
    for (i = 0; i < Length; i++) // 遍历数字的每一位
    {
        /*调用ShowChar函数，依次显示每个数字*/
        /*Number / Pow(10, Length - i - 1) % 10 可以十进制提取数字的每一位*/
        /*+ '0' 可将数字转换为字符格式*/
        ShowChar(X + i * FontSize, Y, Number / Pow(10, Length - i - 1) % 10 + '0', FontSize);
    }
}

void Device::OLED::ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize)
{
    uint8_t i;
    uint32_t Number1;

    if (Number >= 0) // 数字大于等于0
    {
        ShowChar(X, Y, '+', FontSize); // 显示+号
        Number1 = Number;              // Number1直接等于Number
    }
    else // 数字小于0
    {
        ShowChar(X, Y, '-', FontSize); // 显示-号
        Number1 = -Number;             // Number1等于Number取负
    }

    for (i = 0; i < Length; i++) // 遍历数字的每一位
    {
        /*调用ShowChar函数，依次显示每个数字*/
        /*Number1 / Pow(10, Length - i - 1) % 10 可以十进制提取数字的每一位*/
        /*+ '0' 可将数字转换为字符格式*/
        ShowChar(X + (i + 1) * FontSize, Y, Number1 / Pow(10, Length - i - 1) % 10 + '0', FontSize);
    }
}

void Device::OLED::ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
    uint8_t i, SingleNumber;
    for (i = 0; i < Length; i++) // 遍历数字的每一位
    {
        /*以十六进制提取数字的每一位*/
        SingleNumber = Number / Pow(16, Length - i - 1) % 16;

        if (SingleNumber < 10) // 单个数字小于10
        {
            /*调用ShowChar函数，显示此数字*/
            /*+ '0' 可将数字转换为字符格式*/
            ShowChar(X + i * FontSize, Y, SingleNumber + '0', FontSize);
        }
        else // 单个数字大于10
        {
            /*调用ShowChar函数，显示此数字*/
            /*+ 'A' 可将数字转换为从A开始的十六进制字符*/
            ShowChar(X + i * FontSize, Y, SingleNumber - 10 + 'A', FontSize);
        }
    }
}

void Device::OLED::ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
    uint8_t i;
    for (i = 0; i < Length; i++) // 遍历数字的每一位
    {
        /*调用ShowChar函数，依次显示每个数字*/
        /*Number / Pow(2, Length - i - 1) % 2 可以二进制提取数字的每一位*/
        /*+ '0' 可将数字转换为字符格式*/
        ShowChar(X + i * FontSize, Y, Number / Pow(2, Length - i - 1) % 2 + '0', FontSize);
    }
}

void Device::OLED::ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize)
{
    uint32_t PowNum, IntNum, FraNum;

    if (Number >= 0) // 数字大于等于0
    {
        ShowChar(X, Y, '+', FontSize); // 显示+号
    }
    else // 数字小于0
    {
        ShowChar(X, Y, '-', FontSize); // 显示-号
        Number = -Number;              // Number取负
    }

    /*提取整数部分和小数部分*/
    IntNum = Number;                 // 直接赋值给整型变量，提取整数
    Number -= IntNum;                // 将Number的整数减掉，防止之后将小数乘到整数时因数过大造成错误
    PowNum = Pow(10, FraLength);     // 根据指定小数的位数，确定乘数
    FraNum = round(Number * PowNum); // 将小数乘到整数，同时四舍五入，避免显示误差
    IntNum += FraNum / PowNum;       // 若四舍五入造成了进位，则需要再加给整数

    /*显示整数部分*/
    ShowNum(X + FontSize, Y, IntNum, IntLength, FontSize);

    /*显示小数点*/
    ShowChar(X + (IntLength + 1) * FontSize, Y, '.', FontSize);

    /*显示小数部分*/
    ShowNum(X + (IntLength + 2) * FontSize, Y, FraNum, FraLength, FontSize);
}

void Device::OLED::ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image)
{
    uint8_t i = 0, j = 0;
    int16_t Page, Shift;

    /*将图像所在区域清空*/
    ClearArea(X, Y, Width, Height);

    /*遍历指定图像涉及的相关页*/
    /*(Height - 1) / 8 + 1的目的是Height / 8并向上取整*/
    for (j = 0; j < (Height - 1) / 8 + 1; j++)
    {
        /*遍历指定图像涉及的相关列*/
        for (i = 0; i < Width; i++)
        {
            if (X + i >= 0 && X + i <= 127) // 超出屏幕的内容不显示
            {
                /*负数坐标在计算页地址和移位时需要加一个偏移*/
                Page = Y / 8;
                Shift = Y % 8;
                if (Y < 0)
                {
                    Page -= 1;
                    Shift += 8;
                }

                if (Page + j >= 0 && Page + j <= 7) // 超出屏幕的内容不显示
                {
                    /*显示图像在当前页的内容*/
                    DisplayBuf[Page + j][X + i] |= Image[j * Width + i] << (Shift);
                }

                if (Page + j + 1 >= 0 && Page + j + 1 <= 7) // 超出屏幕的内容不显示
                {
                    /*显示图像在下一页的内容*/
                    DisplayBuf[Page + j + 1][X + i] |= Image[j * Width + i] >> (8 - Shift);
                }
            }
        }
    }
}

void Device::OLED::Printf(int16_t X, int16_t Y, uint8_t FontSize, char *format, ...)
{
    char String[256];                   // 定义字符数组
    va_list arg;                        // 定义可变参数列表数据类型的变量arg
    va_start(arg, format);              // 从format开始，接收参数列表到arg变量
    vsprintf(String, format, arg);      // 使用vsprintf打印格式化字符串和参数列表到字符数组中
    va_end(arg);                        // 结束变量arg
    ShowString(X, Y, String, FontSize); // OLED显示字符数组（字符串）
}

void Device::OLED::DrawPoint(int16_t X, int16_t Y)
{
    if (X >= 0 && X <= 127 && Y >= 0 && Y <= 63) // 超出屏幕的内容不显示
    {
        /*将显存数组指定位置的一个Bit数据置1*/
        DisplayBuf[Y / 8][X] |= 0x01 << (Y % 8);
    }
}

uint8_t Device::OLED::GetPoint(int16_t X, int16_t Y)
{
    if (X >= 0 && X <= 127 && Y >= 0 && Y <= 63) // 超出屏幕的内容不读取
    {
        /*判断指定位置的数据*/
        if (DisplayBuf[Y / 8][X] & 0x01 << (Y % 8))
        {
            return 1; // 为1，返回1
        }
    }

    return 0; // 否则，返回0
}

// OLED绘图方法实现
void Device::OLED::DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1)
{
    int16_t x, y, dx, dy, d, incrE, incrNE, temp;
    int16_t x0 = X0, y0 = Y0, x1 = X1, y1 = Y1;
    uint8_t yflag = 0, xyflag = 0;

    if (y0 == y1) // 横线单独处理
    {
        /*0号点X坐标大于1号点X坐标，则交换两点X坐标*/
        if (x0 > x1)
        {
            temp = x0;
            x0 = x1;
            x1 = temp;
        }

        /*遍历X坐标*/
        for (x = x0; x <= x1; x++)
        {
            DrawPoint(x, y0); // 依次画点
        }
    }
    else if (x0 == x1) // 竖线单独处理
    {
        /*0号点Y坐标大于1号点Y坐标，则交换两点Y坐标*/
        if (y0 > y1)
        {
            temp = y0;
            y0 = y1;
            y1 = temp;
        }

        /*遍历Y坐标*/
        for (y = y0; y <= y1; y++)
        {
            DrawPoint(x0, y); // 依次画点
        }
    }
    else // 斜线
    {
        /*使用Bresenham算法画直线，可以避免耗时的浮点运算，效率更高*/
        /*参考文档：https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
        /*参考教程：https://www.bilibili.com/video/BV1364y1d7Lo*/

        if (x0 > x1) // 0号点X坐标大于1号点X坐标
        {
            /*交换两点坐标*/
            /*交换后不影响画线，但是画线方向由第一、二、三、四象限变为第一、四象限*/
            temp = x0;
            x0 = x1;
            x1 = temp;
            temp = y0;
            y0 = y1;
            y1 = temp;
        }

        if (y0 > y1) // 0号点Y坐标大于1号点Y坐标
        {
            /*将Y坐标取负*/
            /*取负后影响画线，但是画线方向由第一、四象限变为第一象限*/
            y0 = -y0;
            y1 = -y1;

            /*置标志位yflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
            yflag = 1;
        }

        if (y1 - y0 > x1 - x0) // 画线斜率大于1
        {
            /*将X坐标与Y坐标互换*/
            /*互换后影响画线，但是画线方向由第一象限0~90度范围变为第一象限0~45度范围*/
            temp = x0;
            x0 = y0;
            y0 = temp;
            temp = x1;
            x1 = y1;
            y1 = temp;

            /*置标志位xyflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
            xyflag = 1;
        }

        /*以下为Bresenham算法画直线*/
        /*算法要求，画线方向必须为第一象限0~45度范围*/
        dx = x1 - x0;
        dy = y1 - y0;
        incrE = 2 * dy;
        incrNE = 2 * (dy - dx);
        d = 2 * dy - dx;
        x = x0;
        y = y0;

        /*画起始点，同时判断标志位，将坐标换回来*/
        if (yflag && xyflag)
        {
            DrawPoint(y, -x);
        }
        else if (yflag)
        {
            DrawPoint(x, -y);
        }
        else if (xyflag)
        {
            DrawPoint(y, x);
        }
        else
        {
            DrawPoint(x, y);
        }

        while (x < x1) // 遍历X轴的每个点
        {
            x++;
            if (d < 0) // 下一个点在当前点东方
            {
                d += incrE;
            }
            else // 下一个点在当前点东北方
            {
                y++;
                d += incrNE;
            }

            /*画每一个点，同时判断标志位，将坐标换回来*/
            if (yflag && xyflag)
            {
                DrawPoint(y, -x);
            }
            else if (yflag)
            {
                DrawPoint(x, -y);
            }
            else if (xyflag)
            {
                DrawPoint(y, x);
            }
            else
            {
                DrawPoint(x, y);
            }
        }
    }
}

void Device::OLED::DrawRectangle(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled)
{
    int16_t i, j;
    if (!IsFilled) // 指定矩形不填充
    {
        /*遍历上下X坐标，画矩形上下两条线*/
        for (i = X; i < X + Width; i++)
        {
            DrawPoint(i, Y);
            DrawPoint(i, Y + Height - 1);
        }
        /*遍历左右Y坐标，画矩形左右两条线*/
        for (i = Y; i < Y + Height; i++)
        {
            DrawPoint(X, i);
            DrawPoint(X + Width - 1, i);
        }
    }
    else // 指定矩形填充
    {
        /*遍历X坐标*/
        for (i = X; i < X + Width; i++)
        {
            /*遍历Y坐标*/
            for (j = Y; j < Y + Height; j++)
            {
                /*在指定区域画点，填充满矩形*/
                DrawPoint(i, j);
            }
        }
    }
}

void Device::OLED::DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled)
{
    int16_t minx = X0, miny = Y0, maxx = X0, maxy = Y0;
    int16_t i, j;
    int16_t vx[] = {X0, X1, X2};
    int16_t vy[] = {Y0, Y1, Y2};

    if (!IsFilled) // 指定三角形不填充
    {
        /*调用画线函数，将三个点用直线连接*/
        DrawLine(X0, Y0, X1, Y1);
        DrawLine(X0, Y0, X2, Y2);
        DrawLine(X1, Y1, X2, Y2);
    }
    else // 指定三角形填充
    {
        /*找到三个点最小的X、Y坐标*/
        if (X1 < minx)
        {
            minx = X1;
        }
        if (X2 < minx)
        {
            minx = X2;
        }
        if (Y1 < miny)
        {
            miny = Y1;
        }
        if (Y2 < miny)
        {
            miny = Y2;
        }

        /*找到三个点最大的X、Y坐标*/
        if (X1 > maxx)
        {
            maxx = X1;
        }
        if (X2 > maxx)
        {
            maxx = X2;
        }
        if (Y1 > maxy)
        {
            maxy = Y1;
        }
        if (Y2 > maxy)
        {
            maxy = Y2;
        }

        /*最小最大坐标之间的矩形为可能需要填充的区域*/
        /*遍历此区域中所有的点*/
        /*遍历X坐标*/
        for (i = minx; i <= maxx; i++)
        {
            /*遍历Y坐标*/
            for (j = miny; j <= maxy; j++)
            {
                /*调用pnpoly，判断指定点是否在指定三角形之中*/
                /*如果在，则画点，如果不在，则不做处理*/
                if (pnpoly(3, vx, vy, i, j))
                {
                    DrawPoint(i, j);
                }
            }
        }
    }
}

void Device::OLED::DrawCircle(int16_t X, int16_t Y, uint8_t Radius, uint8_t IsFilled)
{
    int16_t x, y, d, j;

    /*使用Bresenham算法画圆，可以避免耗时的浮点运算，效率更高*/
    /*参考文档：https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
    /*参考教程：https://www.bilibili.com/video/BV1VM4y1u7wJ*/

    d = 1 - Radius;
    x = 0;
    y = Radius;

    /*画每个八分之一圆弧的起始点*/
    DrawPoint(X + x, Y + y);
    DrawPoint(X - x, Y - y);
    DrawPoint(X + y, Y + x);
    DrawPoint(X - y, Y - x);

    if (IsFilled) // 指定圆填充
    {
        /*遍历起始点Y坐标*/
        for (j = -y; j < y; j++)
        {
            /*在指定区域画点，填充部分圆*/
            DrawPoint(X, Y + j);
        }
    }

    while (x < y) // 遍历X轴的每个点
    {
        x++;
        if (d < 0) // 下一个点在当前点东方
        {
            d += 2 * x + 1;
        }
        else // 下一个点在当前点东南方
        {
            y--;
            d += 2 * (x - y) + 1;
        }

        /*画每个八分之一圆弧的点*/
        DrawPoint(X + x, Y + y);
        DrawPoint(X + y, Y + x);
        DrawPoint(X - x, Y - y);
        DrawPoint(X - y, Y - x);
        DrawPoint(X + x, Y - y);
        DrawPoint(X + y, Y - x);
        DrawPoint(X - x, Y + y);
        DrawPoint(X - y, Y + x);

        if (IsFilled) // 指定圆填充
        {
            /*遍历中间部分*/
            for (j = -y; j < y; j++)
            {
                /*在指定区域画点，填充部分圆*/
                DrawPoint(X + x, Y + j);
                DrawPoint(X - x, Y + j);
            }

            /*遍历两侧部分*/
            for (j = -x; j < x; j++)
            {
                /*在指定区域画点，填充部分圆*/
                DrawPoint(X - y, Y + j);
                DrawPoint(X + y, Y + j);
            }
        }
    }
}

void Device::OLED::DrawEllipse(int16_t X, int16_t Y, uint8_t A, uint8_t B, uint8_t IsFilled)
{
    int16_t x, y, j;
    int16_t a = A, b = B;
    float d1, d2;

    /*使用Bresenham算法画椭圆，可以避免部分耗时的浮点运算，效率更高*/
    /*参考链接：https://blog.csdn.net/myf_666/article/details/128167392*/

    x = 0;
    y = b;
    d1 = b * b + a * a * (-b + 0.5);

    if (IsFilled) // 指定椭圆填充
    {
        /*遍历起始点Y坐标*/
        for (j = -y; j < y; j++)
        {
            /*在指定区域画点，填充部分椭圆*/
            DrawPoint(X, Y + j);
            DrawPoint(X, Y + j);
        }
    }

    /*画椭圆弧的起始点*/
    DrawPoint(X + x, Y + y);
    DrawPoint(X - x, Y - y);
    DrawPoint(X - x, Y + y);
    DrawPoint(X + x, Y - y);

    /*画椭圆中间部分*/
    while (b * b * (x + 1) < a * a * (y - 0.5))
    {
        if (d1 <= 0) // 下一个点在当前点东方
        {
            d1 += b * b * (2 * x + 3);
        }
        else // 下一个点在当前点东南方
        {
            d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            y--;
        }
        x++;

        if (IsFilled) // 指定椭圆填充
        {
            /*遍历中间部分*/
            for (j = -y; j < y; j++)
            {
                /*在指定区域画点，填充部分椭圆*/
                DrawPoint(X + x, Y + j);
                DrawPoint(X - x, Y + j);
            }
        }

        /*画椭圆中间部分圆弧*/
        DrawPoint(X + x, Y + y);
        DrawPoint(X - x, Y - y);
        DrawPoint(X - x, Y + y);
        DrawPoint(X + x, Y - y);
    }

    /*画椭圆两侧部分*/
    d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;

    while (y > 0)
    {
        if (d2 <= 0) // 下一个点在当前点东方
        {
            d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
        }
        else // 下一个点在当前点东南方
        {
            d2 += a * a * (-2 * y + 3);
        }
        y--;

        if (IsFilled) // 指定椭圆填充
        {
            /*遍历两侧部分*/
            for (j = -y; j < y; j++)
            {
                /*在指定区域画点，填充部分椭圆*/
                DrawPoint(X + x, Y + j);
                DrawPoint(X - x, Y + j);
            }
        }

        /*画椭圆两侧部分圆弧*/
        DrawPoint(X + x, Y + y);
        DrawPoint(X - x, Y - y);
        DrawPoint(X - x, Y + y);
        DrawPoint(X + x, Y - y);
    }
}

void Device::OLED::DrawArc(int16_t X, int16_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled)
{
    int16_t x, y, d, j;

    /*此函数借用Bresenham算法画圆的方法*/

    d = 1 - Radius;
    x = 0;
    y = Radius;

    /*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
    if (IsInAngle(x, y, StartAngle, EndAngle))
    {
        DrawPoint(X + x, Y + y);
    }
    if (IsInAngle(-x, -y, StartAngle, EndAngle))
    {
        DrawPoint(X - x, Y - y);
    }
    if (IsInAngle(y, x, StartAngle, EndAngle))
    {
        DrawPoint(X + y, Y + x);
    }
    if (IsInAngle(-y, -x, StartAngle, EndAngle))
    {
        DrawPoint(X - y, Y - x);
    }

    if (IsFilled) // 指定圆弧填充
    {
        /*遍历起始点Y坐标*/
        for (j = -y; j < y; j++)
        {
            /*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
            if (IsInAngle(0, j, StartAngle, EndAngle))
            {
                DrawPoint(X, Y + j);
            }
        }
    }

    while (x < y) // 遍历X轴的每个点
    {
        x++;
        if (d < 0) // 下一个点在当前点东方
        {
            d += 2 * x + 1;
        }
        else // 下一个点在当前点东南方
        {
            y--;
            d += 2 * (x - y) + 1;
        }

        /*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
        if (IsInAngle(x, y, StartAngle, EndAngle))
        {
            DrawPoint(X + x, Y + y);
        }
        if (IsInAngle(y, x, StartAngle, EndAngle))
        {
            DrawPoint(X + y, Y + x);
        }
        if (IsInAngle(-x, -y, StartAngle, EndAngle))
        {
            DrawPoint(X - x, Y - y);
        }
        if (IsInAngle(-y, -x, StartAngle, EndAngle))
        {
            DrawPoint(X - y, Y - x);
        }
        if (IsInAngle(x, -y, StartAngle, EndAngle))
        {
            DrawPoint(X + x, Y - y);
        }
        if (IsInAngle(y, -x, StartAngle, EndAngle))
        {
            DrawPoint(X + y, Y - x);
        }
        if (IsInAngle(-x, y, StartAngle, EndAngle))
        {
            DrawPoint(X - x, Y + y);
        }
        if (IsInAngle(-y, x, StartAngle, EndAngle))
        {
            DrawPoint(X - y, Y + x);
        }

        if (IsFilled) // 指定圆弧填充
        {
            /*遍历中间部分*/
            for (j = -y; j < y; j++)
            {
                /*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
                if (IsInAngle(x, j, StartAngle, EndAngle))
                {
                    DrawPoint(X + x, Y + j);
                }
                if (IsInAngle(-x, j, StartAngle, EndAngle))
                {
                    DrawPoint(X - x, Y + j);
                }
            }

            /*遍历两侧部分*/
            for (j = -x; j < x; j++)
            {
                /*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
                if (IsInAngle(-y, j, StartAngle, EndAngle))
                {
                    DrawPoint(X - y, Y + j);
                }
                if (IsInAngle(y, j, StartAngle, EndAngle))
                {
                    DrawPoint(X + y, Y + j);
                }
            }
        }
    }
}

// // OLED_类实现
// Device::OLED_::OLED_()
// {
//     OLED_Init();
// }

// void Device::OLED_::Update()
// {
//     OLED_Update();
// }

// void Device::OLED_::UpdateArea(int16_t x, int16_t y, uint8_t width, uint8_t height)
// {
//     OLED_UpdateArea(x, y, width, height);
// }

// void Device::OLED_::Clear()
// {
//     OLED_Clear();
// }

// void Device::OLED_::ClearArea(int16_t x, int16_t y, uint8_t width, uint8_t height)
// {
//     OLED_ClearArea(x, y, width, height);
// }

// void Device::OLED_::Reverse()
// {
//     OLED_Reverse();
// }

// void Device::OLED_::ReverseArea(int16_t x, int16_t y, uint8_t width, uint8_t height)
// {
//     OLED_ReverseArea(x, y, width, height);
// }

// void Device::OLED_::ShowChar(int16_t x, int16_t y, char ch, uint8_t fontSize)
// {
//     OLED_ShowChar(x, y, ch, fontSize);
// }

// void Device::OLED_::ShowString(int16_t x, int16_t y, const char *str, uint8_t fontSize)
// {
//     OLED_ShowString(x, y, const_cast<char *>(str), fontSize);
// }

// void Device::OLED_::ShowNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize)
// {
//     OLED_ShowNum(x, y, number, length, fontSize);
// }

// void Device::OLED_::ShowSignedNum(int16_t x, int16_t y, int32_t number, uint8_t length, uint8_t fontSize)
// {
//     OLED_ShowSignedNum(x, y, number, length, fontSize);
// }

// void Device::OLED_::ShowHexNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize)
// {
//     OLED_ShowHexNum(x, y, number, length, fontSize);
// }

// void Device::OLED_::ShowBinNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize)
// {
//     OLED_ShowBinNum(x, y, number, length, fontSize);
// }

// void Device::OLED_::ShowFloatNum(int16_t x, int16_t y, double number, uint8_t intLength, uint8_t fraLength, uint8_t fontSize)
// {
//     OLED_ShowFloatNum(x, y, number, intLength, fraLength, fontSize);
// }

// void Device::OLED_::ShowImage(int16_t x, int16_t y, uint8_t width, uint8_t height, const uint8_t *image)
// {
//     OLED_ShowImage(x, y, width, height, image);
// }

// void Device::OLED_::Printf(int16_t x, int16_t y, uint8_t fontSize, const char *format, ...)
// {
//     va_list args;
//     va_start(args, format);
//     char buffer[256];
//     vsprintf(buffer, format, args);
//     OLED_ShowString(x, y, buffer, fontSize);
//     va_end(args);
// }

// void Device::OLED_::DrawPoint(int16_t x, int16_t y)
// {
//     OLED_DrawPoint(x, y);
// }

// bool Device::OLED_::GetPoint(int16_t x, int16_t y)
// {
//     return OLED_GetPoint(x, y) != 0;
// }

// void Device::OLED_::DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
// {
//     OLED_DrawLine(x0, y0, x1, y1);
// }

// void Device::OLED_::DrawRectangle(int16_t x, int16_t y, uint8_t width, uint8_t height, bool filled)
// {
//     OLED_DrawRectangle(x, y, width, height, filled ? FILLED : UNFILLED);
// }

// void Device::OLED_::DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, bool filled)
// {
//     OLED_DrawTriangle(x0, y0, x1, y1, x2, y2, filled ? FILLED : UNFILLED);
// }

// void Device::OLED_::DrawCircle(int16_t x, int16_t y, uint8_t radius, bool filled)
// {
//     OLED_DrawCircle(x, y, radius, filled ? FILLED : UNFILLED);
// }

// void Device::OLED_::DrawEllipse(int16_t x, int16_t y, uint8_t a, uint8_t b, bool filled)
// {
//     OLED_DrawEllipse(x, y, a, b, filled ? FILLED : UNFILLED);
// }

// void Device::OLED_::DrawArc(int16_t x, int16_t y, uint8_t radius, int16_t startAngle, int16_t endAngle, bool filled)
// {
//     OLED_DrawArc(x, y, radius, startAngle, endAngle, filled ? FILLED : UNFILLED);
// }

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
    uint16_t pulse = ((TIMx->ARR + 1) * _dutyRatio) / 100;

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

// uint32_t Device::PWM::Port_to_Rcc(GPIO_TypeDef *in)
// {
//     // 将GPIO端口转换为对应的RCC时钟使能位
//     if (in == GPIOA)
//         return RCC_APB2Periph_GPIOA;
//     if (in == GPIOB)
//         return RCC_APB2Periph_GPIOB;
//     if (in == GPIOC)
//         return RCC_APB2Periph_GPIOC;
//     if (in == GPIOD)
//         return RCC_APB2Periph_GPIOD;
//     if (in == GPIOE)
//         return RCC_APB2Periph_GPIOE;
//     if (in == GPIOF)
//         return RCC_APB2Periph_GPIOF;
//     if (in == GPIOG)
//         return RCC_APB2Periph_GPIOG;

//     return 0; // 默认返回0，表示无效
// }

Device::Timer::Channal::Channal(uint8_t _timer, uint8_t _index)
    : timer(_timer), index(_index) {}

uint32_t Device::Timer::Channal::portRcc()
{
    return 1 << ((reinterpret_cast<uint32_t>(this->getPort()) - APB2PERIPH_BASE) / 0x400);
}

Device::Timer::Channal &Device::Timer::Channal::operator=(Timer::Channal &&that)
{
    // TODO: 在此处插入 return 语句
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
