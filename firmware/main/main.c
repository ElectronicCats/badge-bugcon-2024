#include <stdio.h>

#include "adv_scan_module.h"
#include "badge_connect.h"
#include "badge_link_module.h"
#include "buzzer.h"
#include "cat_console.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "flame.h"
#include "flash_fs.h"
#include "flash_fs_screens.h"
#include "keyboard_module.h"
#include "llamaneitor.h"
#include "lora_manager.h"
#include "menus_module.h"
#include "mission_two.h"
#include "neopixels_events.h"
#include "neopixels_module.h"
#include "oled_screen.h"
#include "open_thread.h"
#include "preferences.h"
#include "screen_saver.h"
#include "sd_card.h"
#include "sounds.h"
#include "toast.h"
#include "web_file_browser.h"
#include "wifi_app.h"

#include "villages.h"

static const char* TAG = "main";

void app_main() {
#if !defined(CONFIG_MAIN_DEBUG)
  esp_log_level_set(TAG, ESP_LOG_NONE);
#endif
  preferences_begin();
  if (preferences_get_int("dp_select", 0) == 0) {
    preferences_put_int("dp_select", 6);
  }
  // flash_fs_begin(flash_fs_screens_handler);
  // sd_card_begin();
  keyboard_module_begin();
  menus_module_begin();
  if (!preferences_get_int("flogin", 0)) {
    screen_saver_stop();
  }
  preferences_put_bool("wifi_connected", false);
  // neopixels_module_begin();
  // neopixels_set_pixels(MAX_LED_NUMBER, 0, 0, 0);
  // neopixels_refresh();

  // villages_begin();
  // lora_module_begin();
  // buzzer_enable();
  // buzzer_begin(11);
  // This to show the history on first boot and until the user completes the
  // history
  // if (!preferences_get_int("flogin", 0)) {
  //   llamaneitor_begin();
  // }
  // toast_begin();
  // flame_task_begin();

  // adv_scanner_module_begin();
  // Always start the console at the end
  // cat_console_begin();
  // play_artu();
}
