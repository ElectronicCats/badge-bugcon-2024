#include "villages.h"

#include <string.h>

#include "almanac.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ibeacon_scann.h"
#include "inventory.h"
#include "llamaneitor_scenes.c"
#include "lora_manager.h"
#include "mision.h"
#include "neopixels_events.h"
#include "neopixels_module.h"
#include "preferences.h"
#include "sounds.h"

#define VILLAGE_RSSI_FILTER -70
#define VILLAGES_TIMEOUT_S  10

#define VILLAGE_TAG "VILLAGE"

esp_timer_handle_t villages_timer = NULL;

typedef struct {
  villages_e idx;
  int8_t rssi;
} village_ctx_t;

static village_ctx_t village_ctx = {.idx = EKOPARTY, .rssi = -100};

static void on_villages_timeout() {
  village_ctx.idx = EKOPARTY;
  village_ctx.rssi = -100;
  neopixel_events_stop_event();
}

static void set_village_color() {
  // ESP_LOGI(VILLAGE_TAG, "Village color: %d\n", village_ctx.idx);
  village_t* village = &villages[village_ctx.idx];
  uint8_t red = village->R * 0.5;
  uint8_t green = village->G * 0.5;
  uint8_t blue = village->B * 0.5;
  neopixels_set_pixels(MAX_LED_NUMBER, red, green, blue);
  neopixels_refresh();
  vTaskDelay(pdMS_TO_TICKS(200));
  neopixels_set_pixels(MAX_LED_NUMBER, 0, 0, 0);
  neopixels_refresh();
  vTaskDelay(pdMS_TO_TICKS(500));
}

static void show_village_screen() {
  // if (llamaneitor_scenes_get_scene()) {
  //   return;
  // }
  village_t* village = &villages[village_ctx.idx];
  if (village->idx == CHICHES_ASADO) {
    sounds_play_soundtrack(play_azul);
    flame_feed_flame(120);
    if (almanac_unlock_item(village->idx)) {
      return;
    }
    lora_manager_alert_scrolling(village->name);
  } else if (village->idx > CHICHES_ASADO) {
    flame_waken_flame(30);
    if (almanac_unlock_item(village->idx)) {
      return;
    }
    lora_manager_alert_scrolling(village->name);
  } else {
    flame_feed_flame(120);
    if (almanac_unlock_item(village->idx)) {
      return;
    }
    char str[100];
    sprintf(str, "Has_llegado_a:_%s", village->name);
    lora_manager_alert_scrolling(str);
  }

  show_mission_screen(village->idx);
}

static void on_village_detected() {
  if (!mission_get_state()) {
    show_village_screen();
    // ESP_LOGI("VILLAGE", "Village detected: %d\n", village_ctx.idx);
    neopixels_events_set_animation(set_village_color);
  }
}

static village_t* get_village_by_uuid(esp_ble_ibeacon_t* ibeacon,
                                      esp_ble_gap_cb_param_t* scan_result) {
  for (uint8_t i = 1; i < VILLAGES_COUNT; i++) {
    int8_t rssi = scan_result->scan_rst.rssi;
    if (!memcmp(villages[i].uuid, ibeacon->ibeacon_vendor.proximity_uuid,
                UUID_LEN)) {
      if (rssi > VILLAGE_RSSI_FILTER) {
        return &villages[i];
      }
    }
  }
  return NULL;
}

static void on_ibeacon_cb(esp_ble_ibeacon_t* ibeacon,
                          esp_ble_gap_cb_param_t* scan_result) {
  if (preferences_get_int("flogin", 0) == 0) {
    return;
  }
  village_t* village = get_village_by_uuid(ibeacon, scan_result);
  if (village) {
    esp_timer_stop(villages_timer);
    esp_timer_start_once(villages_timer, VILLAGES_TIMEOUT_S * 1000 * 1000);
    // ESP_LOGI(VILLAGE_TAG, "%s: %d", village->name,
    // scan_result->scan_rst.rssi);
    if (village->idx == village_ctx.idx) {
      village_ctx.rssi = scan_result->scan_rst.rssi;
    } else if (scan_result->scan_rst.rssi > village_ctx.rssi) {
      village_ctx.rssi = scan_result->scan_rst.rssi;
      village_ctx.idx = village->idx;
      on_village_detected(village);
    }
  } else {
    ESP_LOGE(VILLAGE_TAG, "UUID UNRECOGNIZED\n");
  }
}

village_t* villages_get_current_village() {
  return &villages[village_ctx.idx];
}

void villages_begin() {
  ibeacon_scann_set_on_ibeacon_cb(on_ibeacon_cb);
  ibeacon_scann_begin();

  inventory_load_items();
  almanac_load_items();

  esp_timer_create_args_t villages_timer_args = {
      .arg = NULL, .callback = on_villages_timeout};
  esp_timer_create(&villages_timer_args, &villages_timer);
}