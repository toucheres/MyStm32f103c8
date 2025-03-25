#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f10x.h"
#include <cstdint>

namespace Device
{
    class ADC
    {
    public:
        class Mode
        {
        public:
            constexpr static const uint8_t non_continuous = 0;
            constexpr static const uint8_t continuous = 1;
            constexpr static const uint8_t non_multichannel = 0;
            constexpr static const uint8_t multichannel = 1;
            constexpr static const uint32_t T1_CC1 = ((uint32_t)0x00000000);             /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t T1_CC2 = ((uint32_t)0x00020000);             /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t T2_CC2 = ((uint32_t)0x00060000);             /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t T3_TRGO = ((uint32_t)0x00080000);            /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t T4_CC4 = ((uint32_t)0x000A0000);             /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t Ext_IT11_TIM8_TRGO = ((uint32_t)0x000C0000); /*!< For ADC1 and ADC2 */
            constexpr static const uint32_t T1_CC3 = ((uint32_t)0x00040000);             /*!< For ADC1, ADC2 and ADC3 */
            constexpr static const uint32_t None = ((uint32_t)0x000E0000);               /*!< For ADC1, ADC2 and ADC3 */
        };
        
        enum Channel
        {
            Channel0 = ADC_Channel_0,   // PA0
            Channel1 = ADC_Channel_1,   // PA1
            Channel2 = ADC_Channel_2,   // PA2
            Channel3 = ADC_Channel_3,   // PA3
            Channel4 = ADC_Channel_4,   // PA4
            Channel5 = ADC_Channel_5,   // PA5
            Channel6 = ADC_Channel_6,   // PA6
            Channel7 = ADC_Channel_7,   // PA7
            Channel8 = ADC_Channel_8,   // PB0
            Channel9 = ADC_Channel_9,   // PB1
            Channel16 = ADC_Channel_16, // 内部温度传感器
            Channel17 = ADC_Channel_17  // 内部参考电压
        };
        
        class ADCType
        {
        public:
            inline static ADC_TypeDef *const adc1 = ADC1;
            inline static ADC_TypeDef *const adc2 = ADC2;
        };
        
        uint8_t iscontinuous;
        uint8_t num_channals;
        ADC_TypeDef *adcType;
        
        ADC(uint8_t iscontinuous, uint8_t num_channals, uint32_t triggerType, ADC_TypeDef *adc);
        
        void addChannal(uint8_t channal);
        uint16_t getChannal(uint8_t channal);
        float convertToTemperature(uint16_t adcValue);
    };
} // namespace Device

#endif // _ADC_H_
