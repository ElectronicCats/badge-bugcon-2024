#pragma once

#include <stdbool.h>
#include <stdio.h>

#define MMISSION_ONE_PATAGON_BEACON  55
#define MMISSION_ONE_DESCRIPTION     28
#define MMISSION_ONE_PAT_HW_BEACON   68
#define MMISSION_ONE_PATAGON_FINISH  36
#define MMISSION_ONE_FINISHED        1
#define MMISSION_ONE_HARDWARE_BEACON 66
#define MMISSION_ONE_HARDWARE_TASK   5

#define FSAVE_STATE "m_state"
#define FMISSION_1  "mission_1"

typedef enum {
  MISSION_ONE_PAT_IDLE,  // Waiting for a beacon in the patagonspace village
  MISSION_ONE_PAT_SHOW_MISSION,    // Show mission
  MISSION_ONE_PAT_BEACON,          // Mission 1 in the patagonspace village
  MISSION_ONE_PAT_UNLOCK,          // Unlock mission
  MISSION_ONE_PAT_WAIT_HW_BEACON,  // Waiting for a beacon in the hardware
                                   // village
  MISSION_ONE_PAT_ITEM_UNLOCK,     // Unlock item
  MISSION_ONE_PAT_FINISH,          // Finish mission
  MISSION_ONE_PATAGON_COUNT,
  MISSION_ONE_HW_SHOW_MISSION,
  MISSION_ONE_HW_ITEM_UNLOCK,
} mission_one_state_t;

char* mmission_one_patagon_beacon[MMISSION_ONE_PATAGON_BEACON] = {
    "... El badge",
    "detecta algo...",
    "             ",
    "             ",
    "El mundo de",
    "las finanzas",
    "es algo que",
    "no entendemos",
    "pero sabemos",
    "que es",
    "necesario",
    "para que",
    "todo funcione",
    "             ",
    "             ",
    "Entras a la",
    "sala de",
    "reuniones",
    "y ves a los",
    "CyberFiance",
    "trabajando",
    "en un",
    "proyecto ...",
    "             ",
    "             ",
    "Mientras",
    "piensas en",
    "como ayudar",
    "ves un como",
    "unas graficas",
    "empiezan a",
    "cambiar sus",
    "valores ...",
    "             ",
    "Pero ...",
    "De la nada su",
    "computadora",
    "se apaga ...",
    "             ",
    "Desesperados",
    "te piden ayuda",
    "y te dicen:",
    "- Necesitamos",
    "ayuda para",
    "arreglar la",
    "computadora",
    "             ",
    "             ",
    "En tu mente",
    "solo hay una",
    "idea:",
    "- Necesito",
    "ayudarlos!",
    "             ",
    "- NUEVA MISION -",
};

char* mmission_one_description[MMISSION_ONE_DESCRIPTION] = {
    "No es posible",    "seguir el",     "mercado de ",
    "las altas",        "finanzas sin",  "una",
    "computadora",      "que funcione",  "correctamente",
    "     ...     ",    "             ", "Los chicos de",
    "CyberFiance",      "necesitan",     "ayuda",
    "consigue un",      "cautin para",   "arreglar la",
    "computadora",      "     ...     ", "             ",
    "puedes ayudarlos", "buscando algo", "con los amigos?",
    "             ",    "             ", "Pista: Soldar?",
    "Hardware?",
};

char* mmission_one_pat_hardware_beacon[MMISSION_ONE_PAT_HW_BEACON] = {
    "Llegaste a la",   "villa de",         "Hardware",
    "             ",   "             ",    "Saludas a la",
    "jefa de taller",  "y le preguntas",   "si puedes",
    "usar el",         "cautin ...",       "             ",
    "- El equipo de",  "labotorio no se",  "presta... ",
    "- comenta la",    "jefa de taller.",  "             ",
    "             ",   "Maldita sea!",     "- piensas -",
    "No puede ser",    "todo tan",         "complicado, apenas",
    "comenzamos y ya", "parece un",        "obstaculo",
    "insalvable",      "             ",    "             ",
    "Ya en voz alta:", "- No hay otra",    "forma de ayudar",
    "a los patagon,",  "necesito un ",     "cautin, urgente!",
    "             ",   "             ",    "La jefa de",
    "taller te mira",  "y te dice:",       "- Entonces",
    "tendras que",     "hacer algo por",   "mi primero...",
    "             ",   "Se cayo la ",      "caja de",
    "resistencias",    "y necesito",       "que las",
    "recojas",         "             ",    "             ",
    "- Te pones",      "manos a la",       "obra y",
    "recolectas",      "las resistencias", "             ",
    "- Buen trabajo",  "ahora puedes",     "usar el cautin",
    "             ",   "La jefa te da",    "un codigo para",
    "la matrix...",    "             ",
};

char* mmission_one_pat_finish[MMISSION_ONE_PATAGON_FINISH] = {
    "Vez como la",   "computadora",    "vuelve a",      "encenderse",
    "y los chicos",  "de CyberFiance", "te agradecen",  "             ",
    "Las graficas",  "vuelven a",      "funciona",      "y todo",
    "vuelve a la",   "normalidad",     "             ", "Solo el",
    "bitcoin",       "es el que se",   "mantiene",      "inestable",
    "             ", "- Mision",       "cumplida -",    "             ",
    "Los chicos de", "CyberFiance",    "te dan las",    "gracias",
    "y te dicen:",   "- Gracias por",  "ayudarnos",     "             ",
    "Te dan un",     "codigo para",    "la matrix...",  "             ",
};

char* mmission_one_hardware_beacon[MMISSION_ONE_HARDWARE_BEACON] = {
    "... El badge",    "detecta algo...", "             ",
    "             ",   "La comunidad",    "de hardware es",
    "un lugar",        "tranquilo",       "donde las",
    "tecnicas se",     "dejan la vision", "trabajando con",
    "precision",       "milimetra",       "los dise\32os",
    "y probandolos",   "para que",        "funcionen bajo",
    "circunstancias",  "extremas",        "             ",
    "Saludas al",      "equipo de",       "ingenieros",
    "y te dicen:",     "- Hola,",         "necesitamos",
    "ayuda para",      "arreglar el",     "transbordador",
    "espacial",        "             ",   "             ",
    "A lo lejos",      "ves un",          "cautin ...",
    "Te preguntas...", "Pero ellos son",  "ingenieros...",
    "             ",   "El jefe te ve",   "y te dice:",
    "- Se lo que",     "estas pensando",  "pero no es para",
    "nosotros, es",    "para nuestros",   "amigos de",
    "CyberFiance",     "             ",   "             ",
    "En tu mente",     "solo hay una",    "idea:",
    "- Necesito ese",  "cautin!",         "             ",
    "             ",   "El jefe ve en",   "tus ojos la",
    "determinacion",   "y te da un",      "codigo para",
    "la matrix...",    "             ",   "- NUEVA MISION -",
};

char* mmission_one_hardware_task[MMISSION_ONE_HARDWARE_TASK] = {
    "Ayuda a los", "CyberFinance",  "a arreglar su",
    "computadora", "             ",
};

char* mmission_one_finished[MMISSION_ONE_FINISHED] = {"Mision cumplida"};

void mission_one_begin(uint8_t village_idx);
void mission_one_show_mission_done();
void mission_one_show_mission_details(void* exit_cb);
uint8_t mission_one_get_current_state();