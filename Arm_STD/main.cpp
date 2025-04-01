// filepath: [main.cpp](http://_vscodecontentref_/1)
#include "RTE_Components.h"
#include <cstdio>
#include <cstdlib>
#include CMSIS_device_header
#include "Bluetooth.h"
#include "Interrupt.h"
#include "LED.h"
#include "MyStm32.h"
#include "OLED.h"
#include "System.h"
#include "WIFI.h"

Device::LED led{Port::A, Pin::Pin0};
Device::OLED oled{Port::B, Pin::Pin8, Port::B, Pin::Pin9};
Device::Bluetooth bluetooth{USART1, 9600};
Device::WIFI wifi{USART2, 115200}; // 使用USART2初始化WiFi模块

bool test = false;
uint8_t times = 0;
// WiFi回调函数
void wifi_callback(void* in)
{
    times++;

    // 转发WiFi模块收到的所有消息到蓝牙
    bluetooth.printf_late("WiFi[%d]: %s\n", times, wifi.rxBuffer);

    // 检查是否收到TCP数据
    if (strstr(wifi.rxBuffer, "+IPD") != NULL)
    {
        // 解析数据
        int conn_id = 0;
        int len = 0;
        char* data_start = NULL;

        // 尝试解析连接ID和数据长度 (+IPD,id,len:data)
        if (sscanf(wifi.rxBuffer, "+IPD,%d,%d:", &conn_id, &len) == 2)
        {
            // 找到数据起始位置
            data_start = strstr(wifi.rxBuffer, ":");
            if (data_start != NULL)
            {
                data_start++; // 跳过冒号

                // 显示收到的数据内容
                bluetooth.printf_late("Data[%d] Len=%d: ", conn_id, len);

                // 限制显示长度，避免溢出
                int show_len = (len > 32) ? 32 : len;
                char temp[33] = {0}; // 最多显示32个字符加结束符
                strncpy(temp, data_start, show_len);
                bluetooth.printf_late("%s\n", temp);

                // 如果数据是
                if (strncmp(data_start, "led change", 6) == 0)
                {
                    led.turn();
                    // 发送响应
                    wifi.printf_late("AT+CIPSEND=%d,7\r\n", conn_id);
                    System::delay(100_ms);
                    wifi.printf_late("LED ON\r\n");
                }
            }
        }
    }

    test = true;
}

// 处理蓝牙命令
void bt_fun(void* in)
{
    Device::Bluetooth* bt = static_cast<Device::Bluetooth*>(in);

    // 测试AT命令
    if (bt->equal_case("test"))
    {
        wifi.printf_late("AT\r\n");
    }
    // 清空WiFi缓冲区
    else if (bt->equal_case("clear"))
    {
        wifi.clear();
    }
    // 显示WiFi接收内容
    else if (bt->equal_case("show"))
    {
        bluetooth.printf_late("times:%d,show:%s\n", times, wifi.rxBuffer);
    }
    // 连接WiFi网络: connect,SSID,PASSWORD
    else if (bt->startsWith_case("connect"))
    {
        char ssid[32], password[32];
        if (bt->scanCommandArgs("connect", "%s %s", ssid, password) == 2)
        {
            bluetooth.printf_late("Connecting to %s...\n", ssid);
            wifi.printf_late("AT+CWMODE=1\r\n"); // 设置为station模式
            System::delay(500_ms);
            wifi.clear();

            // 发送连接命令
            wifi.printf_late("AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
        }
        else
        {
            bluetooth.printf_late("Usage: connect SSID PASSWORD\n");
        }
    }
    // 获取IP地址
    else if (bt->equal_case("getip"))
    {
        wifi.clear();
        wifi.printf_late("AT+CIFSR\r\n");
    }
    // 创建TCP服务器: server,PORT
    else if (bt->startsWith_case("server"))
    {
        int port;
        if (bt->scanCommandArgs("server", "%d", &port) == 1)
        {
            bluetooth.printf_late("Starting TCP server on port %d...\n", port);

            // 设置为多连接模式
            wifi.printf_late("AT+CIPMUX=1\r\n");
            System::delay(500_ms);
            wifi.clear();

            // 创建TCP服务器
            wifi.printf_late("AT+CIPSERVER=1,%d\r\n", port);
        }
        else
        {
            bluetooth.printf_late("Usage: server PORT\n");
        }
    }
    // 连接到TCP服务器: client,HOST,PORT
    else if (bt->startsWith_case("client"))
    {
        char host[64];
        int port;
        if (bt->scanCommandArgs("client", "%s %d", host, &port) == 2)
        {
            bluetooth.printf_late("Connecting to %s:%d...\n", host, port);

            // 设置为单连接模式
            wifi.printf_late("AT+CIPMUX=0\r\n");
            System::delay(500_ms);
            wifi.clear();

            // 连接到TCP服务器
            wifi.printf_late("AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", host, port);
        }
        else
        {
            bluetooth.printf_late("Usage: client HOST PORT\n");
        }
    }
    // 发送数据: send,DATA 或 send,ID,DATA (多连接模式)
    else if (bt->startsWith_case("send"))
    {
        char* args = bt->getArgs("send");
        if (args)
        {
            int id = -1;
            char data[256];

            // 检查是否指定了连接ID (多连接模式)
            if (sscanf(args, "%d,%s", &id, data) == 2)
            {
                int len = strlen(data);
                bluetooth.printf_late("Sending %d bytes to connection %d\n", len, id);
                wifi.printf_late("AT+CIPSEND=%d,%d\r\n", id, len);
                System::delay(100_ms);
                wifi.printf_late("%s", data);
            }
            else
            {
                // 单连接模式
                strcpy(data, args);
                int len = strlen(data);
                bluetooth.printf_late("Sending %d bytes\n", len);
                wifi.printf_late("AT+CIPSEND=%d\r\n", len);
                System::delay(100_ms);
                wifi.printf_late("%s", data);
            }
        }
        else
        {
            bluetooth.printf_late("Usage: send DATA or send ID,DATA\n");
        }
    }
    // 断开连接
    else if (bt->equal_case("disconnect"))
    {
        wifi.printf_late("AT+CIPCLOSE\r\n");
    }
    // 关闭服务器
    else if (bt->equal_case("closeserver"))
    {
        wifi.printf_late("AT+CIPSERVER=0\r\n");
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
    wifi.callback.fun = wifi_callback;
    wifi.callback.arg = &wifi;

    // 显示初始化信息
    oled.ShowString(0, 0, "WiFi Ready", 12);
    oled.ShowString(0, 16, "BT: 9600", 12);
    oled.ShowString(0, 32, "WiFi: 115200", 12);

    // 主循环
    uint32_t lastUpdateTime = 0;
    while (1)
    {
        // 检查并发送蓝牙待发送内容
        if (bluetooth.hasPending())
        {
            bluetooth.sendPending();
        }

        if (test)
        {
            bluetooth.printf("times:%d,while:%s\n", times, wifi.rxBuffer);
            test = false;

            // 更新OLED显示，每秒最多更新一次
            uint32_t currentTime = System::millisecond();
            if (currentTime - lastUpdateTime > 1000)
            {
                lastUpdateTime = currentTime;

                // 清除状态行
                oled.ShowString(0, 48, "                ", 12);

                // 显示当前状态
                if (wifi.status == Device::WIFI::Status::GOT_IP)
                {
                    char ipBuffer[16] = {0};
                    if (wifi.getIP(ipBuffer, sizeof(ipBuffer)))
                    {
                        oled.ShowString(0, 48, ipBuffer, 12);
                    }
                    else
                    {
                        oled.ShowString(0, 48, "Connected", 12);
                    }
                }
                else if (wifi.status == Device::WIFI::Status::CONNECTED)
                {
                    oled.ShowString(0, 48, "Connected", 12);
                }
                else if (wifi.status == Device::WIFI::Status::DISCONNECTED)
                {
                    oled.ShowString(0, 48, "Disconnected", 12);
                }
                else
                {
                    oled.ShowString(0, 48, "Error", 12);
                }
            }
        }

        // 检查并发送WiFi待发送内容
        if (wifi.hasPending())
        {
            wifi.sendPending();
        }
    }
}
// debug   27000
// release 19500
// size    15000