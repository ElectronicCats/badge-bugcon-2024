#include <stdio.h>

#include "adv_scan_module.h"
#include "badge_connect.h"
#include "badge_link_module.h"
#include "buzzer.h"
#include "cat_console.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "flash_fs.h"
#include "flash_fs_screens.h"
#include "keyboard_module.h"
#include "menus_module.h"
#include "oled_screen.h"
#include "open_thread.h"
#include "preferences.h"
#include "rgb_ledc_controller.h"
#include "screen_saver.h"
#include "sd_card.h"
#include "web_file_browser.h"
#include "wifi_app.h"

// Define the GPIO pins for the Red, Green, and Blue LEDs
#define GPIO_LED_RED_1   2
#define GPIO_LED_GREEN_1 15
#define GPIO_LED_BLUE_1  3
#define GPIO_LED_RED_2   11
#define GPIO_LED_GREEN_2 10
#define GPIO_LED_BLUE_2  1

// Define colors as RGB values in hexadecimal
#define RED      0x00FFFF  // Red color for common anode (invert the bits)
#define GREEN    0xFF00FF  // Green color for common anode (invert the bits)
#define BLUE     0xFFFF00  // Blue color for common anode (invert the bits)
#define YELLOW   0x0000FF  // Yellow color for common anode (invert the bits)
#define VIOLET   0x11DD11  // Violet color for common anode (invert the bits)
#define NO_COLOR 0xFFFFFF  // No color (all LEDs off)

static const char* TAG = "main";

void app_main() {
#if !defined(CONFIG_MAIN_DEBUG)
  esp_log_level_set(TAG, ESP_LOG_NONE);
#endif
  preferences_begin();
  if (preferences_get_int("dp_select", 0) == 0) {
    preferences_put_int("dp_select", 6);
  }

  // Create an instance of the RGB LED structure and initialize it with the
  // defined GPIO pins and LEDC channels
  rgb_led_t led1 =
      rgb_led_new(GPIO_LED_RED_1, GPIO_LED_GREEN_1, GPIO_LED_BLUE_1,
                  LEDC_CHANNEL_0, LEDC_CHANNEL_1, LEDC_CHANNEL_2);
  rgb_led_t led2 =
      rgb_led_new(GPIO_LED_RED_2, GPIO_LED_GREEN_2, GPIO_LED_BLUE_2,
                  LEDC_CHANNEL_3, LEDC_CHANNEL_4, LEDC_CHANNEL_5);
  //...you can add one more eg: led2.It is limited to 2 leds due to the LEDC
  // module having only 8 channels available.

  // Initialize the RGB LED, check for any errors during the process
  ESP_ERROR_CHECK(rgb_led_init(&led1));
  ESP_ERROR_CHECK(rgb_led_init(&led2));

  for (uint8_t i = 0; i < 3; i++) {
    rgb_led_set_color(&led1, RED);
    rgb_led_set_color(&led2, NO_COLOR);
    vTaskDelay(pdMS_TO_TICKS(200));
    rgb_led_set_color(&led1, NO_COLOR);
    rgb_led_set_color(&led2, BLUE);
    vTaskDelay(pdMS_TO_TICKS(200));
  }
  rgb_led_set_color(&led2, NO_COLOR);

  // flash_fs_begin(flash_fs_screens_handler);
  // sd_card_begin();
  keyboard_module_begin();
  menus_module_begin();
  if (!preferences_get_int("flogin", 0)) {
    screen_saver_stop();
  }

  // adv_scanner_module_begin();
  // Always start the console at the end
  // cat_console_begin();
  // play_artu();
}
