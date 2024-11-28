#include <stdio.h>
#include "console_util.h"
#include "key_input.h"
#include "inventory.h"

// 인벤토리 메인 메뉴
void showInventory() {
    InventoryState state = {-1, {0}, 0}; // 초기 상태: 무기 미장착, 방어구 없음
    int selectedCategory = 0; // 0: 장비, 1: 소모품, 2: 전리품, 3: 돌아가기
    const char* categories[] = {"Equipment", "Consumables", "Loot", "Back"}; // 메뉴 항목

    while (1) {
        clearScreen(); // 화면 초기화
        printf("Inventory\n");
        printf("================\n");

        // 카테고리 출력
        for (int i = 0; i < 4; i++) {
            gotoxy(1, i + 1);
            if (i == selectedCategory) {
                SetColor(0x0E); // 선택된 항목은 노란색으로 표시
                printf("> %s\n", categories[i]);
                SetColor(0x0F); // 기본 색상 복원
            } else {
                printf("  %s\n", categories[i]);
            }
        }

        // 방향키 및 스페이스 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selectedCategory = (selectedCategory - 1 + 4) % 4; // 위로 이동
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selectedCategory = (selectedCategory + 1) % 4; // 아래로 이동
            Sleep(150);
        } else if (isKeyPressed(KEY_SPACE)) {
            // 선택된 카테고리에 따라 함수 호출
            if (selectedCategory == 0) {
                manageEquipment(&state);
            } else if (selectedCategory == 1) {
                manageConsumables();
            } else if (selectedCategory == 2) {
                manageLoots();
            } else if (selectedCategory == 3) {
                return; // 돌아가기
            }
        }
    }
}

// 장비 관리 메뉴
void manageEquipment(InventoryState* state) {
    int selectedType = 0; // 0: 무기, 1: 방어구
    const char* equipmentTypes[] = {"Weapons", "Armor"}; // 장비 유형

    while (1) {
        clearScreen(); // 화면 초기화
        printf("Equipment Management\n");
        printf("================\n");

        // 장비 유형 출력
        for (int i = 0; i < 2; i++) {
            gotoxy(1, i + 1);
            if (i == selectedType) {
                SetColor(0x0E); // 선택된 항목 노란색
                printf("> %s\n", equipmentTypes[i]);
                SetColor(0x0F);
            } else {
                printf("  %s\n", equipmentTypes[i]);
            }
        }

        // 방향키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selectedType = (selectedType - 1 + 2) % 2; // 위로 이동
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selectedType = (selectedType + 1) % 2; // 아래로 이동
            Sleep(150);
        } else if (isKeyPressed(KEY_SPACE)) {
            // 무기 또는 방어구 관리 호출
            if (selectedType == 0) {
                manageWeapons(state);
            } else if (selectedType == 1) {
                manageArmors(state);
            }
        }
    }
}

// 무기 관리
void manageWeapons(InventoryState* state) {
    int selectedItem = 0; // 선택된 무기의 인덱스

    while (1) {
        clearScreen(); // 화면 초기화
        printf("Weapons Management\n");
        printf("================\n");

        // 무기 목록 출력
        for (int i = 0; i < WEAPON_COUNT; i++) {
            gotoxy(1, i + 1);
            printf("  %s (Qty: %d) [Str: %d Agi: %d]", weapons[i].name, weapons[i].quantity, weapons[i].statBoost.strength, weapons[i].statBoost.agility);
            if (state->equippedWeaponIndex == i) {
                printf(" [E]"); // 장착된 무기 표시
            }
            printf("\n");
        }

        // 방향키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selectedItem = (selectedItem - 1 + WEAPON_COUNT) % WEAPON_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selectedItem = (selectedItem + 1) % WEAPON_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_SPACE)) {
            // 무기 장착
            state->equippedWeaponIndex = selectedItem;
            printf("\nEquipped %s!\n", weapons[selectedItem].name);
            Sleep(1000);
        } else if (isKeyPressed(KEY_ESCAPE)) {
            return; // 돌아가기
        }
    }
}

// 방어구 관리
void manageArmors(InventoryState* state) {
    int selectedItem = 0; // 선택된 방어구 인덱스

    while (1) {
        clearScreen(); // 화면 초기화
        printf("Armor Management\n");
        printf("================\n");

        // 방어구 목록 출력
        for (int i = 0; i < ARMOR_COUNT; i++) {
            gotoxy(1, i + 1);
            printf("  %s (Qty: %d) [HP: %d Int: %d]", armors[i].name, armors[i].quantity, armors[i].statBoost.health, armors[i].statBoost.intelligence);
            for (int j = 0; j < state->equippedArmorCount; j++) {
                if (state->equippedArmors[j] == i) {
                    printf(" [E]"); // 장착된 방어구 표시
                }
            }
            printf("\n");
        }

        // 방향키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selectedItem = (selectedItem - 1 + ARMOR_COUNT) % ARMOR_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selectedItem = (selectedItem + 1) % ARMOR_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_SPACE)) {
            if (state->equippedArmorCount < MAX_ARMOR_EQUIPPED) { // 방어구 장착
                state->equippedArmors[state->equippedArmorCount++] = selectedItem;
                printf("\nEquipped %s!\n", armors[selectedItem].name);
                Sleep(1000);
            } else {
                printf("\nCannot equip more armor!\n");
                Sleep(1000);
            }
        } else if (isKeyPressed(KEY_ESCAPE)) {
            return; // 돌아가기
        }
    }
}

// 소모품 관리
void manageConsumables() {
    int selectedItem = 0;

    while (1) {
        clearScreen();
        printf("Consumables Management\n");
        printf("================\n");

        // 소모품 목록 출력
        for (int i = 0; i < CONSUMABLE_COUNT; i++) {
            gotoxy(1, i + 1);
            printf("  %s (Qty: %d) [Effect: HP+%d Str+%d]\n",
                   consumables[i].name, consumables[i].quantity, consumables[i].effect.health, consumables[i].effect.strength);
        }

        // 방향키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selectedItem = (selectedItem - 1 + CONSUMABLE_COUNT) % CONSUMABLE_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selectedItem = (selectedItem + 1) % CONSUMABLE_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_SPACE)) {
            if (consumables[selectedItem].quantity > 0) {
                consumables[selectedItem].quantity--; // 소모품 사용
                printf("\nUsed %s!\n", consumables[selectedItem].name);
                Sleep(1000);
            } else {
                printf("\nOut of stock!\n");
                Sleep(1000);
            }
        } else if (isKeyPressed(KEY_ESCAPE)) {
            return;
        }
    }
}

// 전리품 관리
void manageLoots() {
    clearScreen();
    printf("Loot Management\n");
    printf("================\n");

    // 전리품 목록 출력
    for (int i = 0; i < LOOT_COUNT; i++) {
        printf("  %s (Qty: %d) - %s\n", loots[i].name, loots[i].quantity, loots[i].effect);
    }

    printf("\nPress any key to return...");
    system("pause > nul");
}