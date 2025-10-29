#ifndef __ROBOSA_SERVO_H__
#define __ROBOSA_SERVO_H__
#include "main.h"

typedef struct
{
    TIM_HandleTypeDef *htim;
    uint32_t channel;
} servo_t;

void servo_init(servo_t *servo, TIM_HandleTypeDef *htim, uint32_t channel);
void servo_rotate(servo_t, uint8_t angle);

#endif // __ROBOSA_SERVO_H__
