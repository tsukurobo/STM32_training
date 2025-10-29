#ifndef __ROBOSA_TIME_H__
#define __ROBOSA_TIME_H__

#include "main.h"

typedef struct
{
    uint32_t pre_cnt;
} time_t;

void time_init(time_t *time);
float time_get_s(time_t *time);
float time_get_ms(time_t *time);
float time_get_us(time_t *time);

#endif // __ROBOSA_TIME_H__
