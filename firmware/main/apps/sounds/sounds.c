#include "sounds.h"
#include "buzzer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST     0

static bool is_playing = false;
static pre_sound_event pre_sound = NULL;

#define TEMPO 108

static uint16_t zelda_medoly[] = {
    NOTE_E4, 2, NOTE_G4, 4,  NOTE_D4, 2, NOTE_C4, 8,  NOTE_D4, 8, NOTE_E4, 2,
    NOTE_G4, 4, NOTE_D4, -2, NOTE_E4, 2, NOTE_G4, 4,  NOTE_D5, 2, NOTE_C5, 4,
    NOTE_G4, 2, NOTE_F4, 8,  NOTE_E4, 8, NOTE_D4, -2, NOTE_E4, 2, NOTE_G4, 4,
    NOTE_D4, 2, NOTE_C4, 8,  NOTE_D4, 8, NOTE_E4, 2,  NOTE_G4, 4, NOTE_D4, -2,
    NOTE_E4, 2, NOTE_G4, 4,

    NOTE_D5, 2, NOTE_C5, 4,  NOTE_G4, 2, NOTE_F4, 8,  NOTE_E4, 8, NOTE_F4, 8,
    NOTE_E4, 8, NOTE_C4, 2,  NOTE_F4, 2, NOTE_E4, 8,  NOTE_D4, 8, NOTE_E4, 8,
    NOTE_D4, 8, NOTE_A3, 2,  NOTE_G4, 2, NOTE_F4, 8,  NOTE_E4, 8, NOTE_F4, 8,
    NOTE_E4, 8, NOTE_C4, 4,  NOTE_F4, 4, NOTE_C5, -2,
};
static uint16_t nggyup[] = {
    NOTE_D5,  -4, NOTE_E5,  -4, NOTE_A4,  4,  // 1
    NOTE_E5,  -4, NOTE_FS5, -4, NOTE_A5,  16, NOTE_G5,  16, NOTE_FS5, 8,
    NOTE_D5,  -4, NOTE_E5,  -4, NOTE_A4,  2,  NOTE_A4,  16, NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  8,  NOTE_D5,  16, NOTE_D5,  -4, NOTE_E5,  -4,
    NOTE_A4,  4,  // repeat from 1
    NOTE_E5,  -4, NOTE_FS5, -4, NOTE_A5,  16, NOTE_G5,  16, NOTE_FS5, 8,
    NOTE_D5,  -4, NOTE_E5,  -4, NOTE_A4,  2,  NOTE_A4,  16, NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  8,  NOTE_D5,  16, REST,     4,  NOTE_B4,  8,
    NOTE_CS5, 8,  NOTE_D5,  8,  NOTE_D5,  8,  NOTE_E5,  8,  NOTE_CS5, -8,
    NOTE_B4,  16, NOTE_A4,  2,  REST,     4,

    REST,     8,  NOTE_B4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,
    NOTE_B4,  4,  NOTE_A4,  8,  // 7
    NOTE_A5,  8,  REST,     8,  NOTE_A5,  8,  NOTE_E5,  -4, REST,     4,
    NOTE_B4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,  NOTE_B4,  8,
    NOTE_D5,  8,  NOTE_E5,  8,  REST,     8,  REST,     8,  NOTE_CS5, 8,
    NOTE_B4,  8,  NOTE_A4,  -4, REST,     4,  REST,     8,  NOTE_B4,  8,
    NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,  NOTE_B4,  8,  NOTE_A4,  4,
    NOTE_E5,  8,  NOTE_E5,  8,  NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_E5,  4,
    REST,     4,

    NOTE_D5,  2,  NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_D5,  8,  // 13
    NOTE_E5,  8,  NOTE_E5,  8,  NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_E5,  4,
    NOTE_A4,  4,  REST,     2,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,
    NOTE_B4,  8,  REST,     8,  NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_E5,  -4,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_FS5, -8,
    NOTE_FS5, -8, NOTE_E5,  -4, NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16,
    NOTE_B4,  16,

    NOTE_E5,  -8, NOTE_E5,  -8, NOTE_D5,  -8, NOTE_CS5, 16, NOTE_B4,  -8,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16,  // 18
    NOTE_D5,  4,  NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16, NOTE_A4,  8,
    NOTE_A4,  8,  NOTE_A4,  8,  NOTE_E5,  4,  NOTE_D5,  2,  NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_FS5, -8, NOTE_FS5, -8,
    NOTE_E5,  -4, NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16,
    NOTE_A5,  4,  NOTE_CS5, 8,  NOTE_D5,  -8, NOTE_CS5, 16, NOTE_B4,  8,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16,

    NOTE_D5,  4,  NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16, NOTE_A4,  4,
    NOTE_A4,  8,  // 23
    NOTE_E5,  4,  NOTE_D5,  2,  REST,     4,  REST,     8,  NOTE_B4,  8,
    NOTE_D5,  8,  NOTE_B4,  8,  NOTE_D5,  8,  NOTE_E5,  4,  REST,     8,
    REST,     8,  NOTE_CS5, 8,  NOTE_B4,  8,  NOTE_A4,  -4, REST,     4,
    REST,     8,  NOTE_B4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,
    NOTE_B4,  8,  NOTE_A4,  4,  REST,     8,  NOTE_A5,  8,  NOTE_A5,  8,
    NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_E5,  8,  NOTE_D5,  8,

    REST,     8,  NOTE_A4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,
    NOTE_B4,  8,  // 29
    REST,     8,  NOTE_CS5, 8,  NOTE_B4,  8,  NOTE_A4,  -4, REST,     4,
    NOTE_B4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,  NOTE_B4,  8,
    NOTE_A4,  4,  REST,     8,  REST,     8,  NOTE_E5,  8,  NOTE_E5,  8,
    NOTE_FS5, 4,  NOTE_E5,  -4, NOTE_D5,  2,  NOTE_D5,  8,  NOTE_E5,  8,
    NOTE_FS5, 8,  NOTE_E5,  4,  NOTE_E5,  8,  NOTE_E5,  8,  NOTE_FS5, 8,
    NOTE_E5,  8,  NOTE_A4,  8,  NOTE_A4,  4,

    REST,     -4, NOTE_A4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,
    NOTE_B4,  8,  // 35
    REST,     8,  NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_E5,  -4, NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_FS5, -8, NOTE_FS5, -8,
    NOTE_E5,  -4, NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16,
    NOTE_E5,  -8, NOTE_E5,  -8, NOTE_D5,  -8, NOTE_CS5, 16, NOTE_B4,  8,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_D5,  4,
    NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16, NOTE_A4,  4,  NOTE_A4,  8,

    NOTE_E5,  4,  NOTE_D5,  2,  NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16,
    NOTE_B4,  16,  // 40
    NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5,  -4, NOTE_A4,  16, NOTE_B4,  16,
    NOTE_D5,  16, NOTE_B4,  16, NOTE_A5,  4,  NOTE_CS5, 8,  NOTE_D5,  -8,
    NOTE_CS5, 16, NOTE_B4,  8,  NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16,
    NOTE_B4,  16, NOTE_D5,  4,  NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16,
    NOTE_A4,  4,  NOTE_A4,  8,  NOTE_E5,  4,  NOTE_D5,  2,  NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16,

    NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5,  -4, NOTE_A4,  16, NOTE_B4,  16,
    NOTE_D5,  16, NOTE_B4,  16,  // 45
    NOTE_A5,  4,  NOTE_CS5, 8,  NOTE_D5,  -8, NOTE_CS5, 16, NOTE_B4,  8,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_D5,  4,
    NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16, NOTE_A4,  4,  NOTE_A4,  8,
    NOTE_E5,  4,  NOTE_D5,  2,  NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16,
    NOTE_B4,  16, NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5,  -4, NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16,  // 45

    NOTE_A5,  4,  NOTE_CS5, 8,  NOTE_D5,  -8, NOTE_CS5, 16, NOTE_B4,  8,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_D5,  4,
    NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16, NOTE_A4,  4,  NOTE_A4,  8,

    NOTE_E5,  4,  NOTE_D5,  2,  REST,     4};

static uint16_t godfather[] = {

    REST,     4, REST,     8, REST,    8, REST,     8, NOTE_E4,  8, NOTE_A4, 8,
    NOTE_C5,  8,  // 1
    NOTE_B4,  8, NOTE_A4,  8, NOTE_C5, 8, NOTE_A4,  8, NOTE_B4,  8, NOTE_A4, 8,
    NOTE_F4,  8, NOTE_G4,  8, NOTE_E4, 2, NOTE_E4,  8, NOTE_A4,  8, NOTE_C5, 8,
    NOTE_B4,  8, NOTE_A4,  8, NOTE_C5, 8, NOTE_A4,  8, NOTE_C5,  8, NOTE_A4, 8,
    NOTE_E4,  8, NOTE_DS4, 8,

    NOTE_D4,  2, NOTE_D4,  8, NOTE_F4, 8, NOTE_GS4, 8,  // 5
    NOTE_B4,  2, NOTE_D4,  8, NOTE_F4, 8, NOTE_GS4, 8, NOTE_A4,  2, NOTE_C4, 8,
    NOTE_C4,  8, NOTE_G4,  8, NOTE_F4, 8, NOTE_E4,  8, NOTE_G4,  8, NOTE_F4, 8,
    NOTE_F4,  8, NOTE_E4,  8, NOTE_E4, 8, NOTE_GS4, 8,

    NOTE_A4,  2, REST,     8, NOTE_A4, 8, NOTE_A4,  8, NOTE_GS4, 8,  // 9
    NOTE_G4,  2, NOTE_B4,  8, NOTE_A4, 8, NOTE_F4,  8, NOTE_E4,  2, NOTE_E4, 8,
    NOTE_G4,  8, NOTE_E4,  8, NOTE_D4, 2, NOTE_D4,  8, NOTE_D4,  8, NOTE_F4, 8,
    NOTE_DS4, 8,

    NOTE_E4,  2, REST,     8, NOTE_E4, 8, NOTE_A4,  8, NOTE_C5,  8,  // 13

    NOTE_E4,  2  // 13
};

static uint16_t azul_melody[] = {
    // Intro
    NOTE_C4, 8, NOTE_E4, 8, NOTE_G4, 4, NOTE_A4, 4, NOTE_F4, 8, NOTE_G4, 8,
    NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 8, NOTE_E4, 8, NOTE_D4, 4, NOTE_E4, 4,

    // "Azul..."
    NOTE_A4, 4, NOTE_B4, 4, NOTE_C5, 2, NOTE_A4, 4, NOTE_G4, 4, NOTE_A4, 2,
    NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 2,

    // "Es que este amor es azul como el mar, azul..."
    NOTE_G4, 8, NOTE_F4, 8, NOTE_E4, 4, NOTE_F4, 4, NOTE_D4, 8, NOTE_E4, 8,
    NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 4, NOTE_B4, 4, NOTE_C5, 2,

    // "Como de tu mirar, azul, azul..."
    NOTE_A4, 4, NOTE_B4, 4, NOTE_A4, 2, NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 2,
    NOTE_D4, 4, NOTE_E4, 4, NOTE_F4, 2,

    // Repetir parte
    NOTE_A4, 4, NOTE_B4, 4, NOTE_C5, 2, NOTE_A4, 4, NOTE_G4, 4, NOTE_A4, 2,
    NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 2,

    REST, 4};

static uint16_t volver_melody[] = {
    // "Volver con la frente marchita..."
    NOTE_C4, 4, NOTE_E4, 4, NOTE_G4, 2,  // "Vol-ver"
    NOTE_A4, 4, NOTE_G4, 4, NOTE_E4, 2,  // "con la"
    NOTE_C4, 4, NOTE_E4, 4, NOTE_G4, 4, NOTE_A4, 8, NOTE_G4,
    8,  // "frente mar-chi-ta"

    // "Las nieves del tiempo..."
    NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 2,              // "Las nie-ves"
    NOTE_G4, 8, NOTE_A4, 8, NOTE_G4, 4, NOTE_E4, 4,  // "del tiem-po"
    NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 2,              // "pla-tearon mi sien"

    // "Sentir que es un soplo la vida..."
    NOTE_C5, 4, NOTE_B4, 4, NOTE_A4, 2,  // "Sen-tir"
    NOTE_G4, 4, NOTE_A4, 4, NOTE_B4, 2,  // "que es un"
    NOTE_C5, 4, NOTE_E5, 4, NOTE_F5, 2,  // "soplo la"

    // "Que veinte años no es nada..."
    NOTE_E5, 4, NOTE_C5, 4, NOTE_A4, 2,  // "vi-da"
    NOTE_C5, 4, NOTE_D5, 4, NOTE_E5, 2,  // "que vein-te"

    // "Que febril la mirada..."
    NOTE_F5, 4, NOTE_G5, 4, NOTE_A5, 2,  // "an-ios no es na-da"
    NOTE_F5, 4, NOTE_D5, 4, NOTE_B4, 2,  // "que fe-bril"

    // "La mirada errante..."
    NOTE_C5, 4, NOTE_B4, 4, NOTE_A4, 4, NOTE_G4, 4,  // "la mi-ra-da er-ran-te"

    // "De las sombras que buscan mi fe..."
    NOTE_C5, 4, NOTE_D5, 4, NOTE_E5, 2,  // "de las som-bras"
    NOTE_C5, 4, NOTE_D5, 4, NOTE_C5, 2,  // "que bus-can"
    NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 2,  // "mi fe"

    // "Tengo miedo del encuentro..."
    NOTE_F5, 4, NOTE_G5, 4, NOTE_A5, 2,  // "Ten-go"
    NOTE_G5, 4, NOTE_F5, 4, NOTE_E5, 2,  // "mie-do"
    NOTE_F5, 4, NOTE_G5, 4, NOTE_A5, 2,  // "del en-cuen-tro"
    // Rest to end the phrase
    REST, 4};

static uint16_t imperial_march_melody[] = {

    NOTE_A4,  -4, NOTE_A4, -4, NOTE_A4,  16,  NOTE_A4, 16, NOTE_A4,  16,
    NOTE_A4,  16, NOTE_F4, 8,  REST,     8,   NOTE_A4, -4, NOTE_A4,  -4,
    NOTE_A4,  16, NOTE_A4, 16, NOTE_A4,  16,  NOTE_A4, 16, NOTE_F4,  8,
    REST,     8,  NOTE_A4, 4,  NOTE_A4,  4,   NOTE_A4, 4,  NOTE_F4,  -8,
    NOTE_C5,  16,

    NOTE_A4,  4,  NOTE_F4, -8, NOTE_C5,  16,  NOTE_A4, 2,  // 4
    NOTE_E5,  4,  NOTE_E5, 4,  NOTE_E5,  4,   NOTE_F5, -8, NOTE_C5,  16,
    NOTE_A4,  4,  NOTE_F4, -8, NOTE_C5,  16,  NOTE_A4, 2,

    NOTE_A5,  4,  NOTE_A4, -8, NOTE_A4,  16,  NOTE_A5, 4,  NOTE_GS5, -8,
    NOTE_G5,  16,  // 7
    NOTE_DS5, 16, NOTE_D5, 16, NOTE_DS5, 8,   REST,    8,  NOTE_A4,  8,
    NOTE_DS5, 4,  NOTE_D5, -8, NOTE_CS5, 16,

    NOTE_C5,  16, NOTE_B4, 16, NOTE_C5,  16,  REST,    8,  NOTE_F4,  8,
    NOTE_GS4, 4,  NOTE_F4, -8, NOTE_A4,  -16,  // 9
    NOTE_C5,  4,  NOTE_A4, -8, NOTE_C5,  16,  NOTE_E5, 2,

    NOTE_A5,  4,  NOTE_A4, -8, NOTE_A4,  16,  NOTE_A5, 4,  NOTE_GS5, -8,
    NOTE_G5,  16,  // 7
    NOTE_DS5, 16, NOTE_D5, 16, NOTE_DS5, 8,   REST,    8,  NOTE_A4,  8,
    NOTE_DS5, 4,  NOTE_D5, -8, NOTE_CS5, 16,

    NOTE_C5,  16, NOTE_B4, 16, NOTE_C5,  16,  REST,    8,  NOTE_F4,  8,
    NOTE_GS4, 4,  NOTE_F4, -8, NOTE_A4,  -16,  // 9
    NOTE_A4,  4,  NOTE_F4, -8, NOTE_C5,  16,  NOTE_A4, 2,

};

void play_imperial_march() {
  int notes =
      sizeof(imperial_march_melody) / sizeof(imperial_march_melody[0] / 2);
  int wholenote = (60000 * 4) / 90;
  int divider = 0, noteDuration = 0;
  while (is_playing) {
    for (int i = 0; i < notes * 2; i += 2) {
      if (!is_playing) {
        break;
      }
      divider = imperial_march_melody[i + 1];
      if (divider == 0) {
        vTaskDelay(wholenote / portTICK_PERIOD_MS);
        continue;
      }
      if (divider > 0) {
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;
      }
      if (imperial_march_melody[i] <= 13) {
        continue;
      }
      buzzer_set_freq(imperial_march_melody[i]);
      buzzer_play_for(noteDuration * 0.9);
      vTaskDelay(noteDuration / portTICK_PERIOD_MS);
    }
  }
  is_playing = false;
  vTaskDelete(NULL);
}

void play_azul() {
  int notes = sizeof(azul_melody) / sizeof(azul_melody[0] / 2);
  int wholenote = (60000 * 4) / 114;
  int divider = 0, noteDuration = 0;
  for (int i = 0; i < notes * 2; i += 2) {
    if (!is_playing) {
      break;
    }
    divider = azul_melody[i + 1];
    if (divider == 0) {
      vTaskDelay(wholenote / portTICK_PERIOD_MS);
      continue;
    }
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    if (azul_melody[i] <= 13) {
      continue;
    }
    buzzer_set_freq(azul_melody[i]);
    buzzer_play_for(noteDuration * 0.9);
    vTaskDelay(noteDuration / portTICK_PERIOD_MS);
  }
  is_playing = false;
  vTaskDelete(NULL);
}

void play_volver() {
  int notes = sizeof(volver_melody) / sizeof(volver_melody[0] / 2);
  int wholenote = (60000 * 4) / 114;
  int divider = 0, noteDuration = 0;
  for (int i = 0; i < notes * 2; i += 2) {
    if (!is_playing) {
      break;
    }
    divider = volver_melody[i + 1];
    if (divider == 0) {
      vTaskDelay(wholenote / portTICK_PERIOD_MS);
      continue;
    }
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    if (volver_melody[i] <= 13) {
      continue;
    }
    buzzer_set_freq(volver_melody[i]);
    buzzer_play_for(noteDuration * 0.9);
    vTaskDelay(noteDuration / portTICK_PERIOD_MS);
  }
  is_playing = false;
  vTaskDelete(NULL);
}

void play_godfather() {
  int notes = sizeof(godfather) / sizeof(godfather[0] / 2);
  int wholenote = (60000 * 4) / 80;
  int divider = 0, noteDuration = 0;
  for (int i = 0; i < notes * 2; i += 2) {
    if (!is_playing) {
      break;
    }
    divider = godfather[i + 1];
    if (divider == 0) {
      vTaskDelay(wholenote / portTICK_PERIOD_MS);
      continue;
    }
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    if (godfather[i] <= 13) {
      continue;
    }
    buzzer_set_freq(godfather[i]);
    buzzer_play_for(noteDuration * 0.9);
    vTaskDelay(noteDuration / portTICK_PERIOD_MS);
  }
  is_playing = false;
  vTaskDelete(NULL);
}

void play_nggyup() {
  int notes = sizeof(nggyup) / sizeof(nggyup[0] / 2);
  int wholenote = (60000 * 4) / 114;
  int divider = 0, noteDuration = 0;
  while (is_playing) {
    for (int i = 0; i < notes * 2; i += 2) {
      if (!is_playing) {
        break;
      }
      divider = nggyup[i + 1];
      if (divider == 0) {
        vTaskDelay(wholenote / portTICK_PERIOD_MS);
        continue;
      }
      if (divider > 0) {
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;
      }
      if (nggyup[i] <= 13) {
        continue;
      }
      buzzer_set_freq(nggyup[i]);
      buzzer_play_for(noteDuration * 0.9);
      vTaskDelay(noteDuration / portTICK_PERIOD_MS);
    }
  }
  is_playing = false;
  vTaskDelete(NULL);
}

void play_zelda() {
  int notes = sizeof(zelda_medoly) / sizeof(zelda_medoly[0] / 2);
  int wholenote = (60000 * 4) / TEMPO;
  int divider = 0, noteDuration = 0;
  while (is_playing) {
    for (int i = 0; i < notes * 2; i += 2) {
      if (!is_playing) {
        break;
      }
      divider = zelda_medoly[i + 1];
      if (divider == 0) {
        vTaskDelay(wholenote / portTICK_PERIOD_MS);
        continue;
      }
      if (divider > 0) {
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;
      }
      if (zelda_medoly[i] <= 13) {
        continue;
      }
      buzzer_set_freq(zelda_medoly[i]);
      buzzer_play_for(noteDuration * 0.9);
      vTaskDelay(noteDuration / portTICK_PERIOD_MS);
    }
  }
  is_playing = false;
  vTaskDelete(NULL);
}

void play_sound(uint32_t note, uint32_t time) {
  buzzer_set_freq(note);
  buzzer_play_for(time);
  vTaskDelay(time / portTICK_PERIOD_MS);
}

void sounds_stop_music() {
  is_playing = false;
}

void sounds_play_music() {
  is_playing = true;
  xTaskCreate(play_zelda, "play_sound", 4096, NULL, 5, NULL);
}

void sounds_play_soundtrack(pre_sound_event pre_sound) {
  if (is_playing == true) {
    is_playing = false;
    vTaskDelete(NULL);
  }
  is_playing = true;
  xTaskCreate(pre_sound, "pre_sound", 4096, NULL, 5, NULL);
}