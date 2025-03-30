// filepath: [main.cpp](http://_vscodecontentref_/1)
#include "RTE_Components.h"
#include <cstdio>
#include <cstdlib>
#include CMSIS_device_header
#include "MyStm32.h"
#include "Bluetooth.h"
#include "LED.h"
#include "OLED.h"
#include "ADC.h"
#include "Timer.h"
#include "PWM.h"
#include "System.h"
#include <string.h>
#include "Interrupt.h"
#include "RTC.h"
#include "WIFI.h"

Device::LED led{Port::A, Pin::Pin0};
Device::OLED oled{Port::B, Pin::Pin8, Port::B, Pin::Pin9};
Device::Bluetooth bluetooth{USART1, 9600};
Device::WIFI wifi{USART2, 115200}; // 使用USART2初始化WiFi模块

bool wifiConnected = false; // WiFi连接状态

// WiFi回调函数
void wifi_callback(void *in)
{
    // Device::WIFI *wf = (Device::WIFI *)(in);
    // bluetooth.printf("%s", wf->getBuffer());
    // wifi.clear();
}



// 处理蓝牙命令
void bt_fun(void *in)
{
    Device::Bluetooth*bt = static_cast<Device::Bluetooth*>(in);
    if (bt->equal_case("test"))
    {
        wifi.sendString("AT\r\n");
    }
    if (bt->equal_case("clear"))
    {
        wifi.clear();
    }
    if (bt->equal_case("show"))
    {
        bluetooth.sendString(wifi.rxBuffer);
    }   
    // 清空接收缓冲区
    bt->clear();
    bt->hasNewData = false;
}

int main(void)
{
    // 初始化外设
    oled.Init();
    bluetooth.init();
    bluetooth.callback.fun = bt_fun;
    bluetooth.callback.arg = &bluetooth;
    wifi.init();
    // 主循环
    while (1)
    {
        // 处理蓝牙接收
        if (bluetooth.hasNewData)
        {
            bluetooth.callback();
        }

        // 处理WiFi接收
        // if (wifi.hasNewData)
        // {
        //     bluetooth.printf("%s", wifi.getBuffer());
        //     wifi.clear();
        // }
    }
}
// debug   27000
// release 19500
// size    15000