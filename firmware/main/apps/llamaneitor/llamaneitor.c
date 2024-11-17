#include "llamaneitor.h"
#include "character.h"
#include "esp_log.h"
#include "llamaneitor_scenes.h"
#include "menus_module.h"
#include "modals_module.h"
#include "neopixels_events.h"
#include "oled_screen.h"
#include "preferences.h"
#include "sounds.h"

#define ITEMOFFSET       1
#define ITEM_PAGE_OFFSET 1

static uint16_t current_item = 0;
static bool is_user_selection = false;

static const general_menu_t history_menu = {
    .menu_items = history_menu_items,
    .menu_count = HISTORY_MENU_COUNT,
    .menu_level = GENERAL_TREE_APP_MENU,
};

static const general_menu_t history_cont_menu = {
    .menu_items = history_continue,
    .menu_count = HISTORY_CONT_COUNT,
    .menu_level = GENERAL_TREE_APP_MENU,
};

// static const general_menu_t main_menu_game = {
//     .menu_items = main_menu_items,
//     .menu_count = MENU_GM_COUNT,
//     .menu_level = GENERAL_TREE_APP_SUBMENU,
// };

static game_ctx_t player_ctx = {0};

static general_menu_t current_history = history_menu;

static void module_cb_event(uint8_t button_name, uint8_t button_event);
static void module_cb_event_user_selection(uint8_t button_name,
                                           uint8_t button_event);
static void module_cb_event_character_selection(uint8_t button_name,
                                                uint8_t button_event);
static void module_cb_event_main_menu(uint8_t button_name,
                                      uint8_t button_event);
static void module_display_history();

static void module_follow_white_rabbit();

static void module_reset_app_state() {
  llamaneitor_scenes_main_menu();
}

static void module_display_history() {
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

  uint16_t end_index = current_item + items_per_screen;
  if (end_index > current_history.menu_count) {
    end_index = current_history.menu_count;
  }

  for (uint16_t i = current_item; i < end_index; i++) {
    oled_screen_display_text(current_history.menu_items[i], 3,
                             (i - current_item) + (ITEMOFFSET + screen_title),
                             OLED_DISPLAY_NORMAL);
  }
  oled_screen_display_show();
}

static void module_follow_white_rabbit() {
  for (int i = 0; i < 13; i++) {
    oled_screen_clear();
    uint8_t is_none = i % 2;
    uint8_t x_pos = 8 * i;
    if (x_pos > 128) {
      x_pos = 0;
    }
    if (is_none == 0) {
      oled_screen_display_bitmap(epd_bitmap_white_rabbit.bitmap, x_pos, 0,
                                 epd_bitmap_white_rabbit.width,
                                 epd_bitmap_white_rabbit.height,
                                 OLED_DISPLAY_NORMAL);
    } else {
      oled_screen_display_bitmap(epd_bitmap_white_rabbit.bitmap, x_pos, 8,
                                 epd_bitmap_white_rabbit.width,
                                 epd_bitmap_white_rabbit.height,
                                 OLED_DISPLAY_NORMAL);
    }
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}

static void module_user_option() {
  general_clear_screen();
  oled_screen_clear();
  oled_screen_display_text("Quieres ayudar?", 0, 0, OLED_DISPLAY_NORMAL);
  if (current_item == 0) {
    oled_screen_display_text("> Si", 0, 2, OLED_DISPLAY_INVERT);
    oled_screen_display_text("No", 0, 3, OLED_DISPLAY_NORMAL);
  } else if (current_item == 1) {
    oled_screen_display_text("Si", 0, 2, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("> No", 0, 3, OLED_DISPLAY_INVERT);
  }
}

static void module_display_character_selector() {
  oled_screen_clear_buffer();
  oled_screen_display_text_center("Elige personaje", 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_up_arrow_bmp, 20, 14, 8, 8,
                             OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_down_arrow_bmp, 20, 22, 8, 8,
                             OLED_DISPLAY_NORMAL);
  epd_bitmap_props_t character_bitmap = characters[current_item];
  uint8_t x = 64 - character_bitmap.width / 2;
  oled_screen_display_bitmap(character_bitmap.bitmap, x, 8,
                             character_bitmap.width, character_bitmap.height,
                             OLED_DISPLAY_NORMAL);
  oled_screen_display_show();
}

static void module_cb_event_character_selection(uint8_t button_name,
                                                uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  switch (button_name) {
    case BUTTON_UP:
      current_item = current_item > 0 ? current_item - 1 : (CHARS_NUM - 1);
      module_display_character_selector();
      break;
    case BUTTON_DOWN:
      current_item = current_item < (CHARS_NUM - 1) ? current_item + 1 : 0;
      module_display_character_selector();
      break;
    case BUTTON_RIGHT:
      player_ctx.character_bitmap = characters[current_item];
      character_set_current_character(current_item);
      current_item = 0;
      if (preferences_get_int("flogin", 0) == 0) {
        preferences_put_int("flogin", 1);
      }
      llamaneitor_scenes_main_menu();
      sounds_stop_music();
      break;
    case BUTTON_LEFT:
      break;
    default:
      break;
  }
}

static void module_cb_event_user_selection(uint8_t button_name,
                                           uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  switch (button_name) {
    case BUTTON_UP:
      current_item = current_item > 0 ? current_item - 1 : (2 - 1);
      module_user_option();
      break;
    case BUTTON_DOWN:
      current_item = current_item < (2 - 1) ? current_item + 1 : 0;
      module_user_option();
      break;
    case BUTTON_RIGHT:
      if (current_item == 1) {
        oled_screen_clear();
        oled_screen_display_text("Igual nos vas", 0, 1, OLED_DISPLAY_NORMAL);
        oled_screen_display_text("Ayudar :)", 0, 2, OLED_DISPLAY_NORMAL);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
      }
      current_history = history_cont_menu;
      oled_screen_clear();
      menus_module_set_app_state(true, module_cb_event);
      neopixels_events_set_animation(neopixel_scanning_event);
      current_item = 0;
      is_user_selection = true;
      module_display_history();
      break;
    case BUTTON_LEFT:
      break;
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
      current_item = current_item > 0 ? current_item - 1
                                      : (current_history.menu_count - 1);
      module_display_history();
      break;
    case BUTTON_DOWN:
      current_item = current_item < (current_history.menu_count - 1)
                         ? current_item + 1
                         : 0;
      if (current_item == (current_history.menu_count - 1)) {
        current_item = 0;
        if (is_user_selection) {
          menus_module_set_app_state(true, NULL);
          module_follow_white_rabbit();
          menus_module_set_app_state(true, module_cb_event_character_selection);
          module_display_character_selector();
        } else {
          general_clear_screen();
          menus_module_set_app_state(true, module_cb_event_user_selection);
          module_user_option();
        }
      } else {
        module_display_history();
      }
      break;
    case BUTTON_RIGHT:
      current_item = 0;
      break;
    case BUTTON_LEFT:
      break;
    default:
      break;
  }
}

game_ctx_t* llamaneitor_get_game_ctx() {
  return &player_ctx;
}

void llamaneitor_begin() {
  sounds_play_soundtrack(play_zelda);
  neopixels_events_set_animation(neopixel_llamaneitor_init);
  oled_screen_clear();
  oled_screen_fadeout();
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("INICIANDO", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("  COMMS", 40, 2, OLED_DISPLAY_NORMAL);
  menus_module_set_app_state(true, module_cb_event);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  oled_screen_fadeout();
  module_display_history();
}

void llamaneitor_menu_begin() {
  llamaneitor_scenes_main_menu();
}
