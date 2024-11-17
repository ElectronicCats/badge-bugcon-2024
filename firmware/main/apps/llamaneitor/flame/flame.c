#include "flame.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "oled_screen.h"
#include "preferences.h"
#include "toast.h"

#include "keyboard_module.h"

uint32_t flame_time;

void flame_refresh(uint8_t frame);
void flame_waken_flame(uint16_t seconds);

static void load_flame_time() {
  flame_time = preferences_get_uint(FLAME_TIME_MEM, FLAME_TIME);
}

static void save_flame_time() {
  preferences_put_uint(FLAME_TIME_MEM, flame_time);
}

static void show_toast_scann(uint8_t dots) {
  if (!flame_time) {
    return;
  }
  if (!toast_is_ready()) {
    return;
  }
  oled_screen_display_bitmap(cup_bmp, 0, 8, 24, 24, OLED_DISPLAY_NORMAL);
  for (int i = 0; i < 3; i++) {
    oled_screen_display_text(i < dots ? "." : "", 104 + (i * 8), 1,
                             OLED_DISPLAY_NORMAL);
  }
}

static void show_flame_animation(uint8_t frame) {
  if (flame_time) {
    oled_screen_display_bitmap(flame_bmp_arr[frame], 52, 0, 24, 24,
                               OLED_DISPLAY_NORMAL);
  } else {
    oled_screen_display_bitmap(fathom_bmp_arr[frame], 32, 0, 64, 24,
                               OLED_DISPLAY_NORMAL);
  }
}

static void show_remaining_time() {
  char life_level_str[10];
  uint8_t life_level = flame_time * 100 / FLAME_TIME;
  sprintf(life_level_str, "%d%%", !life_level && flame_time ? 1 : life_level);
  oled_screen_display_text_center(life_level_str, 3, OLED_DISPLAY_NORMAL);
}

static void flame_task() {
  static uint8_t frame = 0;
  load_flame_time();
  while (1) {
    if (!frame) {
      if (flame_time) {
        flame_time--;
        save_flame_time();
      }
    }
    if (llamaneitor_scenes_get_scene() == LLAMANEITOR_FLAME_SCENE) {
      flame_refresh(frame);
    }
    frame = ++frame > 3 ? 0 : frame;
    vTaskDelay(250);
  }
}

static void flame_input_cb(uint8_t button_name, uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  flame_waken_flame(120);
}

void flame_refresh(uint8_t frame) {
  oled_screen_clear_buffer();
  if (flame_time) {
    toast_init();
  }
  show_toast_scann(frame);
  show_remaining_time();
  show_flame_animation(frame);
  oled_screen_display_show();
}

void flame_task_begin() {
  keyboard_module_set_secondary_input_callback(flame_input_cb);
  xTaskCreate(flame_task, "flame_task", 2048, NULL, 10, NULL);
}

void flame_set_flame_time(uint32_t timestamp) {
  // TODO: Obtener el timestamp y callcular el tiempo restante
}

void flame_feed_flame(uint16_t seconds) {
  if (!flame_time) {
    return;
  }
  flame_time += seconds;
  save_flame_time();
}

void flame_waken_flame(uint16_t seconds) {
  if (flame_time > seconds) {
    flame_time -= seconds;
  } else {
    flame_time = 0;
  }
  save_flame_time();
}

uint32_t get_flame_time() {
  return flame_time;
}