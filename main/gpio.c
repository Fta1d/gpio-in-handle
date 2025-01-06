#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include <esp_log.h>

#define LED_PIN GPIO_NUM_18
#define BUTTON_PIN GPIO_NUM_19
#define GPIO_NUM 2

void configure_gpio(gpio_config_t *config, int gpio_num) {
    for (int i = 0; i < gpio_num; ++i) {
        gpio_config(&config[i]);
    }
}

void app_main(void) {
    int buttonState = 0, prevButtonState = 1;
    bool ledState = 0;

    gpio_config_t config[] = {
        {
            .pin_bit_mask = 1ULL << LED_PIN,
            .mode = GPIO_MODE_OUTPUT
        },
        {
            .pin_bit_mask = 1ULL << BUTTON_PIN,
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_ENABLE
        }
    };

    configure_gpio(config, GPIO_NUM);

    while (1) {
        buttonState = gpio_get_level(BUTTON_PIN);
        ESP_LOGI("gpio", "button state = %d", buttonState);

        if (!buttonState && prevButtonState) {
            ledState = !ledState;
            gpio_set_level(LED_PIN, ledState);

            vTaskDelay(pdMS_TO_TICKS(200));
        }

        prevButtonState = buttonState;

        vTaskDelay(pdMS_TO_TICKS(10));
    }


}
