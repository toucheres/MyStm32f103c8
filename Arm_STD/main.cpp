#include "RTE_Components.h"
#include <string.h>
#include CMSIS_device_header
#include "MyStm32.h"

// 只保留必要的组件
Device::OLED oled{Port::B, Pin::Pin8, Port::B, Pin::Pin9};
// 添加蓝牙对象 - 使用USART1，波特率9600
Device::Bluetooth bluetooth{USART1, 9600};

// 添加到main.cpp开头，用于中断函数访问蓝牙对象
extern Device::Bluetooth bluetooth;  // 声明为外部变量

// 全局变量保存接收到的数据
char recv_buffer[16] = {0};
bool new_data_received = false;

// 修改USART1_IRQHandler中断函数，更新蓝牙对象的接收缓冲区
extern "C" void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        // 清除中断标志
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);

        // 接收数据
        uint8_t data = USART_ReceiveData(USART1);

        // 回显接收到的字符（便于调试）
        USART_SendData(USART1, data);

        // 处理接收到的数据
        static uint8_t pos = 0;

        if (data == '\r' || data == '\n')
        {
            // 只有缓冲区中有实际数据时才视为命令完成
            if (pos > 0)
            {
                recv_buffer[pos] = 0;
                pos = 0;
                new_data_received = true;
            }
            // 如果是空命令，直接忽略
        }
        else if (pos < 15)
        {
            recv_buffer[pos++] = data;
            recv_buffer[pos] = 0;
        }
    }
}

int main(void) {
    // 初始化系统
    SystemInit();

    // 创建并初始化OLED对象
    oled.Init();
    oled.Clear();
    oled.ShowString(0, 0, "Starting...", Device::OLED::OLED_8X16);
    oled.Update();
    
    // 使用简单循环延时替代System::delay
    for(volatile uint32_t i = 0; i < 1000000; i++);
    
    // 初始化蓝牙，去掉双重初始化
    oled.Clear();
    oled.ShowString(0, 0, "Init BT...", Device::OLED::OLED_8X16);
    oled.Update();
    
    bluetooth.init();
    oled.Clear();
    oled.ShowString(0, 0, "Init BT done!", Device::OLED::OLED_8X16);
    oled.Update();
    
    // 主循环
    uint32_t counter = 0;
    while(1) {
        counter++;
        
        // 每秒更新一次状态
        if(counter % 100000 == 0) {
            oled.Clear();
            oled.ShowString(0, 0, "Waiting...", Device::OLED::OLED_8X16);
            
            // 显示缓冲区内容（即使为空）
            char debug_str[32];
            sprintf(debug_str, "Buf[%d]:%s", strlen(recv_buffer), recv_buffer);
            oled.ShowString(0, 16, debug_str, Device::OLED::OLED_6X8);
            
            oled.Update();
        }
        
        // 显示接收到的数据
        if (new_data_received)
        {
            // 更新OLED显示
            oled.Clear();
            oled.ShowString(0, 0, "Received:", Device::OLED::OLED_6X8);
            oled.ShowString(0, 16, recv_buffer, Device::OLED::OLED_8X16);
            oled.Update();

            // 发送确认消息
            bluetooth.sendString("Received: ");
            bluetooth.sendString(recv_buffer);
            bluetooth.sendString("\r\n");

            // 处理接收到的命令（可以根据需要扩展）
            if (strcmp(recv_buffer, "LED ON") == 0)
            {
                bluetooth.sendString("Command: LED ON\r\n");
                // 这里可以添加LED开启代码
            }
            else if (strcmp(recv_buffer, "LED OFF") == 0)
            {
                bluetooth.sendString("Command: LED OFF\r\n");
                // 这里可以添加LED关闭代码
            }
            else if (strcmp(recv_buffer, "HELLO") == 0)
            {
                bluetooth.sendString("Hello from STM32!\r\n");
            }

            // 重置标志
            new_data_received = false;
        }

        // 添加短暂延时避免CPU占用过高
        // System::delay(10_ms);
    }
}