#include "robosa_encoder.h"
#include "robosa_time.h"
#include "stm32g4xx_hal_tim.h"
#include <stdint.h>

void encoder_init(encoder_t *encoder, time_t *time, TIM_HandleTypeDef *htim){
    encoder->htim = htim;
    encoder->time = time;
    encoder->enc_val = 0;
    encoder->velocity = 0;
    HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
}

void encoder_read(encoder_t *encoder){
    uint16_t enc_buff = __HAL_TIM_GET_COUNTER(encoder->htim);
    __HAL_TIM_SET_COUNTER(encoder->htim, 0);
    encoder->enc_val += (int16_t)(enc_buff);
    float t = time_get_s(encoder->time);
    if (t == 0) {
        encoder->velocity = 0;
    } else {
        encoder->velocity = (float)(enc_buff) / t;
    }
}

int32_t encoder_get_enc_val(encoder_t encoder){
    return encoder.enc_val;
}

float encoder_get_velocity(encoder_t encoder){
    return encoder.velocity;
}
