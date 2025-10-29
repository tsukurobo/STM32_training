#ifndef __ROBOSA_ROBOMAS_H__
#define __ROBOSA_ROBOMAS_H__

#include "main.h"

typedef struct{
    FDCAN_HandleTypeDef *hfdcan;
    int16_t current[4];
    int16_t max_current[4];
} robomas_t;

void robomas_init(robomas_t *robomas, FDCAN_HandleTypeDef *hfdcan);
void robomas_put(robomas_t *robomas, uint8_t motor_id, int current);
void robomas_rotate(robomas_t *robomas);

#endif // __ROBOSA_ROBOMAS_H__
