#include "almanac.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "general_screens.h"
#include "inventory.h"
#include "items.h"
#include "llamaneitor_scenes.h"
#include "lora_manager.h"
#include "menus_module.h"
#include "mision.h"
#include "oled_screen.h"
#include "preferences.h"
#include "villages.h"

#define VILLAGE_FOUND_STR "Acabas_de_encontrar_la_villa"
#define SEE_ALMANAC_STR   "Consulta_el_almanaque_para_ver_tu_progreso"

static void show_unlocked_village(villages_e village) {
  oled_screen_fadeout();
  char str[100];
  sprintf(str, "%s_%s_%s", VILLAGE_FOUND_STR, villages[village].name,
          SEE_ALMANAC_STR);
  lora_manager_alert_scrolling(str);
}

void almanac_load_items() {
  char str[12];
  for (uint8_t i = 0; i < VILLAGES_COUNT; i++) {
    sprintf(str, "almanac%d", i);
    almanac[i].found = preferences_get_bool(str, i ? false : true);
  }
}

void almanac_save_items() {
  char str[12];
  for (uint8_t i = 0; i < VILLAGES_COUNT; i++) {
    sprintf(str, "almanac%d", i);
    preferences_put_bool(str, almanac[i].found);
  }
}

bool almanac_is_first_completed() {
  if (inventory_is_unlocked_item(GM_CAT_3)) {
    return false;
  }
  uint8_t cnt = 0;
  for (uint8_t i = 0; i < VILLAGES_COUNT; i++) {
    cnt += almanac[i].found;
  }
  if (cnt >= VILLAGES_COUNT) {
    // TODO: Play NGGYU Song
    genera_screen_display_card_information("Completaste", "el almanaque");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    inventory_unlock_item(GM_CAT_3);
    oled_screen_clear();
    llamaneitor_unlock_cat(GM_CAT_3);
    return true;
  }
  return false;
}

bool almanac_unlock_item(villages_e village) {
  if (almanac[village].found) {
    return false;
  }
  almanac[village].found = true;
  almanac_save_items();
  show_unlocked_village(village);
  return true;
}
