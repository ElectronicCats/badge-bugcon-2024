#pragma once

#include <stdbool.h>
#include <stdio.h>

#define MISSION_ONE_PATAGON_BEACON 41
#define MISSION_ONE_PATAGON        24
#define MISSION_ONE_PATAGON_HW     66
#define MISSION_ONE_PATAGON_FINISH 49

#define MISION1_COUNT    29
#define MISION1_PREAMBLE 50
#define MISION1_PATAGON  42
#define MISION2_COUNT    23

typedef enum {
  MISION_1,
  MISION_2,
  // MISION_3,
  MISION_COUNT
} mision_t;

char* list_mision[MISION_COUNT] = {
    "Sin encontrar", "Sin encontrar",
    // "Sin encontrar",
};

char* mission_one_patagon_beacon[MISSION_ONE_PATAGON_BEACON] = {
    "... El badge",   "detecta algo...",    "             ",
    "             ",  "El espacio",         "es un lugar",
    "donde la",       "tecnologia",         "es la unica",
    "forma de",       "sobrevivir",         "             ",
    "             ",  "- El equipo de",     "ingenieros",
    "necesita ayuda", "para arreglar",      "el transbordador",
    "espacial",       "             ",      "             ",
    "Maldita sea!",   "- piensas -",        "No puede ser",
    "todo tan",       "complicado, apenas", "comenzamos y ya",
    "parece un",      "obstaculo",          "insalvable",
    "             ",  "             ",      "Ya en voz alta:",
    "- No hay otra",  "forma de ayudar",    "a los patagon,",
    "necesito un ",   "cautin, urgente!",   "             ",
    "             ",  "- NUEVA MISION -",
};

char* mission_one_patagon[MISSION_ONE_PATAGON] = {
    "No es posible",     "conseguir que",    "se desarrrolle",
    "el combustible",    "ekologico para",   "los",
    "transbordadores",   "en el espacio",    "si no",
    "conseguimos",       "arreglar este",    "tema el problema",
    "no parece ser",     "demasiado grave,", "solo retrasara el",
    "lanzamiento. Pero", "vas a necesitar",  "herramientas",
    "     ...     ",     "             ",    "puedes ayudarlos",
    "buscando algo",     "con los amigos?",  "             ",
};

char* mission_one_patagon_hw[MISSION_ONE_PATAGON_HW] = {"Llegaste a la",
                                                        "villa de",
                                                        "Hardware",
                                                        "             ",
                                                        "             ",
                                                        "Saludas a la",
                                                        "jefa de taller",
                                                        "y le preguntas",
                                                        "si puedes",
                                                        "usar el",
                                                        "cautin ...",
                                                        "             ",
                                                        "- El equipo de",
                                                        "labotorio no se",
                                                        "presta... ",
                                                        "- comenta la",
                                                        "jefa de taller.",
                                                        "             ",
                                                        "             ",
                                                        "Maldita sea!",
                                                        "- piensas -",
                                                        "No puede ser",
                                                        "todo tan",
                                                        "complicado,",
                                                        "apenas",
                                                        "comenzamos y",
                                                        "ya parece un",
                                                        "obstaculo",
                                                        "insalvable",
                                                        "             ",
                                                        "             ",
                                                        "Ya en voz alta:",
                                                        "- No hay otra",
                                                        "forma de ayudar",
                                                        "a los patagon,",
                                                        "necesito un ",
                                                        "cautin, urgente!",
                                                        "             ",
                                                        "             ",
                                                        "La jefa de",
                                                        "taller te mira",
                                                        "y te dice:",
                                                        "- Entonces",
                                                        "tendras que",
                                                        "hacer algo por",
                                                        "mi primero...",
                                                        "             ",
                                                        "Se cayo la ",
                                                        "caja de",
                                                        "resistencias",
                                                        "y necesito",
                                                        "que las",
                                                        "recojas",
                                                        "             ",
                                                        "             ",
                                                        "- Te pones",
                                                        "manos a la",
                                                        "obra y",
                                                        "recolectas",
                                                        "las resistencias",
                                                        "             ",
                                                        "- Buen trabajo",
                                                        "ahora puedes",
                                                        "usar el cautin",
                                                        "             ",
                                                        "La jefa te da"
                                                        "un codigo para"
                                                        "la matrix..."

};

char* mission_one_patagon_finish[MISSION_ONE_PATAGON_FINISH] = {
    "... Huele a",     "peroxido ...",    "Estan cargando", "los tanques que",
    "se activaran al", "dejar la",        "atmosfera",      "terreste",
    "mientras tu",     "reparas los",     "sistemas de",    "comunicacion",
    "con tu equipo",   "Al final no",     "hay problema",   "que no se",
    "pueda resolver",  "con un poco de",  "ingenio y",      "un cautin",
    "             ",   "             ",   "Impresionaste",  "a los chicos",
    "de Patagon",      "con tu",          "habilidad",      "para resolver",
    "problemas ...",   "             ",   "             ",  "Se te acera",
    "un miembro del",  "equipo y te",     "dice:",          "- Gracias",
    "necesitamos",     "gente como tu",   "en el espacio.", "             ",
    "             ",   "Mision cumplida", "             ",  "Te da un codigo",
    "y te dice:",      "- Este codigo",   "te llevara a",   "la matrix ...",
    "             ",
};

char* mission_1_hardware[MISION1_COUNT] = {
    "No es posible",     "conseguir que",    "se desarrrolle",
    "el combustible",    "ekologico para",   "los",
    "transbordadores",   "en el espacio",    "si no",
    "conseguimos",       "arreglar este",    "tema el problema",
    "no parece ser",     "demasiado grave,", "solo retrasara el",
    "lanzamiento. Pero", "vas a necesitar",  "herramientas",
    "     ...     ",     "             ",    "puedes ayudarlos",
    "buscando algo",     "con los amigos?",  "             ",
    "             ",     "             ",    "             ",
    "Pista: Soldar?",    "Hardware?",
};

// Yes we hack - EC Villages
char* mision_2[MISION2_COUNT] = {"Esto es un reto",
                                 "no? ...",
                                 "Debemos ganar,",
                                 "YES WE HACK!!",
                                 "Que interesante",
                                 "esto de hackear",
                                 "no?",
                                 "Tal vez decirlo",
                                 "nos otorgue",
                                 "poderes",
                                 "o addons",
                                 "             ",
                                 "             ",
                                 "             ",
                                 "             ",
                                 "     Espera!    ",
                                 "Oh los gatos!",
                                 "a los gatos",
                                 "les gustan",
                                 "los addons",
                                 "si tienes",
                                 "uno tal vez"
                                 "les guste",
                                 "verlo"};

void mision_register_cb_exit(void* cb);
void mision_begin();
void mision_enter_code();
void show_mission_screen(uint8_t village_idx);
bool mission_get_state();
void llamaneitor_unlock_cat(uint8_t item_index);