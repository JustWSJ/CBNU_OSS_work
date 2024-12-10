#ifndef SAVE_H
#define SAVE_H

#include "character.h"
#include "inventory.h"

void saveStatus(Character* player);
void loadStatus(Character* player);

// 인벤토리 저장/로드
void saveInventory(const char* filename);
void loadInventory(const char* filename);

#endif
