#include "neopixels_events.h"
#include "esp_log.h"
#include "esp_random.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "neopixels_module.h"

#define MAX_BRIGHTNESS_VALUE 25

static neopixel_animation_ctx_t npx_animation_ctx;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;

uint8_t get_random_uint8() {
  uint32_t entropy = esp_random();
  uint64_t time_since_boot = esp_timer_get_time();
  uint32_t seed = (entropy ^ time_since_boot) & 0xFFFFFFFF;
  srand(seed);

  return rand() % 256;
}

static rgb_color get_random_color() {
  rgb_color color;
  color.r = get_random_uint8() % MAX_BRIGHTNESS_VALUE + 1;
  color.g = get_random_uint8() % MAX_BRIGHTNESS_VALUE + 1;
  color.b = get_random_uint8() % MAX_BRIGHTNESS_VALUE + 1;
  return color;
}

void neopixel_scanning_event() {
  static uint8_t neopixel_idx = 0;
  rgb_color color = get_random_color();
  neopixels_set_pixels(MAX_LED_NUMBER, 0, 0, 0);
  neopixels_set_pixel(neopixel_idx, color.r, color.g, color.b);
  neopixels_refresh();
  neopixel_idx = ++neopixel_idx < MAX_LED_NUMBER ? neopixel_idx : 0;
  vTaskDelay(pdMS_TO_TICKS(200));
}

void neopixel_message_notify() {
  neopixels_set_pixels(MAX_LED_NUMBER, 0, 0, 0);
  neopixels_refresh();
  vTaskDelay(pdMS_TO_TICKS(200));
  neopixels_set_pixels(MAX_LED_NUMBER, 50, 50, 0);
  neopixels_refresh();
  vTaskDelay(pdMS_TO_TICKS(200));
}

void neopixel_llamaneitor_init() {
  static uint8_t neopixel_idx = 0;
  neopixels_set_pixel(neopixel_idx, MAX_BRIGHTNESS_VALUE, MAX_BRIGHTNESS_VALUE,
                      MAX_BRIGHTNESS_VALUE);
  neopixels_refresh();

  vTaskDelay(pdMS_TO_TICKS(50));
  neopixels_set_pixels(MAX_LED_NUMBER, 0, 0, 0);
  neopixels_refresh();
  vTaskDelay(pdMS_TO_TICKS(100));

  neopixel_idx = ++neopixel_idx < MAX_LED_NUMBER ? neopixel_idx : 0;
  vTaskDelay(pdMS_TO_TICKS(200));
}

void neopixel_events_stop_event() {
  npx_animation_ctx.is_running = false;
}

static void npx_task() {
  npx_animation_ctx.is_running = true;
  while (npx_animation_ctx.is_running) {
    npx_animation_ctx.animation();
  }
  neopixels_set_pixels(MAX_LED_NUMBER, 0, 0, 0);
  neopixels_refresh();
  vTaskDelete(NULL);
}

static void npx_task_run() {
  xTaskCreate(npx_task, "effect_function", 2048, NULL, 5, NULL);
}

void neopixels_events_set_animation(neopixel_event event) {
  neopixel_events_stop_event();
  npx_animation_ctx.animation = event;
  npx_task_run();
}

void neopixels_events_set_notification(neopixel_event notification,
                                       uint16_t time_ms) {
  neopixel_event current_animation = npx_animation_ctx.animation;
  neopixels_events_set_animation(notification);
  vTaskDelay(pdMS_TO_TICKS(time_ms));
  neopixels_events_set_animation(current_animation);
}

void neopixel_events_run_event(neopixel_event event) {
  npx_animation_ctx.animation = event;
  xTaskCreate(npx_task, "effect_function", 2048, NULL, 5, NULL);
}

static void v_neopixel_message_notify() {
  for (int i = 0; i < 5; i++) {
    neopixels_set_pixels(MAX_LED_NUMBER, 0, 0, 0);
    neopixels_refresh();
    vTaskDelay(pdMS_TO_TICKS(200));
    neopixels_set_pixels(MAX_LED_NUMBER, 25, 25, 0);
    neopixels_refresh();
    vTaskDelay(pdMS_TO_TICKS(200));
  }
  neopixels_set_pixels(MAX_LED_NUMBER, 0, 0, 0);
  neopixels_refresh();
  vTaskDelete(NULL);
}

void neopixel_volatil_notification() {
  xTaskCreate(v_neopixel_message_notify, "effect_function", 2048, NULL, 5,
              NULL);
}