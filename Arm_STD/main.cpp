#include "RTE_Components.h"
#include <string.h>
#include CMSIS_device_header
#include "MyStm32.h"

Device::LED led{Port::A, Pin::Pin0};
Device::OLED oled{Port::B, Pin::Pin8, Port::B, Pin::Pin9};
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
            oled.ShowString(0, 16, bluetooth.getBuffer(), Device::OLED::OLED_8X16);
            
            // 添加调试信息，显示命令的十六进制值
            char debug_str[64];
            sprintf(debug_str, "Len:%d", strlen(bluetooth.getBuffer()));
            oled.ShowString(0, 32, debug_str, Device::OLED::OLED_6X8);
            
            oled.Update();

            // 使用format方法发送确认消息
            bluetooth.printf("Received: \"%s\" (length: %d)\r\n", 
                            bluetooth.getBuffer(), 
                            strlen(bluetooth.getBuffer()));

            // 使用更灵活的命令比较方式
            if (strcmp(bluetooth.getBuffer(), "Clear") == 0)
            {
                bluetooth.printf("Command: Clear executed at count %lu\r\n", counter);
                bluetooth.clear();
                
                // 确认命令执行的视觉反馈
                oled.Clear();
                oled.ShowString(0, 0, "Clear command", Device::OLED::OLED_8X16);
                oled.ShowString(0, 16, "executed!", Device::OLED::OLED_8X16);
                oled.Update();
            }
            else if (strcasecmp(bluetooth.getBuffer(), "LED OFF") == 0)
            {
                bluetooth.sendString("Command: LED OFF\r\n");
                // LED处理代码
            }
            else
            {
                // 未知命令处理
                bluetooth.sendString("Unknown command\r\n");
            }

            // 重置标志并清空缓冲区，准备接收下一条命令
            bluetooth.clear();
        }
    }
}