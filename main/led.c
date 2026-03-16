#include "led.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>


#include "esp_err.h"
#include "freertos/idf_additions.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include <stdint.h>
#include "sdkconfig.h"


#define BLINK_GPIO CONFIG_BLINK_GPIO

static const char *TAG = "example";

static led_strip_handle_t led_strip;


void led_set(bool on, rgb_t rgb)
{
    /* If the addressable LED is enabled */
    if (on) {

        led_strip_clear(led_strip);
        led_strip_set_pixel(led_strip, 0, rgb.r, rgb.g, rgb.b);
        /* Refresh the strip to send data */
        led_strip_refresh(led_strip);
    } else {
        /* Set all LED off to clear all pixels */
        led_strip_clear(led_strip);
    }
}
void led_clear(led_strip_handle_t led) {
    ESP_ERROR_CHECK(led_strip_clear(led));
}

 void configure_led(uint8_t gpio) {

    // color_queue = xQueueCreate(5, sizeof(rgb_t));

    ESP_LOGI(TAG, "Example configured to blink addressable LED!");

    led_strip_config_t strip_config = {
        // .strip_gpio_num = GPIO_IS_VALID_GPIO(gpio),
        .strip_gpio_num = gpio,
        .max_leds = 1, // at least one LED on board
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false,
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    led_strip_clear(led_strip);
}

// static void display_led(void) {
//     rgb_t color;
//     while (1) {
//         if (xQueueReceive(color_queue, &color, portMAX_DELAY) == pdTRUE) {
//             led_set(true, color);
//         }
//     }
// }
