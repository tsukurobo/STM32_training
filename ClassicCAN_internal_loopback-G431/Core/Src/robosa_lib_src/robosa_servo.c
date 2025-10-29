#include "robosa_servo.h"
#include "main.h"

void servo_init(servo_t *servo, TIM_HandleTypeDef *htim, uint32_t channel) {
  servo->htim = htim;
  servo->channel = channel;
  HAL_TIM_PWM_Start(servo->htim, servo->channel);
}

// angle は0 ~ 180
void servo_rotate(servo_t servo, uint8_t angle) {
  if (angle > 180) {
    return;
  }
  uint8_t compare = (uint8_t)(((float)angle / 180.0f) * 100.0f + 25.0f);
  __HAL_TIM_SET_COMPARE(servo.htim, servo.channel, compare);
}
