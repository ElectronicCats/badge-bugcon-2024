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

typedef struct {
  char name[50];
  uint8_t age;
  uint16_t height;
  uint16_t weight;
} player_t;

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

void receive_data_cb(badge_connect_recv_msg_t* msg) {
  player_t* player = (player_t*) msg->data;
  printf("Player name: %s\n", player->name);
  printf("Player age: %d\n", player->age);
  printf("Player height: %d\n", player->height);
  printf("Player weight: %d\n", player->weight);

  printf("RSSI: %d\n", msg->rx_ctrl->rssi);
  printf("Badge BSides: %s\n", msg->badge_type.is_bsides ? "true" : "false");
  printf("Badge DragonJAR: %s\n",
         msg->badge_type.is_dragonjar ? "true" : "false");
  printf("Badge Ekoparty: %s\n",
         msg->badge_type.is_ekoparty ? "true" : "false");
  printf("Badge BugCON: %s\n", msg->badge_type.is_bugcon ? "true" : "false");
}

void send_struct_data() {
  player_t player = {
      .name = "Cayuya",
      .age = 26,
      .height = 150,
      .weight = 50,
  };
  uint8_t* addr = ESPNOW_ADDR_BROADCAST;  // Send to all badges
  badge_connect_send(addr, &player, sizeof(player));
}

void app_main(void) {
  wifi_init();  // Needed to work with espnow
  badge_connect_init();
  badge_connect_register_recv_cb(receive_data_cb);
  // Set the badge type to BSides, DragonJAR, Ekoparty, or BugCon
  // See README.md or badge_connect.h for more information
  badge_connect_set_bsides_badge();

  while (true) {
    send_struct_data();
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}
