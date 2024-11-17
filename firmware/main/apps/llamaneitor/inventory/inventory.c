#include "inventory.h"

#include "items.h"
#include "preferences.h"
#include "string.h"

void inventory_load_items() {
  char str[10];
  for (uint8_t i = 0; i < GM_CATS_COUNT; i++) {
    sprintf(str, "item%d", i + 1);
    cat_items[i].unlocked = preferences_get_bool(str, false);
  }
}

void inventory_save_items() {
  char str[10];
  for (uint8_t i = 0; i < GM_CATS_COUNT; i++) {
    sprintf(str, "item%d", i + 1);
    preferences_put_bool(str, cat_items[i].unlocked);
  }
}

void inventory_unlock_item(uint8_t item) {
  cat_items[item].unlocked = true;
  inventory_save_items();
}

void inventory_drop_item(uint8_t item) {
  cat_items[item].unlocked = false;
  inventory_save_items();
}

bool inventory_is_unlocked_item(uint8_t item) {
  return cat_items[item].unlocked;
}