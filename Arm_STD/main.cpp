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

class MyDevice
{
    static Device::LED led;
    static Device::Timer::Universal_timer timer;

public:
    static void test() {
        MyDevice::led.turn();
    };
    MyDevice()
    {
        this->timer.setCallback(test);
    }
    void exec()
    {
        
        while (1)
        {
            /* code */
        }
        
    }
};
Device::LED MyDevice::led{Port::PortA, Pin::Pin0};
Device::Timer::Universal_timer MyDevice::timer{Device::Timer::TimerType::Universal::timer_2, 100};
int main(void)
{
    MyDevice self;
    self.exec();
}
