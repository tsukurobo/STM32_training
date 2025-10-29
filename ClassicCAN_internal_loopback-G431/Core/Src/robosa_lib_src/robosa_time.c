#include "robosa_time.h"

#define initCycleCounter() CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

#define resetCycleCounter() DWT->CYCCNT = 0;

#define enableCycleCounter() DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

#define disableCycleCounter() DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;

#define getCycleCounter() DWT->CYCCNT;

float getTime(uint32_t count) {
  float t = (float)count / (float)SystemCoreClock;
  return t;
}

float getTimeUs(uint32_t count) {
  float us = 1000000 * (float)count / (float)SystemCoreClock;
  return us;
}

float getTimeMs(uint32_t count) {
  float ms = 1000 * (float)count / (float)SystemCoreClock;
  return ms;
}

uint32_t get_diff(uint32_t now_cnt, uint32_t pre_cnt) {
  if (now_cnt >= pre_cnt) {
    return now_cnt - pre_cnt;
  } else {
    // オーバーフローした場合
    return (0xFFFFFFFF - pre_cnt) + now_cnt + 1;
  }
}

float getTimebydiff(uint32_t now_cnt, uint32_t pre_cnt) {
  uint32_t cnt = get_diff(now_cnt, pre_cnt);
  return getTime(cnt);
}

float getTimeUsbydiff(uint32_t now_cnt, uint32_t pre_cnt) {
  uint32_t cnt = get_diff(now_cnt, pre_cnt);
  return getTimeUs(cnt);
}

float getTimeMsbydiff(uint32_t now_cnt, uint32_t pre_cnt) {
  uint32_t cnt = get_diff(now_cnt, pre_cnt);
  return getTimeMs(cnt);
}

void time_init(time_t *time) {
  initCycleCounter();
  enableCycleCounter();
  time->pre_cnt = 0;
}

float time_get_s(time_t *time) {
  uint32_t now_cnt = getCycleCounter();
  float t = getTimebydiff(now_cnt, time->pre_cnt);
  time->pre_cnt = now_cnt;
  return t;
}
float time_get_ms(time_t *time) {
  uint32_t now_cnt = getCycleCounter();
  float t = getTimeMsbydiff(now_cnt, time->pre_cnt);
  time->pre_cnt = now_cnt;
  return t;
}

float time_get_us(time_t *time) {
  uint32_t now_cnt = getCycleCounter();
  float t = getTimeUsbydiff(now_cnt, time->pre_cnt);
  time->pre_cnt = now_cnt;
  return t;
}
