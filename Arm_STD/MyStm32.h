#include "stm32f10x.h"
enum Port_abandoned
{
    PortA,
    PortB,
    PortC,
    PortD,
    PortE,
    PortF,
    PortG
};
class Port
{
public:
    static GPIO_TypeDef *PortA;
    static GPIO_TypeDef *PortB;
    static GPIO_TypeDef *PortC;
    static GPIO_TypeDef *PortD;
    static GPIO_TypeDef *PortE;
    static GPIO_TypeDef *PortF;
    static GPIO_TypeDef *PortG;
};
GPIO_TypeDef *Port::PortA = GPIOA;
GPIO_TypeDef *Port::PortB = GPIOB;
GPIO_TypeDef *Port::PortC = GPIOC;
GPIO_TypeDef *Port::PortD = GPIOD;
GPIO_TypeDef *Port::PortE = GPIOE;
GPIO_TypeDef *Port::PortF = GPIOF;
GPIO_TypeDef *Port::PortG = GPIOG;

enum Pin_abandoned
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
class Pin
{
public:
    static const uint16_t Pin0 = GPIO_Pin_0;
    static const uint16_t Pin1 = GPIO_Pin_1;
    static const uint16_t Pin2 = GPIO_Pin_2;
    static const uint16_t Pin3 = GPIO_Pin_3;
    static const uint16_t Pin4 = GPIO_Pin_4;
    static const uint16_t Pin5 = GPIO_Pin_5;
    static const uint16_t Pin6 = GPIO_Pin_6;
    static const uint16_t Pin7 = GPIO_Pin_7;
    static const uint16_t Pin8 = GPIO_Pin_8;
    static const uint16_t Pin9 = GPIO_Pin_9;
    static const uint16_t Pin10 = GPIO_Pin_10;
    static const uint16_t Pin11 = GPIO_Pin_11;
    static const uint16_t Pin12 = GPIO_Pin_12;
    static const uint16_t Pin13 = GPIO_Pin_13;
    static const uint16_t Pin14 = GPIO_Pin_14;
    static const uint16_t Pin15 = GPIO_Pin_15;
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
    static bool sign(const GPIO_TypeDef *_port,const uint16_t _pin)
    {
        int index = 0;
        if (_port == Port::PortA)
            index = 0;
        else if (_port == Port::PortB)
            index = 1;
        else if (_port == Port::PortC)
            index = 2;
        else if (_port == Port::PortD)
            index = 3;
        if (used[index] & _pin)
        {
            return false;
        }
        else
        {
            used[index] &= _pin;
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
            explicit PortProxy(Port_abandoned p) : port(p) {}

        private:
            Port_abandoned port;
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
            static void doInitPin(Port_abandoned port, uint16_t pin, GPIOMode_TypeDef mode)
            {
                GPIO_InitTypeDef GPIO_InitStructure;
                GPIO_InitStructure.GPIO_Pin = pin;
                GPIO_InitStructure.GPIO_Mode = mode;
                GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

                GPIO_TypeDef *GPIOx = getGPIOx(port);
                GPIO_Init(GPIOx, &GPIO_InitStructure);
            }

            // 初始化多个引脚
            static void doInitPins(Port_abandoned port, uint16_t pinMask, GPIOMode_TypeDef mode)
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
        PortProxy PortA{/*Port_abandoned*/ ::PortA};
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
            explicit PortProxy(Port_abandoned p) : port(p) {}

        private:
            Port_abandoned port;
            // 读单个引脚
            static bool doReadPin(Port_abandoned port, uint16_t pin)
            {
                GPIO_TypeDef *GPIOx = getGPIOx(port);
                return GPIO_ReadInputDataBit(GPIOx, pin) != 0;
            }

            // 读整个端口
            static uint16_t doReadPort(Port_abandoned port)
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
            void Pin0(uint8_t value) const { doWritePin(port, GPIO_Pin_0, value != 0 ? Bit_SET : Bit_RESET); }
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
            Port_abandoned port;
            explicit PortProxy(Port_abandoned p) : port(p) {}

            // 写单个引脚
            static void doWritePin(Port_abandoned port, uint16_t pin, BitAction value)
            {
                GPIO_TypeDef *GPIOx = getGPIOx(port);
                GPIO_WriteBit(GPIOx, pin, value);
            }

            // 写整个端口
            static void doWritePort(Port_abandoned port, uint16_t value)
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
    static GPIO_TypeDef *getGPIOx(::Port_abandoned port)
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
    static uint16_t getPinx(::Pin_abandoned port)
    {
        return 1 << static_cast<uint16_t>(port);
    }
    static inline uint8_t ReadInputDataBit(Port_abandoned port, Pin_abandoned pin)
    {
        return GPIO_ReadInputDataBit(IO::getGPIOx(port), IO::getPinx(pin));
    }
    static inline uint16_t ReadInputData(Port_abandoned port)
    {
        return GPIO_ReadInputData(IO::getGPIOx(port));
    }
    static inline uint8_t ReadOutputDataBit(Port_abandoned port, Pin_abandoned pin)
    {
        return GPIO_ReadOutputDataBit(IO::getGPIOx(port), IO::getPinx(pin));
    }
    static inline uint16_t ReadOutputData(Port_abandoned port)
    {
        return GPIO_ReadOutputData(IO::getGPIOx(port));
    }
    static void SetBits(Port_abandoned GPIOx, Pin_abandoned GPIO_Pin)
    {
        GPIO_SetBits(IO::getGPIOx(GPIOx), IO::getPinx(GPIO_Pin));
    }
    static void ResetBits(Port_abandoned GPIOx, Pin_abandoned GPIO_Pin)
    {
        GPIO_ResetBits(IO::getGPIOx(GPIOx), IO::getPinx(GPIO_Pin));
    }
    static void WriteBit(Port_abandoned GPIOx, Pin_abandoned GPIO_Pin, bool val)
    {
        GPIO_WriteBit(IO::getGPIOx(GPIOx), IO::getPinx(GPIO_Pin), static_cast<BitAction>(val));
    }
    static void Write(Port_abandoned GPIOx, Pin_abandoned PortVal)
    {
        GPIO_Write(IO::getGPIOx(GPIOx), IO::getPinx(PortVal));
    }
    // 公共操作访问点
    InitProxy init;
    ReadProxy read;
    // WriteProxy write;

    class
    {
        GPIO_TypeDef *port;
        static void doInitPin(GPIO_TypeDef *port, uint16_t pin, GPIOMode_TypeDef mode)
        {
            GPIO_InitTypeDef GPIO_InitStructure;
            GPIO_InitStructure.GPIO_Pin = pin;
            GPIO_InitStructure.GPIO_Mode = mode;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(port, &GPIO_InitStructure);
        }

    public:
        class Port_Init
        {
            GPIO_TypeDef *port;

        public:
            Port_Init(GPIO_TypeDef *_port) : port(_port) {}
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
        };
        Port_Init ProtA{Port::PortA};
        Port_Init ProtB{Port::PortB};
        Port_Init ProtC{Port::PortC};
        Port_Init ProtD{Port::PortD};
        Port_Init ProtE{Port::PortE};
        Port_Init ProtF{Port::PortF};
    } ini;

    class
    {
        GPIO_TypeDef *port;
        static void doWritePin(GPIO_TypeDef *port, uint16_t pin, BitAction value)
        {
            GPIO_WriteBit(port, pin, value);
        }

    public:
        class Port_Write
        {
            GPIO_TypeDef *port;

        public:
            Port_Write(GPIO_TypeDef *_port) : port(_port) {}
            void Pin0(uint8_t value) const { doWritePin(port, GPIO_Pin_0, value != 0 ? Bit_SET : Bit_RESET); }
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
        };
        Port_Write ProtA{Port::PortA};
        Port_Write ProtB{Port::PortB};
        Port_Write ProtC{Port::PortC};
        Port_Write ProtD{Port::PortD};
        Port_Write ProtE{Port::PortE};
        Port_Write ProtF{Port::PortF};
    } wri;

    class
    {
        Port port;
        static bool doReadPin(const GPIO_TypeDef *prot, uint16_t pin)
        {
            return GPIO_ReadInputDataBit(const_cast<GPIO_TypeDef *>(prot), pin) != 0;
        }

    public:
        class Port_read
        {
            GPIO_TypeDef *port;

        public:
            Port_read(GPIO_TypeDef *_port) : port(_port) {}
            void Pin0(uint8_t value) const { doReadPin(port, GPIO_Pin_0); }
            void Pin1(uint8_t value) const { doReadPin(port, GPIO_Pin_1); }
            void Pin2(uint8_t value) const { doReadPin(port, GPIO_Pin_2); }
            void Pin3(uint8_t value) const { doReadPin(port, GPIO_Pin_3); }
            void Pin4(uint8_t value) const { doReadPin(port, GPIO_Pin_4); }
            void Pin5(uint8_t value) const { doReadPin(port, GPIO_Pin_5); }
            void Pin6(uint8_t value) const { doReadPin(port, GPIO_Pin_6); }
            void Pin7(uint8_t value) const { doReadPin(port, GPIO_Pin_7); }
            void Pin8(uint8_t value) const { doReadPin(port, GPIO_Pin_8); }
            void Pin9(uint8_t value) const { doReadPin(port, GPIO_Pin_9); }
            void Pin10(uint8_t value) const { doReadPin(port, GPIO_Pin_10); }
            void Pin11(uint8_t value) const { doReadPin(port, GPIO_Pin_11); }
            void Pin12(uint8_t value) const { doReadPin(port, GPIO_Pin_12); }
            void Pin13(uint8_t value) const { doReadPin(port, GPIO_Pin_13); }
            void Pin14(uint8_t value) const { doReadPin(port, GPIO_Pin_14); }
            void Pin15(uint8_t value) const { doReadPin(port, GPIO_Pin_15); }
        };
        Port_read ProtA{Port::PortA};
        Port_read ProtB{Port::PortA};
        Port_read ProtC{Port::PortA};
        Port_read ProtD{Port::PortA};
        Port_read ProtE{Port::PortA};
        Port_read ProtF{Port::PortA};
    } rea;
} static io;
uint16_t IO::used[3] = {0, 0, 0};

// RCC_LSEConfig(uint8_t RCC_LSE);
// 用于配置低速外部（LSE）时钟的工作模式。根据传入的参数（通常为不同的启动方式或配置选项），设置LSE晶振的运行方式。

// RCC_LSICmd(FunctionalState NewState);
// 用于开启或关闭低速内部（LSI）振荡器。参数通常为 ENABLE 或 DISABLE，用于控制该振荡器是否工作。

// RCC_RTCCLKConfig(uint32_t RTCCL_RCCKSource);
// 用于配置实时时钟（RTC）的时钟源。这可以选择为LSE、LSI或其它外部时钟输入，确保RTC模块使用正确的时钟信号。

// RCC_RTCCLKCmd(FunctionalState NewState);
// 用于使能或禁用RTC时钟。通过传递 ENABLE / DISABLE 来控制RTC模块是否获得时钟信号。

//                                          RCC_GetClocksFreq(RCC_ClocksTypeDef RCC_Clocks);
// *用于获取系统各个时钟（如系统时钟 SYSCLK, AHB时钟, APB1 / 2时钟等）的当前频率配置。结果会填充到传入的结构体中。

//                                                        RCC_AHBPeriphClockCmd(uint32_t AHBPe_RCCriph, FunctionalState NewState);
// 用于控制 AHB 总线上外设的时钟开关。传入具体外设标识和开关状态，决定该外设是否获得时钟RCC_ lockC = md(uRCC_  Func = tionalState NewState);
// 与上一个类似，但用于 APB2 总线上外设的时钟控制。

// RCC_APB1PeriphClockCmd(uint32_t APB1P_RCCeriph, FunctionalState NewState);
// 同样用于 APB1 总线外设的时钟控制

class Clock
{
public:
    class RccProt
    {
    public:
        static const uint32_t AFIO_RCC= ((uint32_t)0x00000001);
        static const uint32_t GPIOA_RCC = ((uint32_t)0x00000004);
        static const uint32_t GPIOB_RCC = ((uint32_t)0x00000008);
        static const uint32_t GPIOC_RCC = ((uint32_t)0x00000010);
        static const uint32_t GPIOD_RCC = ((uint32_t)0x00000020);
        static const uint32_t GPIOE_RCC = ((uint32_t)0x00000040);
        static const uint32_t GPIOF_RCC = ((uint32_t)0x00000080);
        static const uint32_t GPIOG_RCC = ((uint32_t)0x00000100);
        static const uint32_t ADC1_RCC= ((uint32_t)0x00000200);
        static const uint32_t ADC2_RCC= ((uint32_t)0x00000400);
        static const uint32_t TIM1_RCC= ((uint32_t)0x00000800);
        static const uint32_t SPI1_RCC= ((uint32_t)0x00001000);
        static const uint32_t TIM8_RCC= ((uint32_t)0x00002000);
        static const uint32_t USART_RCC = ((uint32_t)0x00004000);
        static const uint32_t ADC3_RCC= ((uint32_t)0x00008000);
        static const uint32_t TIM15_RCC = ((uint32_t)0x00010000);
        static const uint32_t TIM16_RCC = ((uint32_t)0x00020000);
        static const uint32_t TIM17_RCC = ((uint32_t)0x00040000);
        static const uint32_t TIM9_RCC= ((uint32_t)0x00080000);
        static const uint32_t TIM10_RCC = ((uint32_t)0x00100000);
        static const uint32_t TIM11_RCC = ((uint32_t)0x00200000);
    }port_to_open;
    class Open
    {
    public:
        static void APB1Periph(uint32_t RCC_APB1Periph)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph, ENABLE);
        }
        static void APB2Periph(uint32_t RCC_APB2Periph)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
        }
        static void AHBPeriph(uint32_t AHBPe_RCCriph)
        {
            RCC_AHBPeriphClockCmd(AHBPe_RCCriph, ENABLE);
        }

    } open;
    class Close
    {
    public:
        static void APB1Periph(uint32_t RCC_APB1Periph)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph, DISABLE);
        }
        static void APB2Periph(uint32_t RCC_APB2Periph)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph, DISABLE);
        }
        static void AHBPeriph(uint32_t RCC_AHBPeriph)
        {
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph, DISABLE);
        }

    } close;
} clock;

namespace Device
{
    class LED
    {
        const GPIO_TypeDef *port;
        const uint16_t pin;

    public:
        LED(const GPIO_TypeDef *_port, const uint16_t _pin, GPIOSpeed_TypeDef Speed = IOSpeed::_50MHz, GPIOMode_TypeDef mode = IOMode::Out_PP)
            : pin(_pin), port(_port)
        {
            if (io.sign(_port, _pin))
            {
                clock.open.APB2Periph(clock.port_to_open.GPIOA_RCC);
                GPIO_InitTypeDef GPIO_InitStructure;
                GPIO_InitStructure.GPIO_Pin = pin;
                GPIO_InitStructure.GPIO_Mode = mode;
                GPIO_InitStructure.GPIO_Speed = Speed;
                GPIO_TypeDef *GPIOx = const_cast<GPIO_TypeDef *>(port);
                GPIO_Init(GPIOx, &GPIO_InitStructure);
                io.ResetBits(PortA, Pin0);
            }
        }
        void open()
        {
        }

        void close()
        {
        }
    };
};
