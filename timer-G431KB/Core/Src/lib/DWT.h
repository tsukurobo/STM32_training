#ifndef DWT_H
#define DWT_H

#include "main.h"

#define initCycleCounter()	\
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

#define resetCycleCounter()	\
	DWT->CYCCNT = 0;

#define enableCycleCounter() \
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

#define disableCycleCounter() \
	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;

#define getCycleCounter() \
	DWT->CYCCNT;

float getTimebydiff(uint32_t now_cnt, uint32_t pre_cnt);
float getTimeUsbydiff(uint32_t now_cnt, uint32_t pre_cnt);
float getTimeMsbydiff(uint32_t now_cnt, uint32_t pre_cnt);

#endif