#include "toast.h"

#include "badge_connect.h"
#include "badge_pairing.h"
#include "espnow.h"
#include "flame.h"
#include "general_screens.h"
#include "menus_module.h"
#include "nvs_flash.h"
#include "oled_screen.h"
#include "preferences.h"
#include "sounds.h"

void toast_exit();

toast_ctx_t* ctx = NULL;

static void cooldown_task() {
  while (--ctx->cooldown_time) {
    preferences_put_ushort(COOLDOWN_MEM, ctx->cooldown_time);
    // printf("TIME: %d\n", ctx->cooldown_time);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelete(NULL);
}

static void ctx_init() {
  ctx = calloc(1, sizeof(toast_ctx_t));
  ctx->cooldown_time = preferences_get_ushort(COOLDOWN_MEM, 0);
  if (ctx->cooldown_time) {
    xTaskCreate(cooldown_task, "cooldown_task", 2048, NULL, 10, NULL);
  }
}

static void lets_toast() {
  // printf("BRINDIS\n");
  sounds_play_soundtrack(play_volver);
  flame_feed_flame(600);
  ctx->cooldown_time = COOLDOWN_TIME_S;
  xTaskCreate(cooldown_task, "cooldown_task", 2048, NULL, 10, NULL);
  toast_exit();
}

void toast_exit() {
  ctx->waiting = false;
  badge_pairing_set_callbacks(NULL, NULL, NULL);
  badge_pairing_deinit();
}

static void nvs_init() {
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
      ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
}

static void wifi_init() {
  esp_event_loop_create_default();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  nvs_init();

  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
  ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
  ESP_ERROR_CHECK(esp_wifi_start());
}

bool toast_is_ready() {
  return !ctx->cooldown_time && ctx->waiting;
}

void toast_init() {
  if (!ctx->cooldown_time && !ctx->waiting) {
    badge_pairing_begin();
    badge_pairing_set_callbacks(lets_toast, NULL, NULL);  // TODO
    badge_pairing_init();
    badge_pairing_set_any_team();
    ctx->waiting = true;
  }
}

void toast_begin() {
  ctx_init();
  wifi_init();
  badge_connect_init();
  badge_connect_register_recv_cb(ping_handler);
  // badge_connect_set_ekoparty_badge();
  // toast_init();
}