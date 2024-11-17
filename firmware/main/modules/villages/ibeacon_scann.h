#pragma once

#include <stdio.h>
#include "esp_gap_ble_api.h"
#include "esp_ibeacon_api.h"

typedef void (*on_ibeacon_cb_t)(esp_ble_ibeacon_t*, esp_ble_gap_cb_param_t*);

void ibeacon_scann_begin();
void ibeacon_scann_set_on_ibeacon_cb(on_ibeacon_cb_t cb);