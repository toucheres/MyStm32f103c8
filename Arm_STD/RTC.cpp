#include "Interrupt.h"
#include "System.h"
#include "RTC.h"
// 静态成员初始化
System::Interrupt::RunAble System::rtc_clock::secondCallback = nullptr;
System::Interrupt::RunAble System::rtc_clock::alarmCallback = nullptr;
bool System::rtc_clock::configured = false;
System::rtc_clock::ClockSource System::rtc_clock::clockSource = System::rtc_clock::LSE;

// 月份天数表
const uint8_t daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// 初始化RTC
bool System::rtc_clock::init(ClockSource source)
{
    bool firstConfig = false;

    // 使能PWR和BKP时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    // 使能访问RTC和备份寄存器
    PWR_BackupAccessCmd(ENABLE);

    // 检查备份寄存器中的配置标记
    if (BKP_ReadBackupRegister(BKP_DR1) != 0x5A5A || source != clockSource)
    {
        // 重置备份域
        BKP_DeInit();
        firstConfig = true;

        // 配置RTC时钟源
        switch (source)
        {
        case LSE:
            // 启用LSE（外部32.768kHz晶体）
            RCC_LSEConfig(RCC_LSE_ON);
            // 等待LSE就绪
            while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
            {
            }
            // 选择LSE作为RTC时钟
            RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
            break;

        case LSI:
            // 启用LSI内部振荡器
            RCC_LSICmd(ENABLE);
            // 等待LSI就绪
            while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
            {
            }
            // 选择LSI作为RTC时钟
            RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
            break;

        case HSE:
            // 选择HSE/128作为RTC时钟
            RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);
            break;
        }

        // 使能RTC时钟
        RCC_RTCCLKCmd(ENABLE);

        // 等待RTC寄存器同步
        RTC_WaitForSynchro();
        // 等待RTC寄存器写入完成
        RTC_WaitForLastTask();

        // 设置RTC预分频器以获得1秒的计数
        if (source == LSE)
        {
            // LSE是32.768kHz，需要32767分频得到1Hz
            RTC_SetPrescaler(32767);
        }
        else if (source == LSI)
        {
            // LSI约40kHz，需要39999分频得到1Hz
            RTC_SetPrescaler(39999);
        }
        else
        { // HSE
            // 假设HSE为8MHz，HSE/128约为62.5kHz，需要62499分频得到1Hz
            // 如果HSE不是8MHz，需要相应调整
            RTC_SetPrescaler(62499);
        }

        // 等待设置完成
        RTC_WaitForLastTask();

        // 将配置标记写入备份寄存器
        BKP_WriteBackupRegister(BKP_DR1, 0x5A5A);

        // 保存时钟源
        clockSource = source;
    }
    else
    {
        // RTC已经配置，只需等待同步
        RTC_WaitForSynchro();
        RTC_WaitForLastTask();
    }

    // 配置RTC中断
    // 设置NVIC优先级
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 配置RTC闹钟中断
    NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_Init(&NVIC_InitStructure);

    // 使能外部中断线17（RTCAlarm事件）
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line17;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    RTC_WaitForSynchro();
    RTC_ClearITPendingBit(RTC_IT_SEC);
    RTC_ClearITPendingBit(RTC_IT_ALR);
    RTC_ClearITPendingBit(RTC_IT_OW);
    configured = true;
    return firstConfig;
}

// 设置时间
void System::rtc_clock::setTime(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    // 获取当前RTC计数器值
    DateTime dt = getDateTime();

    // 更新时间
    dt.hours = hours;
    dt.minutes = minutes;
    dt.seconds = seconds;

    // 将日期时间转换为计数器值并设置
    setUnixTime(dateTimeToCounter(dt));
}

// 获取时间
void System::rtc_clock::getTime(uint8_t &hours, uint8_t &minutes, uint8_t &seconds)
{
    DateTime dt = getDateTime();
    hours = dt.hours;
    minutes = dt.minutes;
    seconds = dt.seconds;
}

// 设置日期
void System::rtc_clock::setDate(uint8_t day, uint8_t month, uint16_t year, uint8_t weekday)
{
    DateTime dt = getDateTime();
    dt.day = day;
    dt.month = month;
    dt.year = year;
    dt.weekday = weekday;

    setUnixTime(dateTimeToCounter(dt));
}

// 获取日期
void System::rtc_clock::getDate(uint8_t &day, uint8_t &month, uint16_t &year, uint8_t &weekday)
{
    DateTime dt = getDateTime();
    day = dt.day;
    month = dt.month;
    year = dt.year;
    weekday = dt.weekday;
}

// 设置完整日期时间
void System::rtc_clock::setDateTime(const DateTime &dt)
{
    setUnixTime(dateTimeToCounter(dt));
}

// 获取完整日期时间
System::rtc_clock::DateTime System::rtc_clock::getDateTime()
{
    return counterToDateTime(getUnixTime());
}

// 设置Unix时间戳
void System::rtc_clock::setUnixTime(uint32_t unixTime)
{
    enterConfigMode();
    RTC_SetCounter(unixTime);
    exitConfigMode();
}

// 获取Unix时间戳
uint32_t System::rtc_clock::getUnixTime()
{
    return RTC_GetCounter();
}

// 设置闹钟
void System::rtc_clock::setAlarm(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    // 获取当前日期
    DateTime dt = getDateTime();

    // 设置闹钟时间
    dt.hours = hours;
    dt.minutes = minutes;
    dt.seconds = seconds;

    // 检查是否已过今天的设定时间，如果是，将闹钟设为明天
    DateTime current = getDateTime();
    if (current.hours > hours ||
        (current.hours == hours && current.minutes > minutes) ||
        (current.hours == hours && current.minutes == minutes && current.seconds >= seconds))
    {
        // 增加一天
        dt.day++;
        // 检查月末
        if (dt.day > getDaysInMonth(dt.month, dt.year))
        {
            dt.day = 1;
            dt.month++;
            // 检查年末
            if (dt.month > 12)
            {
                dt.month = 1;
                dt.year++;
            }
        }
    }

    // 设置闹钟
    uint32_t alarmValue = dateTimeToCounter(dt);
    enterConfigMode();
    RTC_SetAlarm(alarmValue);
    exitConfigMode();
}

// 获取闹钟设置
void System::rtc_clock::getAlarm(uint8_t &hours, uint8_t &minutes, uint8_t &seconds)
{
    // 直接从RTC闹钟寄存器读取值
    uint32_t alarmh = RTC->ALRH & 0xFFFF;
    uint32_t alarml = RTC->ALRL & 0xFFFF;
    uint32_t alarmValue = (alarmh << 16) | alarml;

    DateTime dt = counterToDateTime(alarmValue);
    hours = dt.hours;
    minutes = dt.minutes;
    seconds = dt.seconds;
}

// 启用或禁用闹钟
void System::rtc_clock::enableAlarm(bool enable)
{
    if (enable)
    {
        // 使能RTC闹钟中断
        RTC_ITConfig(RTC_IT_ALR, ENABLE);
        // 注册闹钟中断处理函数
        System::Interrupt::registerHandler(System::Interrupt::RTCAlarm_IRQHand,
                                           [](void *)
                                           {
                                               if (alarmCallback)
                                                   alarmCallback();
                                               EXTI_ClearITPendingBit(EXTI_Line17);
                                           });
    }
    else
    {
        RTC_ITConfig(RTC_IT_ALR, DISABLE);
    }
}

// 检查闹钟是否启用
bool System::rtc_clock::isAlarmEnabled()
{
    return (RTC->CRH & RTC_IT_ALR) != 0;
}

// 检查闹钟是否触发
bool System::rtc_clock::isAlarmTriggered()
{
    return RTC_GetFlagStatus(RTC_FLAG_ALR) != RESET;
}

// 清除闹钟标志
void System::rtc_clock::clearAlarmFlag()
{
    RTC_ClearFlag(RTC_FLAG_ALR);
}

// 设置秒中断回调
void System::rtc_clock::setSecondCallback(void (*callback)(void *), void *arg)
{
    secondCallback = System::Interrupt::RunAble(callback, arg);
}

// 设置闹钟中断回调
void System::rtc_clock::setAlarmCallback(void (*callback)(void *), void *arg)
{
    alarmCallback = System::Interrupt::RunAble(callback, arg);
}

// 启用秒中断
void System::rtc_clock::enableSecondInterrupt(bool enable)
{
  // if (enable)
  // {
  //     // 使能RTC秒中断
  //     RTC_ITConfig(RTC_IT_SEC, ENABLE);
  //     // 注册秒中断处理函数
  //     System::Interrupt::registerHandler(System::Interrupt::RTC_IRQHand,
  //                                        [](void *)
  //                                        {
  //                                            if (RTC_GetITStatus(RTC_IT_SEC)
  //                                            != RESET)
  //                                            {
  //                                                if (secondCallback)
  //                                                    secondCallback();
  //                                                RTC_ClearITPendingBit(RTC_IT_SEC);
  //                                            }
  //                                        });
  // }
  // else
  // {
  //     RTC_ITConfig(RTC_IT_SEC, DISABLE);
  // }
  if (enable)
  {
      // 先清除可能存在的秒中断标志位
      RTC_ClearITPendingBit(RTC_IT_SEC);

      // 先注册中断处理函数，再使能中断
      System::Interrupt::registerHandler(System::Interrupt::RTC_IRQHand,
                                         [](void *)
                                         {
                                             if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
                                             {
                                                 if (secondCallback)
                                                     secondCallback();
                                                 RTC_ClearITPendingBit(RTC_IT_SEC);
                                             }
                                         });

      // 暂停一小段时间确保注册完成
      for (volatile int i = 0; i < 1000; i++)
          ;

      // 最后使能RTC秒中断
      RTC_ITConfig(RTC_IT_SEC, ENABLE);
  }
  else
  {
      RTC_ITConfig(RTC_IT_SEC, DISABLE);
  }
}

// 辅助函数 - 将日期时间转换为计数器值
uint32_t System::rtc_clock::dateTimeToCounter(const DateTime &dt)
{
    // 基准时间：1970年1月1日
    uint32_t seconds = 0;

    // 计算年份贡献的秒数
    for (uint16_t y = 1970; y < dt.year; y++)
    {
        seconds += isLeapYear(y) ? 31622400 : 31536000;
    }

    // 计算月份贡献的秒数
    for (uint8_t m = 1; m < dt.month; m++)
    {
        seconds += getDaysInMonth(m, dt.year) * 86400;
    }

    // 计算日期贡献的秒数
    seconds += (dt.day - 1) * 86400;

    // 计算时间贡献的秒数
    seconds += dt.hours * 3600;
    seconds += dt.minutes * 60;
    seconds += dt.seconds;

    return seconds;
}

// 辅助函数 - 将计数器值转换为日期时间
System::rtc_clock::DateTime System::rtc_clock::counterToDateTime(uint32_t counter)
{
    DateTime dt;
    uint32_t seconds = counter;

    // 计算年份
    dt.year = 1970;
    while (seconds >= (isLeapYear(dt.year) ? 31622400 : 31536000))
    {
        seconds -= isLeapYear(dt.year) ? 31622400 : 31536000;
        dt.year++;
    }

    // 计算月份
    dt.month = 1;
    while (seconds >= getDaysInMonth(dt.month, dt.year) * 86400)
    {
        seconds -= getDaysInMonth(dt.month, dt.year) * 86400;
        dt.month++;
    }

    // 计算日
    dt.day = seconds / 86400 + 1;
    seconds %= 86400;

    // 计算时
    dt.hours = seconds / 3600;
    seconds %= 3600;

    // 计算分
    dt.minutes = seconds / 60;

    // 计算秒
    dt.seconds = seconds % 60;

    // 计算星期
    // 1970年1月1日是周四
    uint32_t totalDays = counter / 86400;
    dt.weekday = (totalDays + 4) % 7;
    if (dt.weekday == 0)
        dt.weekday = 7; // 调整为1-7，其中1代表周一

    return dt;
}

// 辅助函数 - 检查是否为闰年
bool System::rtc_clock::isLeapYear(uint16_t year)
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// 辅助函数 - 获取指定月份的天数
uint8_t System::rtc_clock::getDaysInMonth(uint8_t month, uint16_t year)
{
    if (month == 2 && isLeapYear(year))
        return 29;
    else
        return daysInMonth[month];
}

// 辅助函数 - 获取指定年份的天数
uint16_t System::rtc_clock::getDaysInYear(uint16_t year)
{
    return isLeapYear(year) ? 366 : 365;
}

// 辅助函数 - 进入配置模式
void System::rtc_clock::enterConfigMode()
{
    RTC_EnterConfigMode();
}

// 辅助函数 - 退出配置模式
void System::rtc_clock::exitConfigMode()
{
    RTC_ExitConfigMode();
}

// 辅助函数 - 等待同步
void System::rtc_clock::waitForSynchro()
{
    RTC_WaitForSynchro();
}

// 辅助函数 - 等待上次操作完成
void System::rtc_clock::waitForLastOperation()
{
    RTC_WaitForLastTask();
}

// 辅助函数 - 检查RTC是否已配置
bool System::rtc_clock::isConfigured()
{
    return configured;
}