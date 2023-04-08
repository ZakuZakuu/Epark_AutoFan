#include "RTC.h"
#include "rtc.h"
#include "main.h"
#include "oled.h"
#include "stm32f1xx_hal_rtc.h"

void RTC_display()
{
	  /* Get the RTC current Time */
	  HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);
    /* Get the RTC current Date */
    HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);
	
		/* Display date Format : yy/mm/dd */
    printf("%02d/%02d/%02d\r\n",2000 + GetData.Year, GetData.Month, GetData.Date);
		OLED_
    /* Display time Format : hh:mm:ss */
    printf("%02d:%02d:%02d\r\n",GetTime.Hours, GetTime.Minutes, GetTime.Seconds);


}