#include "RTE_Components.h"
#include <string.h>
#include CMSIS_device_header
#include "MyStm32.h"

// 只保留必要的组件
Device::LED led{Port::A,Pin::Pin0};
Device::OLED oled{Port::B, Pin::Pin8, Port::B, Pin::Pin9};
// 添加蓝牙对象 - 使用USART1，波特率9600
Device::Bluetooth bluetooth{USART1, 9600};

// 在main.cpp中修改中断处理函数
USART1_fun
{
    bluetooth.handleInterrupt();
}
// 修改main循环，使用蓝牙类的缓冲区
int main(void)
{
    // 初始化系统
    SystemInit();

    // 创建并初始化OLED对象
    oled.Init();
    oled.Clear();
    oled.ShowString(0, 0, "Starting...", Device::OLED::OLED_8X16);
    oled.Update();

    // 初始化蓝牙
    bluetooth.init();
    oled.Clear();
    oled.ShowString(0, 0, "Init BT done!", Device::OLED::OLED_8X16);
    oled.Update();

    // 主循环
    uint32_t counter = 0;
    while (1)
    {
        counter++;

        // 每秒更新一次状态
        if (counter % 100000 == 0)
        {
            oled.Clear();
            oled.ShowString(0, 0, "Waiting...", Device::OLED::OLED_8X16);

            // 显示缓冲区内容
            char debug_str[32];
            sprintf(debug_str, "Buf[%d]:%s", strlen(bluetooth.rxBuffer), bluetooth.rxBuffer);
            oled.ShowString(0, 16, debug_str, Device::OLED::OLED_6X8);

            oled.Update();
        }

        // 显示接收到的数据
        if (bluetooth.hasNewData)
        {
            oled.Clear();
            oled.ShowString(0, 0, "Received:", Device::OLED::OLED_6X8);
            oled.ShowString(0, 16, bluetooth.rxBuffer, Device::OLED::OLED_8X16);
            oled.Update();

            // 发送确认消息
            bluetooth.sendString("Received: ");
            bluetooth.sendString(bluetooth.rxBuffer);
            bluetooth.sendString("\r\n");

            // 处理命令
            if (strcmp(bluetooth.rxBuffer, "LED ON") == 0)
            {
                bluetooth.sendString("Command: LED ON\r\n");
                // LED处理代码
            }
            else if (strcmp(bluetooth.rxBuffer, "LED OFF") == 0)
            {
                bluetooth.sendString("Command: LED OFF\r\n");
                // LED处理代码
            }

            // 重置标志
            bluetooth.hasNewData = false;
        }
    }
}