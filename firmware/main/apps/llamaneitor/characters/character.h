#pragma once

#include <stdio.h>

#include "bitmaps_general.h"
#include "llamaneitor.h"

#define CHAR1_NAME_STR "Pulga"
#define CHAR2_NAME_STR "Sam"
#define CHAR3_NAME_STR "Llama"
#define CHAR4_NAME_STR "Dragon"

typedef struct {
  const char* name;
  epd_bitmap_props_t bitmap;
  char** desc;
  uint8_t desc_len;
} character_t;

const char* char1_desc[] = {CHAR1_NAME_STR, "", "Habilidad:", "- Ninguna"};
const char* char2_desc[] = {CHAR2_NAME_STR, "", "Habilidad:", "- Ninguna...",
                            "pero en gato"};
const char* char3_desc[] = {CHAR3_NAME_STR, "",
                            "Habilidad:",   "- Puede imitar",
                            "la habilidad", "de Sam"};
const char* char4_desc[] = {
    CHAR4_NAME_STR, "", "Habilidad:", "- Anula la", "habilidad de", "la llama"};

character_t character_profiles[CHARS_NUM] = {
    {.bitmap = epd_bitmap_char1_props,
     .name = CHAR1_NAME_STR,
     .desc = char1_desc,
     .desc_len = 4},
    {.bitmap = epd_bitmap_char2_props,
     .name = CHAR2_NAME_STR,
     .desc = char2_desc,
     .desc_len = 5},
    {.bitmap = epd_bitmap_char3_props,
     .name = CHAR3_NAME_STR,
     .desc = char3_desc,
     .desc_len = 6},
    {.bitmap = epd_bitmap_char4_props,
     .name = CHAR4_NAME_STR,
     .desc = char4_desc,
     .desc_len = 6},
};

void character_open_profile();
void character_set_current_character(uint8_t character);