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
    Device::WIFI *wf = (Device::WIFI *)(in);

    // 1. 打印接收到的数据
    bluetooth.printf("wifiget:%s\n", wf->getBuffer());

    // 2. 只在收到完整响应时清空缓冲区
    if (strstr(wf->getBuffer(), "\r\nOK\r\n") ||
        strstr(wf->getBuffer(), "\r\nERROR\r\n") ||
        strstr(wf->getBuffer(), "SEND OK\r\n"))
    {
        // 处理完整响应后才清空
        // wf->clear();  // 注意：在主循环中清空可能更合适
    }
}



// 处理蓝牙命令
void bt_fun(void *in)
{
    Device::Bluetooth*bt = static_cast<Device::Bluetooth*>(in);
    if (bt->equal_case("wifitest"))
    {
        bt->sendString("Testing WiFi hardware connection...\r\n");

        // 1. 清空WiFi接收缓冲区
        wifi.clear();

        // 2. 发送AT测试命令
        wifi.sendString("AT\r\n");

        // 3. 等待响应（设置合理的超时时间）
        uint32_t startTime = System::millisecond();
        bool responseReceived = false;
        bool okFound = false;
        System::delay(2_s);
        // 检查是否收到OK响应
        if (strstr(wifi.getBuffer(), "\r\nOK\r\n"))
        {
            bt->sendString("WiFi module responded with OK! Hardware connection successful.\r\n");
            okFound = true;
            responseReceived = true;
        }
        // 检查是否收到ERROR响应
        else if (strstr(wifi.getBuffer(), "\r\nERROR\r\n"))
        {
            bt->sendString("WiFi module responded with ERROR!\r\n");
            responseReceived = true;
        }

        // 4. 超时和结果报告
        if (!responseReceived)
        {
            bt->printf("No proper response within timeout.\r\n");
            bt->printf("Received buffer: %s\r\n", wifi.getBuffer());
        }

        // 5. 更新OLED显示
        oled.ShowString(0, 48, okFound ? "WiFi OK" : "WiFi Failed", Device::OLED::OLED_6X8);
        oled.Update();

        // 6. 清空缓冲区为下次命令做准备
        wifi.clear();
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

    // 初始化WiFi模块并检查是否成功
    if (wifi.init())
    {
        oled.ShowString(0, 48, "WiFi Ready", Device::OLED::OLED_6X8);
        bluetooth.printf("WiFi Ready\n");
        wifi.callback.fun = wifi_callback;
        wifi.callback.arg = &wifi;
    }
    else
    {
        oled.ShowString(0, 48, "WiFi Init Failed", Device::OLED::OLED_6X8);
        bluetooth.printf("WiFi Init Failed\n");

        bluetooth.sendString("WIFI init failed!\r\n");
    }
    bluetooth.sendString("Available commands:\r\n");
    bluetooth.sendString("  RTC Commands:\r\n");
    bluetooth.sendString("    time - show current time\r\n");
    bluetooth.sendString("    settime HH:MM:SS - set current time\r\n");
    bluetooth.sendString("    setalarm HH:MM:SS - set alarm time\r\n");
    bluetooth.sendString("    alarmon - enable alarm\r\n");
    bluetooth.sendString("    alarmoff - disable alarm\r\n");
    bluetooth.sendString("  WiFi Commands:\r\n");
    bluetooth.sendString("    wificonnect SSID PASSWORD - connect to WiFi\r\n");
    bluetooth.sendString("    wifistatus - show WiFi status\r\n");
    bluetooth.sendString("    wifiip - show IP address\r\n");
    bluetooth.sendString("    wifidisconnect - disconnect from WiFi\r\n");
    bluetooth.sendString("    wifitest - run connection test\r\n");
    bluetooth.sendString("    wifiat [command] - send AT command to WiFi module\r\n");
    bluetooth.sendString("    wifitest - run hardware connection test\r\n");

    // 主循环
    while (1)
    {
        // 处理蓝牙接收
        if (bluetooth.hasNewData)
        {
            bluetooth.callback();
        }

        // 处理WiFi接收
        if (wifi.hasNewData)
        {
            wifi.callback();
            wifi.hasNewData = false; // 确保数据被处理后重置标志
        }
    }
}
// debug   27000
// release 19500
// size    15000