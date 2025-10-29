#ifndef __ROBOSA_ENCODER_H__
#define __ROBOSA_ENCODER_H__

#include "robosa_time.h"

typedef struct
{
    TIM_HandleTypeDef *htim;
    time_t *time;
    int32_t enc_val;
    float velocity;
} encoder_t;

void encoder_init(encoder_t *encoder, time_t *time, TIM_HandleTypeDef *htim);
void encoder_read(encoder_t *encoder);
float encoder_get_velocity(encoder_t encoder);
int32_t encoder_get_enc_val(encoder_t encoder);

#endif // __ROBOSA_ENCODER_H__
