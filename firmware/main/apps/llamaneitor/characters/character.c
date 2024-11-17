#include "character.h"

#include "keyboard_module.h"
#include "llamaneitor_scenes.h"
#include "menus_module.h"
#include "oled_screen.h"
#include "preferences.h"

#define CHARACTER_MEM "character"

static void show_character_desc();
void character_open_profile();
void character_set_current_character(uint8_t character);

//////////////////////////////////// Character Description
//////////////////////////////////////

static character_t* get_current_character() {
  return &character_profiles[preferences_get_ushort(CHARACTER_MEM, 0)];
}

static void profile_input_cb(uint8_t button_name, uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  uint8_t character_idx = preferences_get_ushort(CHARACTER_MEM, 0);
  switch (button_name) {
    case BUTTON_UP:
      character_idx = character_idx ? character_idx - 1 : CHARS_NUM - 1;
      character_set_current_character(character_idx);
      character_open_profile();
      break;
    case BUTTON_DOWN:
      character_idx = ++character_idx > CHARS_NUM - 1 ? 0 : character_idx;
      character_set_current_character(character_idx);
      character_open_profile();
      break;
    case BUTTON_RIGHT:
      show_character_desc();
      break;
    case BUTTON_LEFT:
      llamaneitor_scenes_main_menu();
      break;
    default:
      break;
  }
}

static void show_character_desc() {
  character_t* character = get_current_character();
  static general_menu_t character_desc_menu;
  character_desc_menu.menu_items = character->desc;
  character_desc_menu.menu_count = character->desc_len;
  character_desc_menu.menu_level = GENERAL_TREE_APP_INFORMATION;
  general_register_scrolling_menu(&character_desc_menu);
  general_screen_display_scrolling_text_handler(character_open_profile);
}

void character_open_profile() {
  character_t* character = get_current_character();
  menus_module_set_app_state(true, profile_input_cb);
  uint8_t x = strlen(character->name) * 8 / 2 + 64;
  oled_screen_clear_buffer();
  oled_screen_display_text_center(character->name, 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_right_arrow_bmp, x, 0, 8, 8,
                             OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_up_arrow_bmp, 20, 14, 8, 8,
                             OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_down_arrow_bmp, 20, 22, 8, 8,
                             OLED_DISPLAY_NORMAL);
  x = 64 - character->bitmap.width / 2;
  oled_screen_display_bitmap(character->bitmap.bitmap, x, 8,
                             character->bitmap.width, character->bitmap.height,
                             OLED_DISPLAY_NORMAL);
  oled_screen_display_show();
}

void character_set_current_character(uint8_t character) {
  preferences_put_ushort(CHARACTER_MEM, character);
}