#ifndef __RTC_H
#define __RTC_H
#include "main.h"

RTC_DateTypeDef GetData;  //获取日期结构体

RTC_TimeTypeDef GetTime;   //获取时间结构体

void RTC_display();

#endif