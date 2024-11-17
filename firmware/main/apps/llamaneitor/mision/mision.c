#include "mision.h"
#include "bitmaps_general.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "general/general_screens.h"
#include "general_submenu.h"
#include "inventory.h"
#include "items.h"
#include "llamaneitor.h"
#include "lora_manager.h"
#include "menus_module.h"
#include "mission_one.h"
#include "mission_two.h"
#include "oled_screen.h"
#include "preferences.h"
#include "sounds.h"
#include "villages.h"

#define CODE_LEN         4
#define ITEMOFFSET       1
#define ITEM_PAGE_OFFSET 1

static uint8_t code_gato_1[CODE_LEN] = {1, 3, 3, 7};
static uint8_t code_gato_2[CODE_LEN] = {4, 5, 6, 7};
static uint8_t code_gato_3[CODE_LEN] = {8, 9, 0, 1};
static uint8_t code_cautin[CODE_LEN] = {1, 0, 0, 0};
static uint8_t code_mission_2[CODE_LEN] = {1, 3, 3, 4};
static uint8_t code_mission_2_chiche[CODE_LEN] = {0, 1, 0, 1};
static uint8_t code_selected[CODE_LEN] = {0, 0, 0, 0};

static uint8_t current_mision = 0;
static uint8_t current_mision_idx = 0;
static uint8_t current_x_pos = 0;
static uint8_t current_y_pos = 0;

static bool block_notification = false;
static uint8_t mission_idx = 0;

static void* exit_cb;

static void module_cb_event(uint8_t button_name, uint8_t button_event);
static void module_cb_code_register_event(uint8_t button_name,
                                          uint8_t button_event);
static void module_exit_missions_app();
static void module_display_code_selector();
static void module_validate_code();

static void module_update_mision() {
  char menu_item[16];
  char mission_item[16];

  for (int i = 0; i < MISION_COUNT; i++) {
    sprintf(menu_item, "mission_%d", i + 1);
    uint8_t show_mission = preferences_get_int(menu_item, 0);
    if (show_mission == 1) {
      if (cat_items[i].unlocked == false) {
        sprintf(mission_item, "Mision %d", i + 1);
      } else {
        sprintf(mission_item, "Completa");
      }

      list_mision[i] = malloc(16);
      strcpy(list_mision[i], mission_item);
    }
  }
  general_menu_t mision_menu = {
      .menu_items = list_mision,
      .menu_count = MISION_COUNT,
      .menu_level = GENERAL_TREE_APP_INFORMATION,
  };

  general_register_menu(&mision_menu);
  general_screen_display_menu(current_mision);
}

void show_mission_screen(uint8_t village_idx) {
  mission_idx = village_idx;
  inventory_load_items();

  // Unlock mission 1
  if (village_idx == CYB_FIN || village_idx == HW_HACK) {
    if (cat_items[GM_CAT_1].unlocked == false) {
      mission_one_begin(village_idx);
    }
  } else if (village_idx == YWE_HACK) {
    if (cat_items[GM_CAT_2].unlocked == false) {
      mission_two_begin(village_idx);
    }
  } else if (village_idx == EC) {
    if (cat_items[GM_CAT_2].unlocked == false) {
      mission_two_begin(village_idx);
    }
  } else if (village_idx == BLUE_SPACE) {
    mission_two_unhack_animation();
  } else if (village_idx == THE_BOSS_1 || village_idx == THE_BOSS_2) {
    sounds_play_soundtrack(play_godfather);
  } else if (village_idx == RED_TEAM) {
    uint8_t is_unlocked_mission_two = preferences_get_int(FMISSION_2, 0);
    if (is_unlocked_mission_two == 0) {
      if (cat_items[GM_CAT_2].unlocked == false) {
        mission_two_hacked_begin(village_idx);
      }
    }
  } else if (village_idx == CAR_HACK) {
    uint8_t is_unlocked_mission_one = preferences_get_int(FMISSION_2, 0);
    if (is_unlocked_mission_one == 0) {
      if (cat_items[GM_CAT_2].unlocked == false) {
        mission_two_begin(village_idx);
      }
    }
  } else if (village_idx == CHICHES_ASADO) {
    uint8_t is_unlocked_mission_one = preferences_get_int(FMISSION_2, 0);
    if (is_unlocked_mission_one == 0) {
      if (cat_items[GM_CAT_2].unlocked == false) {
        sounds_play_soundtrack(play_azul);
        mission_two_begin(village_idx);
      }
    }
  }
  block_notification = false;
}

static void llamaneitor_show_need_mission() {
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Te faltan", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("misiones", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

void llamaneitor_unlock_cat(uint8_t item_index) {
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Gato", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Liberado", 40, 3, OLED_DISPLAY_NORMAL);
  oled_screen_display_text(cat_items[item_index].name, 40, 2,
                           OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void llamaneitor_unlock_mission_two() {
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Add-On", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Liberado", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void llamaneitor_unlock_mission_two_asado() {
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Asado", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Liberado", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void llamaneitor_unlock_cautin() {
  oled_screen_fadeout();
  oled_screen_display_bitmap(soldering_iron_bitmap.bitmap, 4, 16,
                             soldering_iron_bitmap.width,
                             soldering_iron_bitmap.height, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(2000));
  oled_screen_clear();
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Cautin", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Liberado", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void llamaneitor_error_trick() {
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("El truco", 40, 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("solo funciona", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("una vez", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void llamaneitor_mission_first() {
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("La mision", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("es primero", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void llamaneitor_unlock_code() {
  oled_screen_clear();
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("A los EC", 40, 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("les gusta", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("de esos", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void module_validate_code() {
  if (current_x_pos != 4) {
    return;
  }
  oled_screen_clear();

  if (memcmp(code_selected, code_gato_1, CODE_LEN) == 0) {
    uint8_t is_unlocked_mission = preferences_get_int("mission_1", 0);
    if (is_unlocked_mission) {
      if (!inventory_is_unlocked_item(GM_CAT_1)) {
        if (inventory_is_unlocked_item(GM_SOLDERING_IRON)) {
          inventory_unlock_item(GM_CAT_1);
          llamaneitor_unlock_cat(GM_CAT_1);
          mission_one_show_mission_done();
          return;
        } else {
          llamaneitor_show_need_mission();
        }
      } else {
        llamaneitor_error_trick();
      }
    } else {
      llamaneitor_mission_first();
    }
  } else if (memcmp(code_selected, code_gato_2, CODE_LEN) == 0) {
    uint8_t is_unlocked_mission = preferences_get_int("mission_2", 0);
    if (is_unlocked_mission) {
      if (!inventory_is_unlocked_item(GM_CAT_2)) {
        inventory_unlock_item(GM_CAT_2);
        llamaneitor_unlock_cat(GM_CAT_2);
      } else {
        llamaneitor_error_trick();
      }
    } else {
      llamaneitor_mission_first();
    }
  } else if (memcmp(code_selected, code_gato_3, CODE_LEN) == 0) {
    uint8_t is_unlocked_mission = preferences_get_int("mission_3", 0);
    if (is_unlocked_mission) {
      if (!inventory_is_unlocked_item(GM_CAT_3)) {
        inventory_unlock_item(GM_CAT_3);
        llamaneitor_unlock_cat(GM_CAT_3);
      } else {
        llamaneitor_error_trick();
      }
    } else {
      llamaneitor_mission_first();
    }
  } else if (memcmp(code_selected, code_cautin, CODE_LEN) == 0) {
    uint8_t is_unlocked_mission = preferences_get_int("mission_1", 0);
    if (is_unlocked_mission) {
      if (!inventory_is_unlocked_item(GM_SOLDERING_IRON)) {
        inventory_unlock_item(GM_SOLDERING_IRON);
        llamaneitor_unlock_cautin();

      } else {
        llamaneitor_error_trick();
      }
    } else {
      llamaneitor_mission_first();
    }
  } else if (memcmp(code_selected, code_mission_2, CODE_LEN) == 0) {
    uint8_t is_unlocked_mission = preferences_get_int("mission_2", 0);
    if (is_unlocked_mission == 1) {
      uint8_t is_unlocked_mission_two =
          preferences_get_int(MISSION_TWO_YWHACK_COMPLETE, 0);
      if (is_unlocked_mission_two == 0) {
        preferences_put_int(MISSION_TWO_YWHACK_COMPLETE, 1);
        llamaneitor_unlock_mission_two();
        llamaneitor_unlock_code();
      } else if (preferences_get_int(MISSION_TWO_EC_COMPLETE, 0) == 0) {
        preferences_put_int(MISSION_TWO_YWHACK_COMPLETE, 1);
        llamaneitor_unlock_mission_two();
        llamaneitor_unlock_code();
      } else {
        llamaneitor_mission_first();
      }
    } else {
      llamaneitor_error_trick();
    }
  } else if (memcmp(code_selected, code_mission_2_chiche, CODE_LEN) == 0) {
    uint8_t is_unlocked_mission = preferences_get_int("mission_2", 0);
    if (is_unlocked_mission == 1) {
      uint8_t is_unlocked_mission_two =
          preferences_get_int(MISSION_TWO_EC_COMPLETE, 0);
      if (is_unlocked_mission_two == 0) {
        preferences_put_int(MISSION_TWO_EC_COMPLETE, 1);
        llamaneitor_unlock_mission_two_asado();
        llamaneitor_unlock_code();
      } else {
        llamaneitor_mission_first();
      }
    } else {
      llamaneitor_error_trick();
    }
  } else {
    oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32,
                               OLED_DISPLAY_NORMAL);
    oled_screen_display_text("Codigo", 40, 1, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("incorrecto", 40, 2, OLED_DISPLAY_NORMAL);
    vTaskDelay(pdMS_TO_TICKS(3000));
    current_x_pos = 0;
    current_y_pos = code_selected[current_x_pos];
    module_display_code_selector();
    return;
  }
  if (exit_cb != NULL) {
    ((void (*)(void)) exit_cb)();
  }
}

static void module_exit_missions_app() {
  current_mision = 0;
  oled_screen_clear();
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Volvere..", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
  menus_module_set_app_state(true, module_cb_event);
  module_update_mision();
}

// Cuando se selecciona una mision
static void mision_selection_handler(uint8_t selection) {
  oled_screen_clear();
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  inventory_load_items();

  switch (selection) {
    case MISION_1:
      if (cat_items[GM_CAT_1].unlocked) {
        mission_one_show_mission_done();
        return;
      }
      oled_screen_display_text("No es un", 40, 0, OLED_DISPLAY_NORMAL);
      oled_screen_display_text("hombre...", 40, 1, OLED_DISPLAY_NORMAL);
      oled_screen_display_text("es una", 40, 2, OLED_DISPLAY_NORMAL);
      oled_screen_display_text("maquina", 40, 3, OLED_DISPLAY_NORMAL);
      vTaskDelay(pdMS_TO_TICKS(1000));
      mission_one_show_mission_details(module_exit_missions_app);
      break;
    case MISION_2:
      oled_screen_display_text("El destino", 40, 1, OLED_DISPLAY_NORMAL);
      oled_screen_display_text("no ha sido", 40, 2, OLED_DISPLAY_NORMAL);
      oled_screen_display_text("escrito", 40, 3, OLED_DISPLAY_NORMAL);
      vTaskDelay(pdMS_TO_TICKS(1000));
      mission_two_show_mission_details(module_exit_missions_app);
      break;
    // case MISION_3:
    //   break;
    default:
      break;
  }
}

static void module_cb_event(uint8_t button_name, uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  switch (button_name) {
    case BUTTON_UP:
      current_mision =
          current_mision > 0 ? current_mision - 1 : (MISION_COUNT - 1);
      module_update_mision();
      break;
    case BUTTON_DOWN:
      current_mision =
          current_mision < (MISION_COUNT - 1) ? current_mision + 1 : 0;
      module_update_mision();
      break;
    case BUTTON_RIGHT:
      mision_selection_handler(current_mision);
      current_mision = 0;
      break;
    case BUTTON_LEFT:
      llamaneitor_scenes_main_menu();
      break;
    default:
      break;
  }
}

static void module_display_code_selector() {
  oled_screen_clear();
  char code[4];
  oled_screen_display_text_center("Ingresa codigo", 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_up_arrow_bmp, 0, 8 * 2, 8, 8,
                             OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_down_arrow_bmp, 0, 8 * 3, 8, 8,
                             OLED_DISPLAY_NORMAL);
  uint8_t x_post_offset = 8;
  for (uint8_t i = 0; i < 4; i++) {
    snprintf(code, 4, "%d", code_selected[i]);
    oled_screen_display_text(
        code, (x_post_offset + 16 * i) + 16, 2,
        (i == current_x_pos) ? OLED_DISPLAY_INVERT : OLED_DISPLAY_NORMAL);
  }
  oled_screen_display_text(
      "OK", 100, 2,
      (current_x_pos == 4) ? OLED_DISPLAY_INVERT : OLED_DISPLAY_NORMAL);
}

static void module_cb_code_register_event(uint8_t button_name,
                                          uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }

  switch (button_name) {
    case BUTTON_UP:
      current_y_pos++;
      if (current_y_pos > 9) {
        current_y_pos = 0;
      }
      code_selected[current_x_pos] = current_y_pos;
      module_display_code_selector();
      break;
    case BUTTON_DOWN:
      current_y_pos--;
      if (current_y_pos == 255) {
        current_y_pos = 9;
      }
      code_selected[current_x_pos] = current_y_pos;
      module_display_code_selector();
      break;
    case BUTTON_RIGHT:
      if (current_x_pos == 4) {
        module_validate_code();
        current_x_pos = 0;
        current_y_pos = code_selected[current_x_pos];
      } else {
        current_x_pos++;
        current_y_pos = code_selected[current_x_pos];
        module_display_code_selector();
      }

      break;
    case BUTTON_LEFT:
      current_x_pos--;
      if (current_x_pos == 255) {
        current_x_pos = 0;
        if (exit_cb != NULL) {
          ((void (*)(void)) exit_cb)();
        }
      } else {
        current_y_pos = code_selected[current_x_pos];
        module_display_code_selector();
      }
      break;
    default:
      break;
  }
}

// static void mision_exit_handler() { menus_module_exit_app(); }

void mision_register_cb_exit(void* cb) {
  exit_cb = cb;
}

void mision_begin() {
  menus_module_set_app_state(true, module_cb_event);
  module_update_mision();
}

bool mission_get_state() {
  return block_notification;
}

void mision_enter_code() {
  menus_module_set_app_state(true, module_cb_code_register_event);
  module_display_code_selector();
}