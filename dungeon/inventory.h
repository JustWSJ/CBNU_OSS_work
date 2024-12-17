#ifndef INVENTORY_H
#define INVENTORY_H

#include "items.h"

#define MAX_ITEMS 100         // 인벤토리 최대 크기
#define MAX_ARMOR_EQUIPPED 5  // 최대 장착 가능한 방어구 수

// 인벤토리 상태 구조체
typedef struct {
    int equippedWeaponIndex;              // 현재 장착된 무기의 인덱스 (-1: 미장착)
    int equippedArmors[MAX_ARMOR_EQUIPPED]; // 현재 장착된 방어구의 인덱스
    int equippedArmorCount;               // 현재 장착된 방어구의 개수
} InventoryState;

// 전체 인벤토리 구조체
typedef struct {
    Item items[MAX_ITEMS];  // 현재 플레이어가 소유한 아이템 배열
    int itemCount;          // 현재 아이템 수
} Inventory;

extern Inventory playerInventory; // 전역 인벤토리 선언

// 함수 선언
void initializeInventory();                  // 인벤토리 초기화
void addItemToInventory(Item newItem);       // 아이템 추가
int navigateMenu(const char* menuItems[], int itemCount);
void showInventory();                        // 인벤토리 메인 메뉴 표시

// 관리 함수 선언
void manageEquipment(InventoryState* state); // 장비 관리 메뉴
void manageWeapons(InventoryState* state);   // 무기 관리 메뉴
void manageArmors(InventoryState* state);    // 방어구 관리 메뉴
void manageConsumables();                    // 소모품 관리 메뉴
void manageLoots();                          // 전리품 관리 메뉴

#endif // INVENTORY_H