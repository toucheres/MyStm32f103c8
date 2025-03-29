#include "stm32f10x.h"
#include <cstdint>
#include "Interrupt.h"

// 创建一个全局标志位，用于在主循环中监测中断是否发生
volatile bool usart2_interrupt_occurred = false;

// 这个函数会被 USART2_IRQHandler 调用
extern "C" void USART2_Debug_Handler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        // 清除中断标志
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        
        // 读取数据（防止连续中断）
        uint8_t data = USART_ReceiveData(USART2);
        
        // 设置标志位
        usart2_interrupt_occurred = true;
        
        // 可选：回环发送数据作为测试
        USART_SendData(USART2, data);
    }
}

// 在主程序中调用此函数来检查中断状态
bool check_usart2_interrupt_status(void)
{
    bool status = usart2_interrupt_occurred;
    usart2_interrupt_occurred = false; // 重置标志位
    return status;
}
