#include <stdio.h>
#include "cleint.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"

#include "nvs_flash.h"
#include "wifi.h"
#include "led.h"

#define LED_GPIO GPIO_NUM_2
// #define LED_GPIO 2
//

void temp(void *pvParamenters) {
    rgb_t color;

    while (1) {
        color = (rgb_t){255, 0, 0};   // red
        // xQueueSend(color_queue, &color, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000));

        color = (rgb_t){0, 255, 0};   // green
        // xQueueSend(color_queue, &color, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000));

        color = (rgb_t){0, 0, 255};   // blue
        // xQueueSend(color_queue, &color, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    configure_led(8);

    // xTaskCreate(temp, "led_task", 2048, NULL, 5, NULL);

    // rgb g = {0,255,0};
    rgb_t color = {0, (255 * 80) / 255, (100 * 80) / 255};
        led_set(true, color);
    // gpio_config_t io_conf = {
    //     .pin_bit_mask = 1ULL << LED_GPIO,
    //     .mode = GPIO_MODE_OUTPUT,
    //     .pull_up_en = GPIO_PULLUP_DISABLE,
    //     .pull_down_en = GPIO_PULLDOWN_DISABLE,
    //     .intr_type = GPIO_INTR_DISABLE
    // };
    //
    // gpio_config(&io_conf);
    // for (;;) {
    // gpio_set_level(LED_GPIO, 1);
    //     vTaskDelay(pdMS_TO_TICKS(500));
    // gpio_set_level(LED_GPIO, 0);
    //     vTaskDelay(pdMS_TO_TICKS(500));
    // }
    //
    //
    esp_err_t status = WIFI_FAILURE;


    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    status = connect_wifi();
    if (WIFI_SUCCESS != status) {
        ESP_LOGI("WIFI", "Failed to associate to AP, duing...");
        return;
    }

    status = connect_tcp_server();
    if (TCP_SUCCESS != status) {
        ESP_LOGI("TCP", "Failed to connect to remote server, dying...");
        return;
    }
}
