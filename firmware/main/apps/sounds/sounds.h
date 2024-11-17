#include "stdint.h"
#pragma once

typedef void (*pre_sound_event)(void);
void sounds_stop_music();
void sounds_play_music();
void play_sound(uint32_t note, uint32_t time);
void play_zelda();
void play_nggyup();
void play_godfather();
void play_volver();
void play_azul();
void play_imperial_march();
void sounds_play_soundtrack(pre_sound_event pre_sound);
