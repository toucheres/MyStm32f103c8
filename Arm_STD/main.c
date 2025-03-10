#include "RTE_Components.h"
#include CMSIS_device_header

void Delay(uint32_t count)
{
    while (count--)
    {
        __NOP(); // 空操作指令，防止被优化掉
    }
}

int main(void)
{
    // 初始化时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 初始化GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 初始状态设置为高电平，点亮LED
    GPIO_SetBits(GPIOA, GPIO_Pin_0);

    while (1)
    {
        // LED闪烁代码，如果只需常亮可删除这部分
        GPIO_SetBits(GPIOA, GPIO_Pin_0);   // LED亮
        Delay(500000);                     // 延时
        GPIO_ResetBits(GPIOA, GPIO_Pin_0); // LED灭
        Delay(500000);                     // 延时
    }
}
