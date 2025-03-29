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
System::rtc_clock rtc; // 创建RTC实例

char timeStr[20];           // 用于格式化时间字符串
bool updateDisplay = false; // 时间更新标志
bool wifiConnected = false; // WiFi连接状态

// WiFi回调函数
void wifi_callback(void *in)
{
    Device::WIFI *wf = (Device::WIFI *)(in);
    
    // 在此处理WiFi接收到的数据
    // 示例：检测到特定数据时更新显示
    if (strstr(wf->getBuffer(), "+IPD") != NULL)
    {
        // 收到网络数据
        oled.ShowString(0, 48, "Data received!", Device::OLED::OLED_6X8);
        oled.Update();
        
        // 转发到蓝牙
        bluetooth.sendString("WiFi data: ");
        bluetooth.sendString(wf->getBuffer());
        bluetooth.sendString("\r\n");
    }
    
    // 清空接收缓冲区
    wf->clear();
    wf->hasNewData = false;
}

// 秒中断回调 - 每秒执行一次
void onSecondTick(void *)
{
    // 获取当前时间
    uint8_t hours, minutes, seconds;
    rtc.getTime(hours, minutes, seconds);

    // 格式化时间字符串
    sprintf(timeStr, "%02d:%02d:%02d", hours, minutes, seconds);

    // 翻转LED状态，实现1Hz闪烁
    led.turn();

    // 设置显示更新标志
    updateDisplay = true;
}

// 闹钟中断回调
void onAlarm(void *)
{
    // 显示闹钟触发消息
    oled.Clear();
    oled.ShowString(0, 0, "ALARM!", Device::OLED::OLED_8X16);
    oled.ShowString(0, 16, "Wake up time!", Device::OLED::OLED_8X16);
    oled.Update();

    // 通过蓝牙发送闹钟消息
    bluetooth.sendString("ALARM TRIGGERED!\r\n");

    // 清除闹钟标志
    rtc.clearAlarmFlag();
}

// 处理蓝牙命令
void bt_fun(void *in)
{
    Device::Bluetooth *bt = (Device::Bluetooth *)(in);

    // 处理RTC相关命令
    if (bt->equal_case("time"))
    {
        // 获取当前时间x
        uint8_t hours, minutes, seconds;
        rtc.getTime(hours, minutes, seconds);

        // 获取当前日期
        uint8_t day, month, weekday;
        uint16_t year;
        rtc.getDate(day, month, year, weekday);

        // 发送时间日期信息
        bt->printf("Current Time: %02d:%02d:%02d\r\n", hours, minutes, seconds);
        bt->printf("Current Date: %02d/%02d/%04d (Day %d)\r\n", day, month, year, weekday);
    }
    else if (bt->equal_case("settime"))
    {
        // 期望格式: settime 12:34:56
        if (strlen(bt->getBuffer()) > 8)
        {
            uint8_t h, m, s;
            if (sscanf(bt->getBuffer() + 8, "%hhu:%hhu:%hhu", &h, &m, &s) == 3)
            {
                rtc.setTime(h, m, s);
                bt->printf("Time set to %02d:%02d:%02d\r\n", h, m, s);
            }
            else
            {
                bt->sendString("Invalid time format! Use: settime HH:MM:SS\r\n");
            }
        }
    }
    else if (bt->equal_case("setalarm"))
    {
        // 期望格式: setalarm 12:34:56
        if (strlen(bt->getBuffer()) > 9)
        {
            uint8_t h, m, s;
            if (sscanf(bt->getBuffer() + 9, "%hhu:%hhu:%hhu", &h, &m, &s) == 3)
            {
                rtc.setAlarm(h, m, s);
                rtc.enableAlarm(true);
                bt->printf("Alarm set to %02d:%02d:%02d\r\n", h, m, s);
            }
            else
            {
                bt->sendString("Invalid alarm format! Use: setalarm HH:MM:SS\r\n");
            }
        }
    }
    else if (bt->equal_case("alarmon"))
    {
        rtc.enableAlarm(true);
        bt->sendString("Alarm enabled\r\n");
    }
    else if (bt->equal_case("alarmoff"))
    {
        rtc.enableAlarm(false);
        bt->sendString("Alarm disabled\r\n");
    }
    // 添加WiFi相关命令
    else if (bt->equal_case("wificonnect"))
    {
        // 期望格式：wificonnect SSID PASSWORD
        char ssid[32] = {0};
        char password[32] = {0};
        
        if (sscanf(bt->getBuffer() + 12, "%s %s", ssid, password) == 2)
        {
            bt->printf("Connecting to %s...\r\n", ssid);
            oled.ShowString(0, 48, "Connecting WiFi...", Device::OLED::OLED_6X8);
            oled.Update();
            
            if (wifi.connect(ssid, password, 20000)) // 20秒超时
            {
                bt->printf("Connected to WiFi! SSID: %s\r\n", ssid);
                oled.ShowString(0, 48, "WiFi Connected!", Device::OLED::OLED_6X8);
                oled.Update();
                wifiConnected = true;
            }
            else
            {
                bt->sendString("Failed to connect to WiFi!\r\n");
                oled.ShowString(0, 48, "WiFi Failed!", Device::OLED::OLED_6X8);
                oled.Update();
            }
        }
        else
        {
            bt->sendString("Invalid format! Use: wificonnect SSID PASSWORD\r\n");
        }
    }
    else if (bt->equal_case("wifistatus"))
    {
        Device::WIFI::Status status = wifi.getStatus();
        switch (status)
        {
            case Device::WIFI::Status::DISCONNECTED:
                bt->sendString("WiFi Status: DISCONNECTED\r\n");
                break;
            case Device::WIFI::Status::CONNECTED:
                bt->sendString("WiFi Status: CONNECTED\r\n");
                break;
            case Device::WIFI::Status::GOT_IP:
                bt->sendString("WiFi Status: CONNECTED (IP obtained)\r\n");
                break;
            case Device::WIFI::Status::ERROR:
                bt->sendString("WiFi Status: ERROR\r\n");
                break;
        }
    }
    else if (bt->equal_case("wifiip"))
    {
        char ipAddress[16] = {0};
        if (wifi.getIP(ipAddress, sizeof(ipAddress)))
        {
            bt->printf("IP Address: %s\r\n", ipAddress);
        }
        else
        {
            bt->sendString("Failed to get IP address\r\n");
        }
    }
    else if (bt->equal_case("wifidisconnect"))
    {
        if (wifi.disconnect())
        {
            bt->sendString("WiFi disconnected\r\n");
            wifiConnected = false;
            oled.ShowString(0, 48, "WiFi Disconnected", Device::OLED::OLED_6X8);
            oled.Update();
        }
        else
        {
            bt->sendString("Failed to disconnect WiFi\r\n");
        }
    }
    else if (bt->equal_case("wifitest"))
    {
        // 尝试连接TCP服务器进行测试
        bt->sendString("Testing TCP connection...\r\n");
        if (wifi.connectTCP("example.com", 80))
        {
            bt->sendString("TCP connected! Sending test request...\r\n");
            
            // 发送简单的HTTP GET请求
            wifi.sendString("GET / HTTP/1.1\r\nHost: example.com\r\n\r\n");
            
            // 等待响应（实际应用中应使用回调方式）
            System::delay(2000_ms);
            
            // 显示接收到的数据头部
            bt->sendString("Response received:\r\n");
            bt->sendString(wifi.getBuffer());
            
            // 关闭连接
            wifi.closeTCP();
        }
        else
        {
            bt->sendString("Failed to connect TCP server\r\n");
        }
    }
    else
    {
        bt->sendString("Unknown command\r\n");
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
    
    // 初始化WiFi模块
    if (wifi.init())
    {
        oled.ShowString(0, 48, "WiFi Ready", Device::OLED::OLED_6X8);
        wifi.setCallback(wifi_callback, &wifi);
    }
    else
    {
        oled.ShowString(0, 48, "WiFi Init Failed", Device::OLED::OLED_6X8);
    }
    
    // 初始化RTC
    bool isFirstConfig = rtc.init(System::rtc_clock::LSE);
    if (isFirstConfig)
    {
        // 设置当前时间 (12:00:00)
        rtc.setTime(12, 0, 0);
        // 设置当前日期 (2025年3月27日, 星期四)
        rtc.setDate(27, 3, 2025, 4);
        // 设置一个闹钟示例
        rtc.setAlarm(12, 1, 0); // 设置为1分钟后
    }
    // 注册秒中断回调
    rtc.setSecondCallback(onSecondTick, nullptr);
    rtc.enableSecondInterrupt(true);
    // 注册闹钟中断回调
    rtc.setAlarmCallback(onAlarm, nullptr);
    rtc.enableAlarm(true);
    // 显示初始时间
    System::rtc_clock::DateTime now = rtc.getDateTime();
    sprintf(timeStr, "%02d:%02d:%02d", now.hours, now.minutes, now.seconds);

    oled.Clear();
    oled.ShowString(0, 0, "RTC & WiFi Demo", Device::OLED::OLED_8X16);
    oled.ShowString(0, 16, timeStr, Device::OLED::OLED_8X16);

    char dateStr[20];
    sprintf(dateStr, "%02d/%02d/%04d", now.day, now.month, now.year);
    oled.ShowString(0, 32, dateStr, Device::OLED::OLED_8X16);
    oled.Update();

    // 通过蓝牙发送初始化信息
    bluetooth.printf("RTC & WiFi Demo. Current time: %02d:%02d:%02d\r\n",
                     now.hours, now.minutes, now.seconds);
    bluetooth.printf("Date: %02d/%02d/%04d\r\n", now.day, now.month, now.year);
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

    // 主循环
    while (1)
    {
        // 更新RTC显示
        if (updateDisplay)
        {
            oled.Clear();
            oled.ShowString(0, 0, "RTC & WiFi Demo", Device::OLED::OLED_8X16);
            oled.ShowString(0, 16, timeStr, Device::OLED::OLED_8X16);

            // 获取当前日期
            System::rtc_clock::DateTime dt = rtc.getDateTime();
            sprintf(dateStr, "%02d/%02d/%04d", dt.day, dt.month, dt.year);
            oled.ShowString(0, 32, dateStr, Device::OLED::OLED_8X16);

            // 显示WiFi状态
            if (wifiConnected)
            {
                char ipAddress[16] = {0};
                if (wifi.getIP(ipAddress, sizeof(ipAddress)))
                {
                    char ipStr[30];
                    sprintf(ipStr, "IP: %s", ipAddress);
                    oled.ShowString(0, 48, ipStr, Device::OLED::OLED_6X8);
                }
                else
                {
                    oled.ShowString(0, 48, "WiFi Connected", Device::OLED::OLED_6X8);
                }
            }

            oled.Update();
            updateDisplay = false;
        }

        // 处理蓝牙接收
        if (bluetooth.hasNewData)
        {
            bluetooth.callback();
        }

        // 处理WiFi接收
        if (wifi.hasNewData)
        {
            wifi.callback();
        }

        // 低功耗操作
        if (!updateDisplay && !bluetooth.hasNewData && !wifi.hasNewData)
        {
            System::power::sleep_for_interrupt();
        }
    }
}
//debug   27000
//release 19500
//size    15000