#ifndef INVENTORY_H
#define INVENTORY_H

#include "items.h"

#define MAX_ITEMS 100

// 인벤토리 구조체
typedef struct {
    Item items[MAX_ITEMS];  // 아이템 배열
    int itemCount;          // 현재 아이템 수
} Inventory;

extern Inventory playerInventory;

void initializeInventory();                  // 인벤토리 초기화
void addItemToInventory(Item newItem);       // 아이템 추가
void showInventory();                        // 인벤토리 보기 함수

#endif // INVENTORY_H