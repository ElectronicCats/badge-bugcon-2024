/**
 * Badge Connect example for BSides, DragonJAR, Ekoparty, and BugCon badges
 * by Francisco Torres, Electronic Cats (https://electroniccats.com/)
 * Date: June 2024
 *
 * This library provides a way to communicate between badges using the ESPNOW
 * protocol.
 *
 * Development environment specifics:
 * IDE: Visual Studio Code + ESP-IDF v5.4-dev-78-gd4cd437ede
 * Hardware Platform:
 * Tested on ESP32-C6, but should work on any ESP32
 *
 * Electronic Cats invests time and resources providing this open source code,
 * please support Electronic Cats and open-source hardware by purchasing
 * products from Electronic Cats!
 *
 * This code is beerware; if you see me (or any other Electronic Cats
 * member) at the local, and you've found our code helpful,
 * please buy us a round!
 * Distributed as-is; no warranty is given.
 */
#include <stdio.h>
#include <string.h>
#include "badge_connect.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

void nvs_init() {
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
      ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
}

void wifi_init() {
  esp_event_loop_create_default();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  nvs_init();

  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
  ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
  ESP_ERROR_CHECK(esp_wifi_start());
}

// Check badge_connect_recv_msg_t struct in badge_connect.h to see what you can
// get from the received message
void receive_data_cb(badge_connect_recv_msg_t* msg) {
  uint8_t* data_int = (uint8_t*) msg->data;
  printf("Received data (uint8_t): %u\n", *data_int);  // 1 means overflow!
  uint16_t* data_int16 = (uint16_t*) msg->data;
  printf("Received data (uint16_t): %u\n", *data_int16);
  uint32_t* data_int32 = (uint32_t*) msg->data;
  printf("Received data (uint32_t): %lu\n", *data_int32);
  printf("Received data size: %d\n", msg->data_size);

  printf("RSSI: %d\n", msg->rx_ctrl->rssi);
  printf("Badge BSides: %s\n", msg->badge_type.is_bsides ? "true" : "false");
  printf("Badge DragonJAR: %s\n",
         msg->badge_type.is_dragonjar ? "true" : "false");
  printf("Badge Ekoparty: %s\n",
         msg->badge_type.is_ekoparty ? "true" : "false");
  printf("Badge BugCON: %s\n", msg->badge_type.is_bugcon ? "true" : "false");
}

void send_int_data() {
  // It can by any size, just be sure to cast it correctly in receive_data_cb,
  // check 8 bits cast issue
  uint32_t data = 1025;
  uint8_t* addr = ESPNOW_ADDR_BROADCAST;  // Send to all badges
  badge_connect_send(addr, &data, sizeof(data));
}

void app_main(void) {
  wifi_init();  // Needed to work with espnow
  badge_connect_init();
  badge_connect_register_recv_cb(receive_data_cb);
  // Set the badge type to BSides, DragonJAR, Ekoparty, or BugCon
  // See README.md or badge_connect.h for more information
  badge_connect_set_bugcon_badge();

  while (true) {
    send_int_data();
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}
