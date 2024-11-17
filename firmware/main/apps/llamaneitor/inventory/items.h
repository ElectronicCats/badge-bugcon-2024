#pragma once

#include "llamaneitor.h"

#define CAT1_STR           "Naranjo"
#define CAT2_STR           "Panterita"
#define CAT3_STR           "Pelon"
#define SOLDERING_IRON_STR "Cautin"

typedef enum {
  GM_CAT_1,
  GM_CAT_2,
  GM_CAT_3,
  GM_SOLDERING_IRON,
  GM_CATS_COUNT
} game_items_t;

typedef struct {
  const char* name;
  epd_bitmap_t bitmap;
  char** desc;
  uint8_t desc_len;
  char** hint;
  uint8_t hint_len;
  bool unlocked;
  game_items_t item;
} llamaneitor_item_t;

// 'soldering_iron', 64x24px
const unsigned char epd_bitmap_soldering_iron[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x30, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3c, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0xe3, 0x00,
    0x00, 0x00, 0x00, 0x07, 0xc0, 0x03, 0x01, 0x80, 0x00, 0x00, 0x00, 0x08,
    0x00, 0x1e, 0x00, 0x80, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x78, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x23, 0x03, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x39,
    0x0c, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xf9, 0x78, 0x00, 0x03, 0x80,
    0x00, 0x00, 0x03, 0xf6, 0x80, 0x00, 0x06, 0x00, 0x01, 0x50, 0x0f, 0xc0,
    0x00, 0x00, 0x0c, 0x00, 0x01, 0xf0, 0x1f, 0x00, 0x00, 0x00, 0x08, 0x00,
    0x06, 0x0c, 0x3c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x02, 0x08, 0x00, 0x00,
    0x00, 0x00, 0x08, 0x7f, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0,
    0x02, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// 'kitty_medal', 64x24px
const unsigned char epd_bitmap_kitty_medal[] = {
    0x00, 0x00, 0x01, 0xc0, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe1,
    0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0x4e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x3c, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
    0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x10, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x18,
    0x18, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1c, 0x38, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x3f, 0xfc, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3f,
    0xfc, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x39, 0x9c, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x39, 0x9c, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1f,
    0xf8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x8f, 0xf1, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x87, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
    0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00};

const epd_bitmap_t cat_badge_bitmap = {
    .bitmap = epd_bitmap_kitty_medal,
    .width = 64,
    .height = 24,
};

const epd_bitmap_t soldering_iron_bitmap = {
    .bitmap = epd_bitmap_soldering_iron,
    .width = 64,
    .height = 24,
};

const char* cat1_desc[] = {"Gato " CAT1_STR,  "",
                           "Habilidad:",      "- Maestro del",
                           "hardware",        "",
                           "Este gato te",    "ayudara a ",
                           "reparar y",       "optimizar",
                           "cualquier",       "dispositivo",
                           "tecnologico",     "con un solo",
                           "toque. Tambien",  "incluye la",
                           "habilidad de",    "hablar con",
                           "los componentes", "internos y",
                           "convencerlos",    "de trabajar",
                           "mas rapido,",     "como si fueran",
                           "un equipo de",    "trabajo muy",
                           "motivado.",       "Perfecta para",
                           "salvar el dia",   "antes de una",
                           "presentacion",    "importante!"};

const char* cat1_hint[] = {"No encontrado", "Completa la", "mision #1",
                           "para obtenerlo"};
const char* cat2_desc[] = {"Gato " CAT2_STR,
                           "",
                           "Habilidad:",
                           "- Hacker etico",
                           "",
                           "Este gato tiene",
                           "la capacidad",
                           "de acceder a",
                           "cualquier",
                           "sistema",
                           "con un solo",
                           "clic, pero",
                           "siempre con",
                           "buenas",
                           "intenciones.",
                           "Ademas, puede",
                           "hacer que los",
                           "antivirus se",
                           "pongan",
                           "nerviosos",
                           "y generen",
                           "mensajes de",
                           "Alerta!! El",
                           "hacker",
                           "simpatico",
                           "esta en la",
                           "casa!!",
                           "mientras ayuda",
                           "a fortalecer",
                           "la seguridad",
                           "de las redes."};
const char* cat2_hint[] = {"No encontrado", "Completa la", "mision #2",
                           "para obtenerlo"};
const char* cat3_desc[] = {"Gato " CAT3_STR,  "",
                           "Habilidad:",      "- Explorador",
                           "de villas",       "",
                           "Este gato puede", "navegar por",
                           "todo el evento",  "como si fuera",
                           "un mapa del",     "tesoro. Puede",
                           "descubrir",       "`villas' de",
                           "energia y",       "`misiones' de",
                           "resistencia,",    "y hasta tiene",
                           "un radar para",   "detectar",
                           "componentes que", "necesitan ser",
                           "reemplazados,",   "todo mientras",
                           "canta una",       "cancion de",
                           "aventuras",       "electronicas."};
const char* cat3_hint[] = {"No encontrado", "Completa la", "mision #3",
                           "para obtenerlo"};

const char* s_iron_desc[] = {
    "Cautin",         "Rapido!!!",    "",
    "Necesitan este", "cautin en la", "villa",
    "PatagonSpace,",  "muestraselos", "para compleatar",
    "la mision"};
const char* s_iron_hint[] = {"No encontrado", "Completa", "el reto en la",
                             "villa de",      "Hardware", "para obtenerlo"};

llamaneitor_item_t cat_items[] = {
    {.bitmap = cat_badge_bitmap,
     .name = CAT1_STR,
     .desc = cat1_desc,
     .desc_len = 32,
     .hint = cat1_hint,
     .hint_len = 4,
     .unlocked = false,
     .item = GM_CAT_1},
    {.bitmap = cat_badge_bitmap,
     .name = CAT2_STR,
     .desc = cat2_desc,
     .desc_len = 31,
     .hint = cat2_hint,
     .hint_len = 4,
     .unlocked = false,
     .item = GM_CAT_2},
    {.bitmap = cat_badge_bitmap,
     .name = CAT3_STR,
     .desc = cat3_desc,
     .desc_len = 28,
     .hint = cat3_hint,
     .hint_len = 4,
     .unlocked = false,
     .item = GM_CAT_3},
    {.bitmap = soldering_iron_bitmap,
     .name = SOLDERING_IRON_STR,
     .desc = s_iron_desc,
     .desc_len = 10,
     .hint = s_iron_hint,
     .hint_len = 6,
     .unlocked = false,
     .item = GM_SOLDERING_IRON},
};