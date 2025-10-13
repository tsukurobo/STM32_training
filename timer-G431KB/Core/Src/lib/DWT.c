#include "DWT.h"

float getTime(uint32_t count)
{
  float t = (float)count / (float)SystemCoreClock;
  return t;
}

float getTimeUs(uint32_t count)
{
  float us = 1000000 * (float)count / (float)SystemCoreClock;
  return us;
}

float getTimeMs(uint32_t count)
{
  float ms = 1000 * (float)count / (float)SystemCoreClock;
  return ms;
}

float getTimebydiff(uint32_t now_cnt, uint32_t pre_cnt)
{
  uint32_t cnt = now_cnt - pre_cnt;
  return getTime(cnt);
}

float getTimeUsbydiff(uint32_t now_cnt, uint32_t pre_cnt)
{
  uint32_t cnt;
  cnt = now_cnt - pre_cnt;
  return getTimeUs(cnt);
}

float getTimeMsbydiff(uint32_t now_cnt, uint32_t pre_cnt)
{
  uint32_t cnt;
  cnt = now_cnt - pre_cnt;
  return getTimeMs(cnt);
}