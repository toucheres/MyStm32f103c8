#ifndef _OLED_H_
#define _OLED_H_

#include "stm32f10x.h"
#include <cstdint>

namespace Device
{
    class OLED
    {
    public:
        constexpr static const uint8_t OLED_8X16 = 8;
        constexpr static const uint8_t OLED_6X8 = 6;
        /*IsFilled参数数值*/
        constexpr static const uint8_t OLED_UNFILLED = 0;
        constexpr static const uint8_t OLED_FILLED = 1;
        GPIO_TypeDef *SCL_port;
        uint16_t SCL_pin;
        GPIO_TypeDef *SDA_port;
        uint16_t SDA_pin;
        uint8_t DisplayBuf[8][128];

        OLED(GPIO_TypeDef *_SCL_port = GPIOB, uint16_t _SCL_pin = GPIO_Pin_8,
             GPIO_TypeDef *_SDA_port = GPIOB, uint16_t _SDA_pin = GPIO_Pin_9);

        void W_SCL(uint8_t BitValue);
        void W_SDA(uint8_t BitValue);
        uint32_t GPIOX_to_RCC(GPIO_TypeDef *GPIOX);
        void OLED_GPIO_Init(void);
        void I2C_Start(void);
        void I2C_Stop(void);
        void I2C_SendByte(uint8_t Byte);
        void WriteCommand(uint8_t Command);
        void WriteData(uint8_t *Data, uint8_t Count);
        void Init(void);
        void SetCursor(uint8_t Page, uint8_t X);
        uint32_t Pow(uint32_t X, uint32_t Y);
        uint8_t pnpoly(uint8_t nvert, int16_t *vertx, int16_t *verty, int16_t testx, int16_t testy);
        uint8_t IsInAngle(int16_t X, int16_t Y, int16_t StartAngle, int16_t EndAngle);
        void Update(void);
        void UpdateArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
        void Clear(void);
        void ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
        void Reverse(void);
        void ReverseArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
        void ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize);
        void ShowString(int16_t X, int16_t Y, const char *String, uint8_t FontSize);
        void ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
        void ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
        void ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
        void ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
        void ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
        void ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
        void Printf(int16_t X, int16_t Y, uint8_t FontSize, const char *format, ...);
        void DrawPoint(int16_t X, int16_t Y);
        uint8_t GetPoint(int16_t X, int16_t Y);
        void DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1);
        void DrawRectangle(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
        void DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled);
        void DrawCircle(int16_t X, int16_t Y, uint8_t Radius, uint8_t IsFilled);
        void DrawEllipse(int16_t X, int16_t Y, uint8_t A, uint8_t B, uint8_t IsFilled);
        void DrawArc(int16_t X, int16_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);
    };
} // namespace Device

#endif // _OLED_H_
