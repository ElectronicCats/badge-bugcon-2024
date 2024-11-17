#pragma once

#include <stdbool.h>
#include <stdio.h>

#define COOLDOWN_TIME_S 60
#define COOLDOWN_MEM    "toast_cooldown"

typedef enum { WAITING_STATE, IN_PROGREES_STATE, FINISH_STATE } toast_states_t;

typedef struct {
  uint8_t state;
  uint16_t cooldown_time;
  volatile bool waiting;
} toast_ctx_t;

void toast_begin();
void toast_init();
bool toast_is_ready();
void toast_exit();