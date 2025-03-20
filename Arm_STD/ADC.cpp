#include "MyStm32.h"
Device::ADC::ADC(uint8_t _iscontinuous, uint8_t _num_channals, uint32_t triggerType, ADC_TypeDef *adc)
    : iscontinuous(_iscontinuous), num_channals(_num_channals), adcType(adc)
{

    /*
    1. **开启RCC时钟**：包括ADC和GPIO的时钟。
    2. **配置GPIO**：将GPIO配置为模拟输入模式。
    3. **配置多路开关**：将左边的通道接入到规则组或注入组中。
    4. **配置ADC转换器**：设置ADC的工作模式、数据对齐方式、外部触发方式等。
    5. **启动ADC和DMA**：调用相关函数使能ADC和DMA，开始数据采集和传输。
    */
    GPIO_InitTypeDef GPIO_InitStruct;
    ADC_InitTypeDef ADC_InitStruct;
    ADC_DeInit(adcType); // 将外设 ADC1 的全部寄存器重设为缺省值
    // ADC1;                // APB2PERIPH_BASE + 0x2400
    // ADC2;                // APB2PERIPH_BASE + 0x2800
    // RCC_APB2Periph_ADC1; // 0x00000200
    // RCC_APB2Periph_ADC2; // uint32_t)0x00000400
    auto rcc_adc = reinterpret_cast<uint32_t>(adcType) - APB2PERIPH_BASE - 0x2200;
    RCC_APB2PeriphClockCmd(rcc_adc | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); // 开启RCC时钟

    // 配置ADC时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 6分频，72/6

    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN; // 模拟输入
    // GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;     //	|GPIO_Pin_5
    // GPIO_Init(GPIOA, &GPIO_InitStruct);        // 配置GPIO

    ADC_InitStruct.ADC_ContinuousConvMode = static_cast<FunctionalState>(_iscontinuous); // 持续模式
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;                                  // 向右对齐模式
    ADC_InitStruct.ADC_ExternalTrigConv = triggerType;                                   // 不使用外部触发模式
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;                                      // 独立ADC模式
    ADC_InitStruct.ADC_NbrOfChannel = _num_channals;                                     // 总共N个通道
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;                                           // 使用扫描模式
    ADC_Init(adcType, &ADC_InitStruct);

    // 选择多路通道  ,配置在规则组菜单列表的第一个位置写入通道0，55.5个周期
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5);
    //	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,2,ADC_SampleTime_55Cycles5 );

    // 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）
    //	ADC_DMACmd(ADC1, ENABLE);

    ADC_Cmd(adcType, ENABLE); // 使能指定的ADC1

    // 校准
    ADC_ResetCalibration(adcType);
    while (ADC_GetResetCalibrationStatus(adcType) == SET)
        ;
    ADC_StartCalibration(adcType);
    while (ADC_GetCalibrationStatus(adcType))
        ;
};
void Device::ADC::addChannal(uint8_t channal) {}

uint16_t Device::ADC::getChannal(uint8_t channal)
{
    // 配置ADC转换通道
    ADC_RegularChannelConfig(adcType, channal, 1, ADC_SampleTime_55Cycles5);

    // 开始转换
    ADC_SoftwareStartConvCmd(adcType, ENABLE);

    // 等待转换完成
    while (ADC_GetFlagStatus(adcType, ADC_FLAG_EOC) == RESET)
        ;

    // 获取转换结果
    uint16_t result = ADC_GetConversionValue(adcType);

    // 如果不是连续模式，停止软件转换
    if (!iscontinuous)
    {
        ADC_SoftwareStartConvCmd(adcType, DISABLE);
    }

    return result;
}