#include "RTE_Components.h"
#include CMSIS_device_header
#include "MyStm32.h"
#include <string.h>

Device::LED led{Port::A, Pin::Pin0};
Device::OLED oled{Port::B, Pin::Pin8, Port::B, Pin::Pin9};
Device::Bluetooth bluetooth{USART1, 9600};
USART1_fun { bluetooth.handleInterrupt(); }
void bt_fun(Device::Bluetooth *bt)
{
    oled.Clear();
    oled.ShowString(0, 0, "Received:", Device::OLED::OLED_6X8);
    oled.ShowString(0, 16, bt->getBuffer(), Device::OLED::OLED_8X16);

    // 添加调试信息，显示命令的十六进制值
    char debug_str[64];
    sprintf(debug_str, "Len:%d", strlen(bt->getBuffer()));
    oled.ShowString(0, 32, debug_str, Device::OLED::OLED_6X8);

    oled.Update();

    // 使用format方法发送确认消息
    bt->printf("Received: \"%s\" (length: %d)\r\n",
               bt->getBuffer(),
               strlen(bt->getBuffer()));

    // 使用更灵活的命令比较方式
    if (bt->equal("Clear"))
    {
        bt->printf("Command: Clear executed at count %lu\r\n", 1);
        bt->clear();

        // 确认命令执行的视觉反馈
        oled.Clear();
        oled.ShowString(0, 0, "Clear command", Device::OLED::OLED_8X16);
        oled.ShowString(0, 16, "executed!", Device::OLED::OLED_8X16);
        oled.Update();
    }
    else if (bt->equal_case("led change"))
    {
        led.turn();
        bt->sendString("Command: LED changed\r\n");

        // LED处理代码
    }
    else if (bt->equal_case("show"))
    {
        bt->sendString("Command: show\r\n");
        oled.Clear();
        oled.ShowString(0, 0, "Waiting...", Device::OLED::OLED_8X16);

        // 显示缓冲区内容
        char debug_str[32];
        sprintf(debug_str, "Buf[%d]:%s", strlen(bluetooth.rxBuffer), bluetooth.rxBuffer);
        oled.ShowString(0, 16, debug_str, Device::OLED::OLED_6X8);

        oled.Update();

        // LED处理代码
    }
    else
    {
        // 未知命令处理
        bt->sendString("Unknown command\r\n");
    }

    // 重置标志并清空缓冲区，准备接收下一条命令
    bt->clear();
    bt->hasNewData = false;
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
    bluetooth.callback = bt_fun;
    // 主循环
    uint32_t counter = 0;
    while (1)
    {
        System::power::sleep_for_interrupt();
    }
}
