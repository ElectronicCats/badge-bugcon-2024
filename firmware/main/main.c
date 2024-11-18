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
#include "screen_saver.h"
#include "sd_card.h"
#include "web_file_browser.h"
#include "wifi_app.h"

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

  // adv_scanner_module_begin();
  // Always start the console at the end
  // cat_console_begin();
  // play_artu();
}
