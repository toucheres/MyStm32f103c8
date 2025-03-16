#include "RTE_Components.h"
#include CMSIS_device_header
#include "MyStm32.h"
Device::Timer::Universal_timer timer{Device::Timer::Universal_timer::TimerType::timer_2,1000_ms};
Device::LED led{Port::A, Pin::Pin0};
Device::OLED oled;
timer2_fun {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) // 检查指定的TIM中断发生与否:TIM 中断源
    {
        // do something;
        led.turn();
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除TIMx的中断待处理位:TIM 中断源
    }
}
int main(void)
{
    // 初始化系统
    SystemInit();

    // 创建并初始化OLED对象

    oled.Clear();

    // 显示文本
    oled.ShowChar(0, 0, 'A', Device::OLED::FONT_SIZE_8X16);
    oled.ShowString(16, 0, "你好!", Device::OLED::FONT_SIZE_8X16);

    // 显示数字
    oled.ShowNum(0, 28, 12345, 5, Device::OLED::FONT_SIZE_6X8);

    // 绘制图形
    oled.DrawRectangle(70, 40, 30, 15, true); // 填充矩形
    oled.DrawCircle(40, 40, 10);              // 空心圆    // 更新显示
    oled.Update();

    while (1)
    {
        // 主循环
    }
}