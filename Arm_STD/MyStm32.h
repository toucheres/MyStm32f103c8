#include "stm32f10x.h"
#include <stdarg.h>
extern "C"
{
// #include "Delay.h"
#include "OLED.h"
}
#define timer2_fun extern "C" void TIM2_IRQHandler(void)
#define timer3_fun extern "C" void TIM3_IRQHandler(void)
#define timer4_fun extern "C" void TIM4_IRQHandler(void)
// #include <vector>
class Port
{
public:
  static GPIO_TypeDef *const A;
  static GPIO_TypeDef *const B;
  static GPIO_TypeDef *const C;
  static GPIO_TypeDef *const D;
  static GPIO_TypeDef *const E;
  static GPIO_TypeDef *const F;
  static GPIO_TypeDef *const G;
};
inline GPIO_TypeDef *const Port::A = GPIOA;
inline GPIO_TypeDef *const Port::B = GPIOB;
inline GPIO_TypeDef *const Port::C = GPIOC;
inline GPIO_TypeDef *const Port::D = GPIOD;
inline GPIO_TypeDef *const Port::E = GPIOE;
inline GPIO_TypeDef *const Port::F = GPIOF;
inline GPIO_TypeDef *const Port::G = GPIOG;
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
// IO类 - 零内存开销设计
class IO
{
  static uint16_t used[3];
  // IO()=default;
public:
  static bool sign(const GPIO_TypeDef *_port, const uint16_t _pin)
  {
    int index = 0;
    if (_port == Port::A)
      index = 0;
    else if (_port == Port::B)
      index = 1;
    else if (_port == Port::C)
      index = 2;
    else if (_port == Port::D)
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

  class
  {
    GPIO_TypeDef *port;
    static void doInitPin(GPIO_TypeDef *port, uint16_t pin,
                          GPIOMode_TypeDef mode)
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
      void Pin0(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_0, mode);
      }
      void Pin1(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_1, mode);
      }
      void Pin2(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_2, mode);
      }
      void Pin3(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_3, mode);
      }
      void Pin4(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_4, mode);
      }
      void Pin5(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_5, mode);
      }
      void Pin6(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_6, mode);
      }
      void Pin7(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_7, mode);
      }
      void Pin8(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_8, mode);
      }
      void Pin9(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_9, mode);
      }
      void Pin10(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_10, mode);
      }
      void Pin11(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_11, mode);
      }
      void Pin12(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_12, mode);
      }
      void Pin13(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_13, mode);
      }
      void Pin14(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_14, mode);
      }
      void Pin15(GPIOMode_TypeDef mode) const
      {
        doInitPin(port, GPIO_Pin_15, mode);
      }
    };
    Port_Init ProtA{Port::A};
    Port_Init ProtB{Port::B};
    Port_Init ProtC{Port::C};
    Port_Init ProtD{Port::D};
    Port_Init ProtE{Port::E};
    Port_Init ProtF{Port::F};
  } static init;

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
      void Pin0(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_0, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin1(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_1, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin2(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_2, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin3(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_3, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin4(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_4, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin5(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_5, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin6(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_6, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin7(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_7, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin8(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_8, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin9(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_9, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin10(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_10, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin11(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_11, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin12(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_12, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin13(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_13, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin14(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_14, value != 0 ? Bit_SET : Bit_RESET);
      }
      void Pin15(uint8_t value) const
      {
        doWritePin(port, GPIO_Pin_15, value != 0 ? Bit_SET : Bit_RESET);
      }
    };
    Port_Write ProtA{Port::A};
    Port_Write ProtB{Port::B};
    Port_Write ProtC{Port::C};
    Port_Write ProtD{Port::D};
    Port_Write ProtE{Port::E};
    Port_Write ProtF{Port::F};
  } static write;

  class
  {
    Port port;
    static bool doReadPin(GPIO_TypeDef *prot, uint16_t pin)
    {
      return GPIO_ReadInputDataBit(prot, pin) != 0;
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
    Port_read ProtA{Port::A};
    Port_read ProtB{Port::A};
    Port_read ProtC{Port::A};
    Port_read ProtD{Port::A};
    Port_read ProtE{Port::A};
    Port_read ProtF{Port::A};
  } static read;

  static uint16_t read_port(GPIO_TypeDef *port)
  {
    return GPIO_ReadInputData(port);
  }
  static uint8_t read_pin(GPIO_TypeDef *port, uint16_t pin)
  {
    return GPIO_ReadInputDataBit(port, pin);
  }
  static void Write_port(GPIO_TypeDef *port, uint16_t val)
  {
    GPIO_Write(port, val);
  }
  static void Write_pin(GPIO_TypeDef *port, uint16_t pin, bool val)
  {
    GPIO_WriteBit(port, pin, val == true ? Bit_SET : Bit_RESET);
  }
  static void Write_pin(GPIO_TypeDef *port, uint16_t pin, BitAction val)
  {
    GPIO_WriteBit(port, pin, val);
  }
  static void Change_pin(GPIO_TypeDef *port, uint16_t pin)
  {
    IO::Write_pin(port, pin, !IO::read_pin(port, pin));
  }
} static io;
inline uint16_t IO::used[3] = {0, 0, 0};

class Clock
{
public:
  class RccProt
  {
  public:
    constexpr static const uint32_t AFIO_RCC = ((uint32_t)0x00000001);
    constexpr static const uint32_t GPIOA_RCC = ((uint32_t)0x00000004);
    constexpr static const uint32_t GPIOB_RCC = ((uint32_t)0x00000008);
    constexpr static const uint32_t GPIOC_RCC = ((uint32_t)0x00000010);
    constexpr static const uint32_t GPIOD_RCC = ((uint32_t)0x00000020);
    constexpr static const uint32_t GPIOE_RCC = ((uint32_t)0x00000040);
    constexpr static const uint32_t GPIOF_RCC = ((uint32_t)0x00000080);
    constexpr static const uint32_t GPIOG_RCC = ((uint32_t)0x00000100);
    constexpr static const uint32_t ADC1_RCC = ((uint32_t)0x00000200);
    constexpr static const uint32_t ADC2_RCC = ((uint32_t)0x00000400);
    constexpr static const uint32_t Timer_1_RCC = ((uint32_t)0x00000800);
    constexpr static const uint32_t SPI1_RCC = ((uint32_t)0x00001000);
    constexpr static const uint32_t TIM8_RCC = ((uint32_t)0x00002000);
    constexpr static const uint32_t USART_RCC = ((uint32_t)0x00004000);
    constexpr static const uint32_t ADC3_RCC = ((uint32_t)0x00008000);
    constexpr static const uint32_t Timer_15_RCC = ((uint32_t)0x00010000);
    constexpr static const uint32_t Timer_16_RCC = ((uint32_t)0x00020000);
    constexpr static const uint32_t Timer_17_RCC = ((uint32_t)0x00040000);
    constexpr static const uint32_t TIM9_RCC = ((uint32_t)0x00080000);
    constexpr static const uint32_t Timer_10_RCC = ((uint32_t)0x00100000);
    constexpr static const uint32_t Timer_11_RCC = ((uint32_t)0x00200000);
  } port_to_open;
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
    static void port(GPIO_TypeDef *port) {
      // GPIOA_BASE = APB2PERIPH_BASE + 0x0800;
      uint32_t portAddr = reinterpret_cast<uint32_t>(port);
      uint32_t offset = portAddr - APB2PERIPH_BASE;
      uint8_t index = offset / 0x0400;
      // 根据偏移量启用相应的时钟
      RCC_APB2PeriphClockCmd(1 << index, ENABLE);
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
    static void port(GPIO_TypeDef *port)
    {
      // GPIOA_BASE = APB2PERIPH_BASE + 0x0800;
      uint32_t portAddr = reinterpret_cast<uint32_t>(port);
      uint32_t offset = portAddr - APB2PERIPH_BASE;
      uint8_t index = offset / 0x0400;
      // 根据偏移量启用相应的时钟
      RCC_APB2PeriphClockCmd(1 << index, DISABLE);
    }
  } close;
  // Timer1为总线2(高级)
  // Timer2/3/4为总线1(通用)
  // GPIO a~g 中断为总线2
} static clocks;

class time_ms
{
public:
  constexpr time_ms(uint16_t _val) : val(_val) {}
  uint16_t val;
};

class time_s
{
public:
  constexpr time_s(uint16_t _val) : val(_val) {}
  uint16_t val;
};

inline constexpr time_ms operator"" _ms(unsigned long long _val)
{
  return time_ms{static_cast<uint16_t>(_val)};
}
inline constexpr time_s operator"" _s(unsigned long long _val)
{
  return time_s{static_cast<uint16_t>(_val)};
}
namespace Device
{
  class Timer
  {
  public:
    class Universal_timer
    {
    public:
      class TimerType
      {
      public:
        static const uint8_t timer_2 = 0;
        static const uint8_t timer_3 = 1;
        static const uint8_t timer_4 = 2;
      };
      // 中断优先级配置
      // #define BASIC_TIM TIM4
      // #define BASIC_TIM_APBxClock_FUN RCC_APB1PeriphClockCmd
      // #define BASIC_TIM_CLK RCC_APB1Periph_TIM4
      // #define BASIC_TIM_Period (1000 - 1)
      // #define BASIC_TIM_Prescaler 71
      // #define BASIC_TIM_IRQ TIM4_IRQn // 中断来源
      // #define BASIC_TIM_IRQHandler TIM6_IRQHandler
    private:
      uint8_t index;
      TIM_TypeDef *BASIC_TIM;

    public:
      Universal_timer(uint8_t timerType, time_ms times)
          : index(timerType), BASIC_TIM((TIM_TypeDef *)(APB1PERIPH_BASE + (0x0400 * index)))
      {
        NVIC_Config();
        TIM_Config(times.val);
      };
      Universal_timer(uint8_t timerType, time_s times)
          : index(timerType), BASIC_TIM(TIM2 + (0x0400) * (index))
      {
        NVIC_Config();
        TIM_Config(times.val * 1000);
      };
      void NVIC_Config()
      {
        NVIC_InitTypeDef NVIC_InitStructure;
        // 设置中断组为0
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
        // 设置中断来源
        // IRQn_Type;
        NVIC_InitStructure.NVIC_IRQChannel = index + 28;
        // 设置主优先级为 0
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        // 设置抢占优先级为3
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
      }

      // void TIM_Config(uint16_t ms_time)
      // {
      //     // 预分频器设为71，使得计数频率为72M/(71+1)=1MHz ，即计数一次
      //     // 1MHz = 10**6Hz
      //     uint16_t BASIC_TIM_Prescaler = 72*10-1;

      //     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

      //     // 开启定时器时钟,即内部时钟CK_INT=72M
      //     RCC_APB1PeriphClockCmd(((uint32_t)0x00000001) << (index), ENABLE);

      //     // 将毫秒转换为微秒，作为周期值
      //     // 例如：10ms = 10 * 1000us = 10000us，对应Period=9999
      //     TIM_TimeBaseStructure.TIM_Period = (ms_time*100) - 1;

      //     // 时钟预分频数
      //     TIM_TimeBaseStructure.TIM_Prescaler = BASIC_TIM_Prescaler;

      //     // 时钟分频因子，基本定时器没有，不用管
      //     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

      //     // 计数器计数模式，基本定时器只能向上计数，没有计数模式的设置
      //     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

      //     // 重复计数器的值，基本定时器没有，不用管
      //     TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

      //     // 初始化定时器
      //     TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);

      //     // 清除计数器中断标志位
      //     TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);

      //     // 开启计数器中断
      //     TIM_ITConfig(BASIC_TIM, TIM_IT_Update, ENABLE);

      //     // 使能计数器
      //     TIM_Cmd(BASIC_TIM, ENABLE);
      // }
      void TIM_Config(uint16_t ms_time)
      {
        // 两级分频方式来实现毫秒级定时
        // 第一级：72MHz / (71+1) = 1MHz（每微秒计数一次）
        uint16_t BASIC_TIM_Prescaler = 72 * 100 - 1;

        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

        // 开启定时器时钟
        RCC_APB1PeriphClockCmd(((uint32_t)0x00000001) << (index), ENABLE);

        // 第二级：使用 Period 值设置中断周期
        // 例如设置 ms_time=500，则 Period=500-1=499
        // 表示500ms触发一次中断
        TIM_TimeBaseStructure.TIM_Period = ms_time * 10 - 1;

        // 预分频值（72分频得到1MHz计数频率）
        TIM_TimeBaseStructure.TIM_Prescaler = BASIC_TIM_Prescaler;

        // 时钟分频因子
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

        // 向上计数模式
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

        // 不使用重复计数
        TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

        // 初始化定时器
        TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);

        // 清除计数器中断标志位
        TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);

        // 开启计数器中断
        TIM_ITConfig(BASIC_TIM, TIM_IT_Update, ENABLE);

        // 使能计数器
        TIM_Cmd(BASIC_TIM, ENABLE);
      }
    };
    class Advanced_timer
    {
    };
  };
  class LED
  {
    GPIO_TypeDef *port;
    uint16_t pin;

  public:
    LED(GPIO_TypeDef *_port, uint16_t _pin,
        GPIOSpeed_TypeDef Speed = IOSpeed::_50MHz,
        GPIOMode_TypeDef mode = IOMode::Out_PP)
        : pin(_pin), port(_port)
    {
      if (io.sign(_port, _pin))
      {
        clocks.open.port(Port::A);
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = pin;
        GPIO_InitStructure.GPIO_Mode = mode;
        GPIO_InitStructure.GPIO_Speed = Speed;
        GPIO_Init(port, &GPIO_InitStructure);
        io.Write_pin(port, pin, 0);
      }
    }
    void turn() { io.Change_pin(this->port, this->pin); }
  };
  class OLED
  {
  private:
    // 封装的字体大小常量
    enum FontSize
    {
      FONT_6X8 = 6, // 对应OLED_6X8
      FONT_8X16 = 8 // 对应OLED_8X16
    };

    // 填充模式
    enum FillMode
    {
      UNFILLED = 0,
      FILLED = 1
    };

  public:
    // 构造函数 - 初始化OLED
    OLED()
    {
      OLED_Init();
    }

    // 更新函数
    void Update()
    {
      OLED_Update();
    }

    void UpdateArea(int16_t x, int16_t y, uint8_t width, uint8_t height)
    {
      OLED_UpdateArea(x, y, width, height);
    }

    // 显存控制函数
    void Clear()
    {
      OLED_Clear();
    }

    void ClearArea(int16_t x, int16_t y, uint8_t width, uint8_t height)
    {
      OLED_ClearArea(x, y, width, height);
    }

    void Reverse()
    {
      OLED_Reverse();
    }

    void ReverseArea(int16_t x, int16_t y, uint8_t width, uint8_t height)
    {
      OLED_ReverseArea(x, y, width, height);
    }

    // 显示函数
    void ShowChar(int16_t x, int16_t y, char ch, uint8_t fontSize)
    {
      OLED_ShowChar(x, y, ch, fontSize);
    }

    void ShowString(int16_t x, int16_t y, const char *str, uint8_t fontSize)
    {
      // 注意：使用const修饰字符串参数，避免C++11警告
      OLED_ShowString(x, y, const_cast<char *>(str), fontSize);
    }

    void ShowNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize)
    {
      OLED_ShowNum(x, y, number, length, fontSize);
    }

    void ShowSignedNum(int16_t x, int16_t y, int32_t number, uint8_t length, uint8_t fontSize)
    {
      OLED_ShowSignedNum(x, y, number, length, fontSize);
    }

    void ShowHexNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize)
    {
      OLED_ShowHexNum(x, y, number, length, fontSize);
    }

    void ShowBinNum(int16_t x, int16_t y, uint32_t number, uint8_t length, uint8_t fontSize)
    {
      OLED_ShowBinNum(x, y, number, length, fontSize);
    }

    void ShowFloatNum(int16_t x, int16_t y, double number, uint8_t intLength,
                      uint8_t fraLength, uint8_t fontSize)
    {
      OLED_ShowFloatNum(x, y, number, intLength, fraLength, fontSize);
    }

    void ShowImage(int16_t x, int16_t y, uint8_t width, uint8_t height, const uint8_t *image)
    {
      OLED_ShowImage(x, y, width, height, image);
    }

    void Printf(int16_t x, int16_t y, uint8_t fontSize, const char *format, ...)
    {
      va_list args;
      va_start(args, format);
      // 因为va_list不能直接传递，需要创建一个包装函数或在此处展开实现
      // 这里简化处理，只传递格式和参数列表给原始函数
      OLED_Printf(x, y, fontSize, const_cast<char *>(format), args);
      va_end(args);
    }

    // 绘图函数
    void DrawPoint(int16_t x, int16_t y)
    {
      OLED_DrawPoint(x, y);
    }

    bool GetPoint(int16_t x, int16_t y)
    {
      return OLED_GetPoint(x, y) != 0;
    }

    void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
    {
      OLED_DrawLine(x0, y0, x1, y1);
    }

    void DrawRectangle(int16_t x, int16_t y, uint8_t width, uint8_t height, bool filled = false)
    {
      OLED_DrawRectangle(x, y, width, height, filled ? FILLED : UNFILLED);
    }

    void DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                      int16_t x2, int16_t y2, bool filled = false)
    {
      OLED_DrawTriangle(x0, y0, x1, y1, x2, y2, filled ? FILLED : UNFILLED);
    }

    void DrawCircle(int16_t x, int16_t y, uint8_t radius, bool filled = false)
    {
      OLED_DrawCircle(x, y, radius, filled ? FILLED : UNFILLED);
    }

    void DrawEllipse(int16_t x, int16_t y, uint8_t a, uint8_t b, bool filled = false)
    {
      OLED_DrawEllipse(x, y, a, b, filled ? FILLED : UNFILLED);
    }

    void DrawArc(int16_t x, int16_t y, uint8_t radius,
                 int16_t startAngle, int16_t endAngle, bool filled = false)
    {
      OLED_DrawArc(x, y, radius, startAngle, endAngle, filled ? FILLED : UNFILLED);
    }

    // 常量定义 - 与OLED.h中的宏定义保持一致
    static constexpr uint8_t FONT_SIZE_6X8 = OLED_6X8;
    static constexpr uint8_t FONT_SIZE_8X16 = OLED_8X16;
  };
}; // namespace Device
