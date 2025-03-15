#include "RTE_Components.h"
#include CMSIS_device_header
#include "MyStm32.h"
// 在Arm_STD.cproject.yml中添加文件
void Delay(uint32_t count)
{
    while (count--)
    {
        __NOP(); // 空操作指令，防止被优化掉
    }
}

Device::LED led{Port::A, Pin::Pin0};
Device::Timer::Universal_timer timer1{Device::Timer::Universal_timer::TimerType::timer_4,1000_ms};
timer4_fun
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET) // 检查指定的TIM中断发生与否:TIM 中断源
    {
        // do something;
        led.turn();
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update); // 清除TIMx的中断待处理位:TIM 中断源
    }
}
int main(void)
{
    while (1)
    {
        uint16_t tp = 0;
        for (tp=0; tp<100; tp++) {
        
        }
        
    }  
}
