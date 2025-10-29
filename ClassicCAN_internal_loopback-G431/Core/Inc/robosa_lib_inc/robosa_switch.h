#ifndef __ROBOSA_SWITCH_H__
#define __ROBOSA_SWITCH_H__

#include "main.h"
#include <stdbool.h>

typedef struct
{
    bool state;
    uint8_t count;
    uint8_t true_count;
    uint8_t false_count;
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
} switch_t;

void switch_init(switch_t *switch_obj, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void switch_read(switch_t *switch_obj);
bool switch_get(switch_t *switch_obj);

#endif // __ROBOSA_SWITCH_H__
