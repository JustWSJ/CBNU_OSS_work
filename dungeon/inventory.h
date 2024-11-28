#ifndef INVENTORY_H
#define INVENTORY_H

#include "items.h"

#define MAX_ARMOR_EQUIPPED 5 // 최대 장착 가능한 방어구 수

// 인벤토리 상태 구조체
typedef struct {
    int equippedWeaponIndex;              // 현재 장착된 무기의 인덱스 (-1: 미장착)
    int equippedArmors[MAX_ARMOR_EQUIPPED]; // 현재 장착된 방어구의 인덱스
    int equippedArmorCount;               // 현재 장착된 방어구의 개수
} InventoryState;

// 인벤토리 관련 함수 선언
void showInventory();                      // 인벤토리 메인 메뉴 표시
void manageEquipment(InventoryState* state); // 장비 관리 메뉴
void manageWeapons(InventoryState* state);   // 무기 관리 메뉴
void manageArmors(InventoryState* state);    // 방어구 관리 메뉴
void manageConsumables();                   // 소모품 관리 메뉴
void manageLoots();                         // 전리품 관리 메뉴

#endif