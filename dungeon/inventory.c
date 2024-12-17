#include <stdio.h>
#include <string.h>
#include <windows.h> // Sleep 함수 사용
#include "console_util.h"
#include "key_input.h"
#include "inventory.h"

// 전역 인벤토리 초기화
Inventory playerInventory = { .itemCount = 0 };

// 인벤토리 초기화 함수
// 게임 시작 시 플레이어 인벤토리를 초기화합니다.
void initializeInventory() {
    playerInventory.itemCount = 0;
}

// 아이템 추가 함수
// 새로운 아이템을 인벤토리에 추가하거나, 이미 존재하는 아이템의 수량을 증가시킵니다.
void addItemToInventory(Item newItem) {
    if (playerInventory.itemCount >= MAX_ITEMS) { // 인벤토리 용량 초과 확인
        printf("인벤토리가 가득 찼습니다!\n");
        return;
    }

    // 기존 아이템 검색 및 수량 증가
    for (int i = 0; i < playerInventory.itemCount; i++) {
        if (strcmp(playerInventory.items[i].name, newItem.name) == 0) {
            playerInventory.items[i].quantity += newItem.quantity;
            printf("%s 수량이 증가했습니다: %d\n", newItem.name, playerInventory.items[i].quantity);
            return;
        }
    }

    // 새로운 아이템 추가
    playerInventory.items[playerInventory.itemCount++] = newItem;
    printf("%s을(를) 인벤토리에 추가했습니다.\n", newItem.name);
}

// 공통 메뉴 탐색 함수
// 메뉴 항목을 키보드 화살표와 스페이스바로 탐색하여 선택합니다.
int navigateMenu(const char* menuItems[], int itemCount) {
    int selected = 0; // 현재 선택된 메뉴 항목

    while (1) {
        clearScreen(); // 화면 지우기
        for (int i = 0; i < itemCount; i++) {
            gotoxy(1, i + 1); // 각 메뉴 항목의 위치 설정
            if (i == selected) { // 현재 선택된 항목 강조
                SetColor(0x0E); // 노란색 강조
                printf("> %s\n", menuItems[i]);
                SetColor(0x0F); // 기본 색상으로 복원
            }
            else {
                printf("  %s\n", menuItems[i]);
            }
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) { // 위 방향키 입력 시
            selected = (selected - 1 + itemCount) % itemCount; // 항목 순환
            Sleep(150); // 입력 딜레이
        }
        else if (isKeyPressed(KEY_DOWN)) { // 아래 방향키 입력 시
            selected = (selected + 1) % itemCount; // 항목 순환
            Sleep(150);
        }
        else if (isKeyPressed(KEY_SPACE)) { // 스페이스바 입력 시 선택
            return selected;
        }
    }
}

// 인벤토리 메인 메뉴
// 플레이어가 인벤토리의 카테고리를 탐색하고 세부 항목으로 이동할 수 있도록 구성합니다.
void showInventory() {
    const char* categories[] = { "Equipment", "Consumables", "Loot", "Back" };
    int selected;

    while (1) {
        selected = navigateMenu(categories, 4); // 메뉴 탐색

        switch (selected) {
        case 0:
            manageEquipment(NULL); // 장비 관리 메뉴
            break;
        case 1:
            manageConsumables(); // 소모품 관리 메뉴
            break;
        case 2:
            manageLoots(); // 전리품 관리 메뉴
            break;
        case 3:
            return; // 돌아가기
        }
    }
}

// 장비 관리 메뉴
// 장비를 카테고리별로 세분화하여 관리합니다.
void manageEquipment(InventoryState* state) {
    const char* equipmentTypes[] = { "Weapons", "Armor", "Back" };
    int selected;

    while (1) {
        selected = navigateMenu(equipmentTypes, 3); // 메뉴 탐색

        if (selected == 0) {
            manageWeapons(state); // 무기 관리
        }
        else if (selected == 1) {
            manageArmors(state); // 방어구 관리
        }
        else if (selected == 2) {
            return; // 돌아가기
        }
    }
}

// 무기 관리
// 플레이어가 무기를 선택하고 장착할 수 있도록 처리합니다.
void manageWeapons(InventoryState* state) {
    int selectedItem = 0;

    while (1) {
        clearScreen();
        printf("Weapons Management\n");
        printf("================\n");

        // 무기 리스트 출력
        for (int i = 0; i < WEAPON_COUNT; i++) {
            gotoxy(1, i + 1);
            printf("  %s (Qty: %d) [Str: %d Agi: %d]", weapons[i].name, weapons[i].quantity, weapons[i].effect.strength, weapons[i].effect.agility);
            if (state && state->equippedWeaponIndex == i) { // 장착된 무기 표시
                printf(" [E]");
            }
            printf("\n");
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selectedItem = (selectedItem - 1 + WEAPON_COUNT) % WEAPON_COUNT; // 항목 순환
            Sleep(150);
        }
        else if (isKeyPressed(KEY_DOWN)) {
            selectedItem = (selectedItem + 1) % WEAPON_COUNT; // 항목 순환
            Sleep(150);
        }
        else if (isKeyPressed(KEY_SPACE)) { // 무기 장착
            if (state) {
                state->equippedWeaponIndex = selectedItem;
                printf("\nEquipped %s!\n", weapons[selectedItem].name);
                Sleep(1000);
            }
        }
        else if (isKeyPressed(KEY_ESCAPE)) { // 돌아가기
            return;
        }
    }
}

// 방어구 관리
// 플레이어가 방어구를 선택하고 장착할 수 있도록 처리합니다.
void manageArmors(InventoryState* state) {
    int selectedItem = 0;

    while (1) {
        clearScreen();
        printf("Armor Management\n");
        printf("================\n");

        // 방어구 리스트 출력
        for (int i = 0; i < ARMOR_COUNT; i++) {
            gotoxy(1, i + 1);
            printf("  %s (Qty: %d) [HP: %d Int: %d]", armors[i].name, armors[i].quantity, armors[i].effect.health, armors[i].effect.intelligence);
            if (state) {
                for (int j = 0; j < state->equippedArmorCount; j++) {
                    if (state->equippedArmors[j] == i) { // 장착된 방어구 표시
                        printf(" [E]");
                    }
                }
            }
            printf("\n");
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selectedItem = (selectedItem - 1 + ARMOR_COUNT) % ARMOR_COUNT; // 항목 순환
            Sleep(150);
        }
        else if (isKeyPressed(KEY_DOWN)) {
            selectedItem = (selectedItem + 1) % ARMOR_COUNT; // 항목 순환
            Sleep(150);
        }
        else if (isKeyPressed(KEY_SPACE)) { // 방어구 장착
            if (state && state->equippedArmorCount < MAX_ARMOR_EQUIPPED) {
                state->equippedArmors[state->equippedArmorCount++] = selectedItem;
                printf("\nEquipped %s!\n", armors[selectedItem].name);
                Sleep(1000);
            }
            else {
                printf("\nCannot equip more armor!\n");
                Sleep(1000);
            }
        }
        else if (isKeyPressed(KEY_ESCAPE)) { // 돌아가기
            return;
        }
    }
}

// 소모품 관리
// 소모품의 사용 및 수량을 관리합니다.
void manageConsumables() {
    int selectedItem = 0;

    while (1) {
        clearScreen();
        printf("Consumables Management\n");
        printf("================\n");

        // 소모품 리스트 출력
        for (int i = 0; i < CONSUMABLE_COUNT; i++) {
            gotoxy(1, i + 1);
            printf("  %s (Qty: %d) [Effect: HP+%d Str+%d]\n", consumables[i].name, consumables[i].quantity, consumables[i].effect.health, consumables[i].effect.strength);
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selectedItem = (selectedItem - 1 + CONSUMABLE_COUNT) % CONSUMABLE_COUNT; // 항목 순환
            Sleep(150);
        }
        else if (isKeyPressed(KEY_DOWN)) {
            selectedItem = (selectedItem + 1) % CONSUMABLE_COUNT; // 항목 순환
            Sleep(150);
        }
        else if (isKeyPressed(KEY_SPACE)) { // 소모품 사용
            if (consumables[selectedItem].quantity > 0) {
                consumables[selectedItem].quantity--;
                printf("\nUsed %s!\n", consumables[selectedItem].name);
                Sleep(1000);
            }
            else {
                printf("\nOut of stock!\n");
                Sleep(1000);
            }
        }
        else if (isKeyPressed(KEY_ESCAPE)) { // 돌아가기
            return;
        }
    }
}

// 전리품 관리
// 전리품 항목을 보여주거나 처리할 수 있는 메뉴입니다.
void manageLoots() {
    clearScreen();
    printf("Loot Management\n");
}