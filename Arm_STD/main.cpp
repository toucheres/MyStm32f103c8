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
    Device::LED led{Port::PortA, Pin::Pin0};
public:
    void exec()
    {
        
        while (1)
        {
            /* code */
        }
        
    }
};
int main(void)
{
    MyDevice self;
    self.exec();
}
