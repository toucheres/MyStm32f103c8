#ifndef _TIMER_H_
#define _TIMER_H_

#include "stm32f10x.h"
#include <cstdint>
#include "MyStm32.h" // 为了使用time_ms和time_s类型

namespace Device
{
    class Timer
    {
    public:
        class Channal
        {
        public:
            uint8_t timer;
            uint8_t index;
            Channal(uint8_t _timer, uint8_t _index);
            uint32_t portRcc();
            inline Channal() = default;
            Timer::Channal &operator=(Timer::Channal &&that);
            uint16_t getPin();
            GPIO_TypeDef *getPort();

            // 动态初始化channal(标准库居然没有)
            void static TIM_OCxInit(TIM_TypeDef *TIMx,
                                    TIM_OCInitTypeDef *TIM_OCInitStruct,
                                    uint8_t channel);
            // 根据指定的通道号动态配置TIMx外设预加载寄存器
            void static TIM_OCxPreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload, uint8_t channel);

            void init();
            class ChannalType
            {
            public:
                constexpr static const uint8_t channal_1 = 0b0001;
                constexpr static const uint8_t channal_2 = 0b0010;
                constexpr static const uint8_t channal_3 = 0b0100;
                constexpr static const uint8_t channal_4 = 0b1000;
            };
        };
        
        class Universal_timer
        {
        public:
            class TimerType
            {
            public:
                constexpr static const uint8_t timer_2 = 0;
                constexpr static const uint8_t timer_3 = 1;
                constexpr static const uint8_t timer_4 = 2;
            };

        private:
            uint8_t index;
            TIM_TypeDef *BASIC_TIM;

        public:
            Universal_timer(uint8_t timerType, time_ms times);
            Universal_timer(uint8_t timerType, time_s times);
            void NVIC_Config();
            void TIM_Config(uint16_t ms_time);
        };

        class Advanced_timer
        {
        };
    };
} // namespace Device

#endif // _TIMER_H_
