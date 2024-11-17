#include "mission_one.h"
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
#include "oled_screen.h"
#include "preferences.h"
#include "sounds.h"
#include "villages.h"

#define ITEMOFFSET       1
#define ITEM_PAGE_OFFSET 1

static uint8_t scrolling_history_idx = 0;
static general_menu_t current_history;
static mission_one_state_t current_state = MISSION_ONE_PAT_IDLE;

static const general_menu_t m_one_patagon_beacon_menu = {
    .menu_items = mmission_one_patagon_beacon,
    .menu_count = MMISSION_ONE_PATAGON_BEACON,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static const general_menu_t mmission_one_hardware_beacon_menu = {
    .menu_items = mmission_one_hardware_beacon,
    .menu_count = MMISSION_ONE_HARDWARE_BEACON,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static const general_menu_t mmission_one_description_menu = {
    .menu_items = mmission_one_description,
    .menu_count = MMISSION_ONE_DESCRIPTION,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static const general_menu_t mmission_one_pat_hardware_beacon_menu = {
    .menu_items = mmission_one_pat_hardware_beacon,
    .menu_count = MMISSION_ONE_PAT_HW_BEACON,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static const general_menu_t mmission_one_pat_finish_menu = {
    .menu_items = mmission_one_pat_finish,
    .menu_count = MMISSION_ONE_PATAGON_FINISH,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static const general_menu_t mmission_one_finished_menu = {
    .menu_items = mmission_one_finished,
    .menu_count = MMISSION_ONE_FINISHED,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static const general_menu_t mmission_one_hardware_task_menu = {
    .menu_items = mmission_one_hardware_task,
    .menu_count = MMISSION_ONE_HARDWARE_TASK,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static void mission_one_display_scrolling_text();
static void mission_follow_history();

static void module_cb_code_register_event(uint8_t button_name,
                                          uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  switch (button_name) {
    case BUTTON_UP:
      scrolling_history_idx = scrolling_history_idx > 0
                                  ? scrolling_history_idx - 1
                                  : (current_history.menu_count - 1);
      mission_one_display_scrolling_text();
      break;
    case BUTTON_DOWN:
      scrolling_history_idx =
          scrolling_history_idx < (current_history.menu_count - 1)
              ? scrolling_history_idx + 1
              : 0;
      if (scrolling_history_idx == (current_history.menu_count - 1)) {
        mission_follow_history();
      } else {
        mission_one_display_scrolling_text();
      }
      break;
    case BUTTON_RIGHT:
      break;
    case BUTTON_LEFT:
      break;
    default:
      break;
  }
}

static void mission_one_reset_history() {
  scrolling_history_idx = 0;
  menus_module_set_app_state(true, module_cb_code_register_event);
  mission_one_display_scrolling_text();
}

static void show_downloading_bar_mission() {
  oled_screen_clear();
  oled_screen_display_text_center("Descargando", 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_text_center("Mision 1", 1, OLED_DISPLAY_NORMAL);
  for (int i = 0; i < 100; i++) {
    oled_screen_display_loading_bar(i, 3);
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

static void mission_one_display_scrolling_text() {
  uint16_t items_per_screen = 3;
  uint16_t screen_title = 0;
  uint8_t scroll_pos = (4 * 2) + 2;

  general_clear_screen();
  oled_screen_clear_buffer();
  genera_screen_display_card_information_nbc("", "");

  oled_screen_display_bitmap(simple_up_arrow_bmp, (128 - 10), scroll_pos, 8, 8,
                             OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_down_arrow_bmp, (128 - 10), scroll_pos + 8,
                             8, 8, OLED_DISPLAY_NORMAL);

  uint16_t end_index = scrolling_history_idx + items_per_screen;
  if (end_index > current_history.menu_count) {
    end_index = current_history.menu_count;
  }

  for (uint16_t i = scrolling_history_idx; i < end_index; i++) {
    oled_screen_display_text(
        current_history.menu_items[i], 3,
        (i - scrolling_history_idx) + (ITEMOFFSET + screen_title),
        OLED_DISPLAY_NORMAL);
  }
  oled_screen_display_show();
}

static void mission_follow_history() {
  switch (current_state) {
    case MISSION_ONE_PAT_IDLE:
      current_state = MISSION_ONE_PAT_SHOW_MISSION;
      preferences_put_int(FSAVE_STATE, current_state);
      current_history = mmission_one_description_menu;
      show_downloading_bar_mission();
      mission_one_reset_history();
      break;
    case MISSION_ONE_PAT_SHOW_MISSION:
      current_state = MISSION_ONE_PAT_BEACON;
      preferences_put_int(FSAVE_STATE, current_state);
      preferences_put_int(FMISSION_1, 1);
      llamaneitor_scenes_main_menu();
      break;
    case MISSION_ONE_PAT_BEACON:
      current_state = MISSION_ONE_PAT_UNLOCK;
      preferences_put_int(FSAVE_STATE, current_state);
      llamaneitor_scenes_main_menu();
      break;
    case MISSION_ONE_PAT_UNLOCK:
    case MISSION_ONE_PAT_WAIT_HW_BEACON:
      ESP_LOGI("MISSION", "Mission one unlocked");
      llamaneitor_scenes_main_menu();
      break;
    case MISSION_ONE_PAT_ITEM_UNLOCK:
      current_state = MISSION_ONE_PAT_FINISH;
      preferences_put_int(FSAVE_STATE, current_state);
      llamaneitor_scenes_main_menu();
      break;
    case MISSION_ONE_PAT_FINISH:
      llamaneitor_scenes_main_menu();
      break;
    case MISSION_ONE_HW_SHOW_MISSION:
      current_state = MISSION_ONE_HW_ITEM_UNLOCK;
      preferences_put_int(FSAVE_STATE, current_state);
      preferences_put_int(FMISSION_1, 1);
      show_downloading_bar_mission();
      current_history = mmission_one_hardware_task_menu;
      mission_one_reset_history();
      break;
    case MISSION_ONE_HW_ITEM_UNLOCK:
      ESP_LOGI("MISSION", "Mission one unlocked");
      llamaneitor_scenes_main_menu();
      break;
    default:
      break;
  }
}

static void mission_beacon_dissector(uint8_t village_idx) {
  uint8_t mission_one_unlocked = preferences_get_int(FMISSION_1, 0);
  bool is_item_unlocked = cat_items[GM_SOLDERING_IRON].unlocked;
  // First part of the mission
  if (village_idx == CYB_FIN) {
    if (mission_one_unlocked == 0) {
      current_history = m_one_patagon_beacon_menu;
    } else {
      if (is_item_unlocked == true && mission_one_unlocked == 1) {
        current_state = MISSION_ONE_PAT_ITEM_UNLOCK;
        current_history = mmission_one_pat_finish_menu;
      } else {
        return;
      }
    }
  }
  if (village_idx == HW_HACK) {
    if (mission_one_unlocked == 0) {
      current_history = mmission_one_hardware_beacon_menu;
      current_state = MISSION_ONE_HW_SHOW_MISSION;
    } else {
      if (!is_item_unlocked) {
        current_history = mmission_one_pat_hardware_beacon_menu;
      } else {
        return;
      }
    }
  }
  if (current_state == MISSION_ONE_PAT_UNLOCK) {
    return;
  }
  mission_one_reset_history();
}

uint8_t mission_one_get_current_state() {
  return current_state;
}

void mission_one_show_mission_details(void* exit_cb) {
  general_register_scrolling_menu(&mmission_one_description_menu);
  general_screen_display_scrolling_text_handler(exit_cb);
}

void mission_one_show_mission_done() {
  general_register_scrolling_menu(&mmission_one_finished_menu);
  general_screen_display_scrolling_text_handler(llamaneitor_scenes_main_menu);
}

void mission_one_begin(uint8_t village_idx) {
  current_state = preferences_get_int(FSAVE_STATE, MISSION_ONE_PAT_IDLE);
  mission_beacon_dissector(village_idx);
}