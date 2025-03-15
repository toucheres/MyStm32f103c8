#include "RTE_Components.h"
#include CMSIS_device_header
#include "MyStm32.h"
int main(void)
{
    // 初始化系统
    SystemInit();

    // 创建并初始化OLED对象
    Device::OLED oled;
    oled.Clear();

    // 显示文本
    oled.ShowChar(0, 0, 'A', Device::OLED::FONT_SIZE_8X16);
    oled.ShowString(16, 0, "Hello World!", Device::OLED::FONT_SIZE_8X16);

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