#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "led_strip.h"

typedef struct {
    uint8_t r,g,b;
} rgb_t;

// QueueHandle_t color_queue = {0};

void led_set(bool on, rgb_t rgb);

 void configure_led(uint8_t gpio);

#endif /* end of include guard: LED_H */
