#include "robosa_switch.h"
#include <stdbool.h>

#define SWITCH_DEBOUNCE_COUNT 30

void switch_init(switch_t *switch_obj, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
    switch_obj->state = false;
    switch_obj->count = 0;
    switch_obj->true_count = 0;
    switch_obj->false_count = 0;
    switch_obj->GPIOx = GPIOx;
    switch_obj->GPIO_Pin = GPIO_Pin;
}

void switch_read(switch_t *switch_obj) {
  if (switch_obj->true_count > SWITCH_DEBOUNCE_COUNT &&
      switch_obj->state == false) {
    switch_obj->state = true;
  } else if (switch_obj->false_count > SWITCH_DEBOUNCE_COUNT &&
             switch_obj->state == true) {
    switch_obj->state = false;
  }

  if (HAL_GPIO_ReadPin(switch_obj->GPIOx, switch_obj->GPIO_Pin) ==
      GPIO_PIN_SET) {
    switch_obj->true_count += 1;
    switch_obj->false_count = 0;
  } else {
    switch_obj->false_count += 1;
    switch_obj->true_count = 0;
  }
}

bool switch_get(switch_t *switch_obj) { return switch_obj->state; }
