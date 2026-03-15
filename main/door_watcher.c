#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"

#include "nvs_flash.h"
#include "wifi.h"

#define LED_GPIO GPIO_NUM_2
// #define LED_GPIO 2

void app_main(void)
{
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
    if (WIFI_SUCESS != status) {
        ESP_LOGI("GG", "Failed to associate to AP, duing...");
        return;
    }
}
