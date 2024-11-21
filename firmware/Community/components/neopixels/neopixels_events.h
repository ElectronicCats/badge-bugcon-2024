#pragma once
#include <stdbool.h>
#include <stdio.h>
#include "esp_random.h"

typedef void (*neopixel_event)(void);
typedef struct {
  neopixel_event animation;
  volatile bool is_running;
} neopixel_animation_ctx_t;

void neopixel_scanning_event();
void neopixel_events_stop_event();
void neopixel_events_run_event(neopixel_event event);

void neopixels_events_set_animation(neopixel_event event);
void neopixels_events_set_notification(neopixel_event notification,
                                       uint16_t time_ms);

void neopixel_llamaneitor_init();
void neopixel_message_notify();
void neopixel_volatil_notification();