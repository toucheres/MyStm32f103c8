#ifndef _RTC_H_
#define _RTC_H_

// 在现有rtc_clock类声明中添加以下内容
#include "Interrupt.h"
#include <cstdint>
namespace System
{
    class rtc_clock
    {
    public:
        // 日期时间结构体
        struct DateTime
        {
            uint8_t hours;   // 小时 (0-23)
            uint8_t minutes; // 分钟 (0-59)
            uint8_t seconds; // 秒 (0-59)
            uint8_t day;     // 日 (1-31)
            uint8_t month;   // 月 (1-12)
            uint16_t year;   // 年 (2000-2099)
            uint8_t weekday; // 星期 (1-7, 1=周一)
        };

        // 时钟源枚举
        enum ClockSource
        {
            LSE, // 外部低速晶振 (32.768 kHz)
            LSI, // 内部低速振荡器 (~40 kHz)
            HSE  // 外部高速晶振/128
        };

        // 初始化RTC，如果首次配置或时钟源变更则返回true
        bool init(ClockSource source = LSE);

        // 时间设置与获取
        void setTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
        void getTime(uint8_t &hours, uint8_t &minutes, uint8_t &seconds);

        // 日期设置与获取
        void setDate(uint8_t day, uint8_t month, uint16_t year, uint8_t weekday = 1);
        void getDate(uint8_t &day, uint8_t &month, uint16_t &year, uint8_t &weekday);

        // 复合操作 - 设置/获取完整日期时间
        void setDateTime(const DateTime &dt);
        DateTime getDateTime();

        // Unix时间戳转换 (从1970年1月1日00:00:00 UTC开始的秒数)
        void setUnixTime(uint32_t unixTime);
        uint32_t getUnixTime();

        // 闹钟功能
        void setAlarm(uint8_t hours, uint8_t minutes, uint8_t seconds);
        void getAlarm(uint8_t &hours, uint8_t &minutes, uint8_t &seconds);
        void enableAlarm(bool enable = true);
        bool isAlarmEnabled();
        bool isAlarmTriggered();
        void clearAlarmFlag();


        // 中断回调设置
        void setSecondCallback(void (*callback)(void*),void*arg);
        void setAlarmCallback(void (*callback)(void*),void*arg);
        void enableSecondInterrupt(bool enable = true);

        // 时间格式转换
        static uint32_t dateTimeToCounter(const DateTime &dt);
        static DateTime counterToDateTime(uint32_t counter);

    private:
        // 检查RTC状态
        bool isConfigured();
        void waitForSynchro();
        void waitForLastOperation();
        void enterConfigMode();
        void exitConfigMode();

        // 日历计算辅助函数
        static bool isLeapYear(uint16_t year);
        static uint8_t getDaysInMonth(uint8_t month, uint16_t year);
        static uint16_t getDaysInYear(uint16_t year);

        // 回调函数指针
        static Interrupt::RunAble secondCallback;
        static Interrupt::RunAble alarmCallback;

        // 供内部使用的标志
        static bool configured;
        static ClockSource clockSource;
    };
}
#endif