#include "header.h"

//tmElements_t tm;

/*
       tm.Hour
       tm.Minute
       tm.Second
       tm.Day
       tm.Month
       tm.Year
       tmYearToCalendar(tm.Year) //usar este para display
*/

void RTC_read()
{
    RTC.read(tm);
}

void RTC_write()
{
    RTC.write(tm);
}

void RTC_updateVar(uint8_t var, uint8_t masmenos) // 1 para sumar 0 para restar
{
    RTC_read();
    
    switch (var)
    {
        case RTC_UP_VAR_hour:
            if (masmenos)
                tm.Hour++;
            else
                tm.Hour--;
            break;
        case RTC_UP_VAR_minute:
            if (masmenos)
                tm.Minute++;
            else
                tm.Minute--;
            break;
        case RTC_UP_VAR_second:
            if (masmenos)
                tm.Second++;
            else
                tm.Second--;
            break;
        case 0:
            
            break;
    }

    RTC_write();
}
