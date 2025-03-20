#include "RTE_Components.h"
#include CMSIS_device_header
#include "MyStm32.h"

Device::Timer::Universal_timer timer{Device::Timer::Universal_timer::TimerType::timer_3, 1000_ms};
// Device::LED led{Port::A, Pin::Pin0};
Device::OLED oled{Port::B, Pin::Pin8, Port::B, Pin::Pin9};
Device::PWM pwm{Device::Timer::Universal_timer::TimerType::timer_2, Device::Timer::Channal::ChannalType::channal_1};
uint16_t nums = 0;
Device::ADC adc{
    Device::ADC::Mode::continuous, 1, Device::ADC::Mode::None, Device::ADC::ADCType::adc1};
timer3_fun
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) ==
        SET) // 检查指定的TIM中断发生与否:TIM 中断源
    {
        nums = adc.getChannal(Device::ADC::Channel16);
        oled.Clear();
        oled.ShowNum(0, 0, nums, 5, Device::OLED::OLED_6X8);
        oled.Update();
        TIM_ClearITPendingBit(TIM3,
                              TIM_IT_Update); // 清除TIMx的中断待处理位:TIM 中断源
    }
}
int main(void)
{
    // 初始化系统
    SystemInit();
    pwm.change(1, 1000, 10);
    pwm.start();
    // // 创建并初始化OLED对象
    oled.Init();
    oled.Clear();
    adc.addChannal(Device::ADC::Channel16);
    // // 显示文本
    // oled.ShowChar(0, 0, 'A', Device::OLED::OLED_6X8);
    // oled.ShowString(16, 0, "new life", Device::OLED::OLED_8X16);

    // // 显示数字
    // oled.ShowNum(0, 28, 12345, 5, Device::OLED::OLED_6X8);

    // // 绘制图形
    // oled.DrawRectangle(70, 40, 30, 15, true); // 填充矩形
    // oled.DrawCircle(40, 40, 10, 0);              // 空心圆    // 更新显示
    // oled.Update();
    while (1)
    {
        // for (size_t i = 0; i < 100; i++)
        // {
        //     pwm.change(1, 1000, i);
        //     System::delay(10_ms);
        // }
        // for (size_t i = 100; i > 0; i--)
        // {
        //     pwm.change(1, 1000, i);
        //     System::delay(10_ms);
        // }
        int i = 0;
        i++;
    }
}
// Program Size: Code=4176 RO-data=256 RW-data=0 ZI-data=5136
// Program Size: Code=2000 RO-data=256 RW-data=0 ZI-data=5136
// Program Size: Code=2888 RO-data=296 RW-data=0 ZI-data=5136