#include "stm32f10x.h"

enum Port
{
    PortA,
    PortB,
    PortC,
    PortD,
    PortE,
    PortF,
    PortG
};
enum class Pin
{
    Pin0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7,
    Pin8,
    Pin9,
    Pin10,
    Pin11,
    Pin12,
    Pin13,
    Pin14,
    Pin15
};
class IOMode
{
public:
    static const GPIOMode_TypeDef AIN = GPIO_Mode_AIN;
    static const GPIOMode_TypeDef IN_FLOATING = GPIO_Mode_IN_FLOATING;
    static const GPIOMode_TypeDef IPD = GPIO_Mode_IPD;
    static const GPIOMode_TypeDef IPU = GPIO_Mode_IPU;
    static const GPIOMode_TypeDef Out_OD = GPIO_Mode_Out_OD;
    static const GPIOMode_TypeDef Out_PP = GPIO_Mode_Out_PP;
    static const GPIOMode_TypeDef AF_OD = GPIO_Mode_AF_OD;
    static const GPIOMode_TypeDef AF_PP = GPIO_Mode_AF_PP;
};
class IOSpeed
{
public:
    static const GPIOSpeed_TypeDef _50MHz = GPIO_Speed_50MHz;
    static const GPIOSpeed_TypeDef _2MHz = GPIO_Speed_2MHz;
    static const GPIOSpeed_TypeDef _10MHz = GPIO_Speed_10MHz;
};
// 前向声明
class IO_Read;
class IO_Init;
class IO_Write;

// IO类 - 零内存开销设计
class IO
{
    static uint16_t used[3];
public:
    static bool sign(Port _port, Pin _pin)
    {
        if (used[_port] & (1 << static_cast<uint16_t>(_pin)))
        {
            return false;
        }
        else
        {
            used[_port] &= (1 << static_cast<uint16_t>(_pin));
            return true;
        }
    }
    // 初始化操作代理
    class InitProxy
    {
    public:
        // 端口代理
        class PortProxy
        {
        public:
            // 初始化单个引脚，可指定模式
            // 所有引脚的初始化方法
            void Pin0(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_0, mode); }
            void Pin1(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_1, mode); }
            void Pin2(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_2, mode); }
            void Pin3(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_3, mode); }
            void Pin4(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_4, mode); }
            void Pin5(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_5, mode); }
            void Pin6(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_6, mode); }
            void Pin7(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_7, mode); }
            void Pin8(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_8, mode); }
            void Pin9(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_9, mode); }
            void Pin10(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_10, mode); }
            void Pin11(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_11, mode); }
            void Pin12(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_12, mode); }
            void Pin13(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_13, mode); }
            void Pin14(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_14, mode); }
            void Pin15(GPIOMode_TypeDef mode) const { doInitPin(port, GPIO_Pin_15, mode); }

            // 可变参数模板函数，初始化多个引脚
            template <typename... Args>
            void Pins(GPIOMode_TypeDef mode, Args... pins) const
            {
                uint16_t pinMask = 0;
                appendPins(pinMask, pins...);
                doInitPins(port, pinMask, mode);
            }
            explicit PortProxy(Port p) : port(p) {}

        private:
            Port port;
            // 递归展开可变参数
            template <typename... Args>
            static void appendPins(uint16_t &mask, uint8_t pin, Args... pins)
            {
                mask |= (1 << pin);
                appendPins(mask, pins...);
            }

            // 可变参数终止条件
            static void appendPins(uint16_t &mask) {}

            // 实际执行引脚初始化
            static void doInitPin(Port port, uint16_t pin, GPIOMode_TypeDef mode)
            {
                GPIO_InitTypeDef GPIO_InitStructure;
                GPIO_InitStructure.GPIO_Pin = pin;
                GPIO_InitStructure.GPIO_Mode = mode;
                GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

                GPIO_TypeDef *GPIOx = getGPIOx(port);
                GPIO_Init(GPIOx, &GPIO_InitStructure);
            }

            // 初始化多个引脚
            static void doInitPins(Port port, uint16_t pinMask, GPIOMode_TypeDef mode)
            {
                GPIO_InitTypeDef GPIO_InitStructure;
                GPIO_InitStructure.GPIO_Pin = pinMask;
                GPIO_InitStructure.GPIO_Mode = mode;
                GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

                GPIO_TypeDef *GPIOx = getGPIOx(port);
                GPIO_Init(GPIOx, &GPIO_InitStructure);
            }

            friend class IO::InitProxy;
        };

        // 各端口代理对象
        PortProxy PortA{/*Port*/ ::PortA};
        PortProxy PortB{::PortB};
        PortProxy PortC{::PortC};
        PortProxy PortD{::PortD};
        PortProxy PortE{::PortE};
        PortProxy PortF{::PortF};
        PortProxy PortG{::PortG};
    };

    // 读取操作代理
    class ReadProxy
    {
    public:
        // 端口代理
        class PortProxy
        {
        public:
            // 读取单个引脚
            bool Pin0() const
            {
                return doReadPin(port, GPIO_Pin_0);
            }

            // 所有引脚的读取方法
            bool Pin1() const { return doReadPin(port, GPIO_Pin_1); }
            bool Pin2() const { return doReadPin(port, GPIO_Pin_2); }
            bool Pin3() const { return doReadPin(port, GPIO_Pin_3); }
            bool Pin4() const { return doReadPin(port, GPIO_Pin_4); }
            bool Pin5() const { return doReadPin(port, GPIO_Pin_5); }
            bool Pin6() const { return doReadPin(port, GPIO_Pin_6); }
            bool Pin7() const { return doReadPin(port, GPIO_Pin_7); }
            bool Pin8() const { return doReadPin(port, GPIO_Pin_8); }
            bool Pin9() const { return doReadPin(port, GPIO_Pin_9); }
            bool Pin10() const { return doReadPin(port, GPIO_Pin_10); }
            bool Pin11() const { return doReadPin(port, GPIO_Pin_11); }
            bool Pin12() const { return doReadPin(port, GPIO_Pin_12); }
            bool Pin13() const { return doReadPin(port, GPIO_Pin_13); }
            bool Pin14() const { return doReadPin(port, GPIO_Pin_14); }
            bool Pin15() const { return doReadPin(port, GPIO_Pin_15); }

            // 读取整个端口
            uint16_t Pins() const
            {
                return doReadPort(port);
            }
            explicit PortProxy(Port p) : port(p) {}

        private:
            Port port;
            // 读单个引脚
            static bool doReadPin(Port port, uint16_t pin)
            {
                GPIO_TypeDef *GPIOx = getGPIOx(port);
                return GPIO_ReadInputDataBit(GPIOx, pin) != 0;
            }

            // 读整个端口
            static uint16_t doReadPort(Port port)
            {
                GPIO_TypeDef *GPIOx = getGPIOx(port);
                return GPIO_ReadInputData(GPIOx);
            }

            friend class IO::ReadProxy;
        };

        // 各端口代理对象
        PortProxy PortA{::PortA};
        PortProxy PortB{::PortB};
        PortProxy PortC{::PortC};
        PortProxy PortD{::PortD};
        PortProxy PortE{::PortE};
        PortProxy PortF{::PortF};
        PortProxy PortG{::PortG};
    };

    // 写入操作代理
    class WriteProxy
    {
    public:
        // 端口代理
        class PortProxy
        {
        public:
            // 写入单个引脚
            void Pin0(uint8_t value) const
            {
                doWritePin(port, GPIO_Pin_0, value != 0 ? Bit_SET : Bit_RESET);
            }

            // 所有引脚的写入方法
            void Pin1(uint8_t value) const { doWritePin(port, GPIO_Pin_1, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin2(uint8_t value) const { doWritePin(port, GPIO_Pin_2, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin3(uint8_t value) const { doWritePin(port, GPIO_Pin_3, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin4(uint8_t value) const { doWritePin(port, GPIO_Pin_4, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin5(uint8_t value) const { doWritePin(port, GPIO_Pin_5, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin6(uint8_t value) const { doWritePin(port, GPIO_Pin_6, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin7(uint8_t value) const { doWritePin(port, GPIO_Pin_7, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin8(uint8_t value) const { doWritePin(port, GPIO_Pin_8, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin9(uint8_t value) const { doWritePin(port, GPIO_Pin_9, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin10(uint8_t value) const { doWritePin(port, GPIO_Pin_10, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin11(uint8_t value) const { doWritePin(port, GPIO_Pin_11, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin12(uint8_t value) const { doWritePin(port, GPIO_Pin_12, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin13(uint8_t value) const { doWritePin(port, GPIO_Pin_13, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin14(uint8_t value) const { doWritePin(port, GPIO_Pin_14, value != 0 ? Bit_SET : Bit_RESET); }
            void Pin15(uint8_t value) const { doWritePin(port, GPIO_Pin_15, value != 0 ? Bit_SET : Bit_RESET); }

            // 写入整个端口
            void Pins(uint16_t value) const
            {
                doWritePort(port, value);
            }

        private:
            Port port;
            explicit PortProxy(Port p) : port(p) {}

            // 写单个引脚
            static void doWritePin(Port port, uint16_t pin, BitAction value)
            {
                GPIO_TypeDef *GPIOx = getGPIOx(port);
                GPIO_WriteBit(GPIOx, pin, value);
            }

            // 写整个端口
            static void doWritePort(Port port, uint16_t value)
            {
                GPIO_TypeDef *GPIOx = getGPIOx(port);
                GPIO_Write(GPIOx, value);
            }

            friend class IO::WriteProxy;
        };

        // 各端口代理对象
        PortProxy PortA{::PortA};
        PortProxy PortB{::PortB};
        PortProxy PortC{::PortC};
        PortProxy PortD{::PortD};
        PortProxy PortE{::PortE};
        PortProxy PortF{::PortF};
        PortProxy PortG{::PortG};
    };
    // 获取GPIO基址的辅助函数
    static GPIO_TypeDef *getGPIOx(::Port port)
    {
        switch (port)
        {
        case PortA:
            return GPIOA;
        case PortB:
            return GPIOB;
        case PortC:
            return GPIOC;
        case PortD:
            return GPIOD;
        case PortE:
            return GPIOE;
        case PortF:
            return GPIOF;
        case PortG:
            return GPIOG;
        default:
            return nullptr;
        }
    }
    static uint16_t getPinx(::Pin port)
    {
        return 1 << static_cast<uint16_t>(port);
    }
    static inline uint8_t ReadInputDataBit(Port port, Pin pin)
    {
        return GPIO_ReadInputDataBit(IO::getGPIOx(port), IO::getPinx(pin));
    }
    static inline uint16_t ReadInputData(Port port)
    {
        return GPIO_ReadInputData(IO::getGPIOx(port));
    }
    static inline uint8_t ReadOutputDataBit(Port port, Pin pin)
    {
        return GPIO_ReadOutputDataBit(IO::getGPIOx(port), IO::getPinx(pin));
    }
    static inline uint16_t ReadOutputData(Port port)
    {
        return GPIO_ReadOutputData(IO::getGPIOx(port));
    }
    static void SetBits(Port GPIOx, Pin GPIO_Pin)
    {
        GPIO_SetBits(IO::getGPIOx(GPIOx), IO::getPinx(GPIO_Pin));
    }
    static void ResetBits(Port GPIOx, Pin GPIO_Pin)
    {
        GPIO_ResetBits(IO::getGPIOx(GPIOx), IO::getPinx(GPIO_Pin));
    }
    static void WriteBit(Port GPIOx, Pin GPIO_Pin, bool val)
    {
        GPIO_WriteBit(IO::getGPIOx(GPIOx), IO::getPinx(GPIO_Pin), static_cast<BitAction>(val));
    }
    static void Write(Port GPIOx, Pin PortVal)
    {
        GPIO_Write(IO::getGPIOx(GPIOx), IO::getPinx(PortVal));
    }
    // 公共操作访问点
    InitProxy init;
    ReadProxy read;
    WriteProxy write;
};
uint16_t IO::used[3] = {0, 0, 0};
static const IO io;

namespace Device
{
    class LED
    {
        const Port port;
        const Pin pin;
        LED(Port _port, Pin _pin, GPIOSpeed_TypeDef Speed = IOSpeed::_50MHz, GPIOMode_TypeDef mode = IOMode::Out_PP)
            : pin(_pin), port(_port)
        {
            if (io.sign(_port, _pin))
            {
                GPIO_InitTypeDef GPIO_InitStructure;
                GPIO_InitStructure.GPIO_Pin = IO::getPinx(_pin);
                GPIO_InitStructure.GPIO_Mode = mode;
                GPIO_InitStructure.GPIO_Speed = Speed;
                // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
                GPIO_TypeDef *GPIOx = IO::getGPIOx(port);
                GPIO_Init(GPIOx, &GPIO_InitStructure);
            }
        }
    };
};

class MyDevice
{
    void exec()
    {

        io.init.PortA.Pin3(IOMode::Out_OD);          // 初始化PortA的3号口
        io.init.PortA.Pins(IOMode::Out_PP, 1, 2, 3); // 初始化PortA的1,2,3...（数量可变）号口
        io.read.PortA.Pin0();                        // 读PortA的0号口(bool)
        io.read.PortA.Pins();                        // 读PortA返回uint16_t
        io.write.PortA.Pin0(1);                      // 写入1到ProtA的0号口
        io.write.PortA.Pin0(0);                      // 写入0到ProtA的0号口
        io.write.PortA.Pins(0b1111111111111111);     // 写入1111111111111111到ProtA
    }
};
