#ifndef _PWM_H_
#define _PWM_H_

//#include "stm32f10x.h"
#include <cstdint>
#include "Timer.h"

namespace Device
{
    class PWM
    {
    private:
        uint8_t channals;
        uint8_t timer;
        uint16_t frequency;
        Timer::Channal channal_1;
        Timer::Channal channal_2;
        Timer::Channal channal_3;
        Timer::Channal channal_4;

    public:
        PWM(uint8_t timertype, uint8_t channals);
        void start();
        void stop();
        void change(uint8_t channal, uint16_t _frequency, uint8_t _dutyRatio);
        uint32_t getRcc();
    };
} // namespace Device

#endif // _PWM_H_
