#include "RTE_Components.h"
#include "stm32f10x_exti.h"
#include <cstdio>
#include CMSIS_device_header
#include "MyStm32.h"
#include "Bluetooth.h"
#include "LED.h"
#include "OLED.h"
#include "ADC.h"
#include "Timer.h"
#include "PWM.h"
#include "System.h" // 添加System头文件
#include <string.h>
#include "Interrupt.h"

Device::LED led{Port::A, Pin::Pin0};
// Device::OLED oled{Port::B, Pin::Pin8, Port::B, Pin::Pin9};
Device::Bluetooth bluetooth{USART1, 9600};
USART1_fun { bluetooth.handleInterrupt(); }
// EXTI1_fun
// {
//     if (EXTI_GetITStatus(EXTI_Line1) != RESET)
//     {
//         EXTI_ClearITPendingBit(EXTI_Line1);
//     }
// }
// void bt_fun(Device::Bluetooth *bt)
// {
//     oled.Clear();
//     oled.ShowString(0, 0, "Received:", Device::OLED::OLED_6X8);
//     oled.ShowString(0, 16, bt->getBuffer(), Device::OLED::OLED_8X16);

//     // 添加调试信息，显示命令的十六进制值
//     char debug_str[64];
//     sprintf(debug_str, "Len:%d", strlen(bt->getBuffer()));
//     oled.ShowString(0, 32, debug_str, Device::OLED::OLED_6X8);

//     oled.Update();

//     // 使用format方法发送确认消息
//     bt->printf("Received: \"%s\" (length: %d)\r\n",
//                bt->getBuffer(),
//                strlen(bt->getBuffer()));

//     // 使用更灵活的命令比较方式
//     if (bt->equal("Clear"))
//     {
//         bt->printf("Command: Clear executed at count %lu\r\n", 1);
//         bt->clear();

//         // 确认命令执行的视觉反馈
//         oled.Clear();
//         oled.ShowString(0, 0, "Clear command", Device::OLED::OLED_8X16);
//         oled.ShowString(0, 16, "executed!", Device::OLED::OLED_8X16);
//         oled.Update();
//     }
//     else if (bt->equal_case("led change"))
//     {
//         led.turn();
//         bt->sendString("Command: LED changed\r\n");

//         // LED处理代码
//     }
//     else if (bt->equal_case("show"))
//     {
//         bt->sendString("Command: show\r\n");
//         oled.Clear();
//         oled.ShowString(0, 0, "Waiting...", Device::OLED::OLED_8X16);

//         // 显示缓冲区内容
//         char debug_str[32];
//         sprintf(debug_str, "Buf[%d]:%s", strlen(bluetooth.rxBuffer), bluetooth.rxBuffer);
//         oled.ShowString(0, 16, debug_str, Device::OLED::OLED_6X8);

//         oled.Update();

//         // LED处理代码
//     }
//     else
//     {
//         // 未知命令处理
//         bt->sendString("Unknown command\r\n");
//     }

//     // 重置标志并清空缓冲区，准备接 收下一条命令
//     bt->clear();
//     bt->hasNewData = false;
// }
// 修改main循环，使用蓝牙类的缓冲区
int main(void)
{
    // // 系统初始化
    // SystemInit();

    // // 外设初始化
    // oled.Init();
    bluetooth.init();

    // size_t i = 0;
    // bool testMode = false; // 设置为true启用PA1测试模式

    // 主循环 - 正式代码
    while (1)
    {
        System::delay(1_s);
        led.turn();
        bluetooth.sendString("test");
        // // 显示即将进入STOP模式
        // oled.Clear();
        // oled.ShowString(0, 0, "Entering STOP", Device::OLED::OLED_8X16);
        // oled.ShowString(0, 16, "Press PA1->Wake", Device::OLED::OLED_6X8);
        // oled.Update();
        // bluetooth.printf("Entering STOP mode, loop:%d\r\n", i);

        // // 延时确保消息发送完成
        // System::delay(500_ms);

        // // 进入STOP模式，明确指定下降沿触发
        // System::power::stopWithEXTIWakeup(GPIOA, GPIO_Pin_1, EXTI_Trigger_Falling);

        // // 下面的代码只有在唤醒后才会执行
        // i++; // 增加计数

        // // 唤醒后重新初始化系统
        // SystemInit();         // 重新配置系统时钟
        // System::delay(10_ms); // 给系统时钟一些稳定时间

        // // 重新初始化外设
        // oled.Init();
        // bluetooth.init();

        // // 显示唤醒成功信息
        // oled.Clear();
        // oled.ShowString(0, 0, "Wakeup Success!", Device::OLED::OLED_8X16);

        // char loopStr[32];
        // sprintf(loopStr, "Loop: %u", i);
        // oled.ShowString(0, 16, loopStr, Device::OLED::OLED_6X8);
        // oled.Update();

        // bluetooth.printf("Wakeup Success! loop:%d\r\n", i);

        // // 显示一段时间后再次进入循环
        // System::delay(200_ms);
    }
}