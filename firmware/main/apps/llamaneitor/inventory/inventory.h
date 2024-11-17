#pragma once

#include <stdbool.h>
#include <stdio.h>

#define ITEM1_MEM "item1"
#define ITEM2_MEM "item2"
#define ITEM3_MEM "item3"
#define ITEM4_MEM "item4"

void inventory_load_items();
void inventory_save_items();
void inventory_unlock_item(uint8_t item);
void inventory_drop_item(uint8_t item);
bool inventory_is_unlocked_item(uint8_t item);