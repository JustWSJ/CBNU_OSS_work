#include <stdio.h>
#include <string.h>
#include <windows.h> // Sleep 함수 사용
#include "console_util.h"
#include "key_input.h"
#include "inventory.h"
// 전역 인벤토리 초기화
Inventory playerInventory = { .itemCount = 0 };

// 새로 추가된 함수: 인벤토리 초기화
void initializeInventory() {
    playerInventory.itemCount = 0;
}

// 새로 추가된 함수: 아이템 추가
void addItemToInventory(Item newItem) {
    if (playerInventory.itemCount >= MAX_ITEMS) {
        printf("인벤토리가 가득 찼습니다!\n");
        return;
    }

    // 동일한 아이템이 있으면 수량 증가
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

// 전역 인벤토리 초기화
Inventory playerInventory = { .itemCount = 0 };

// 인벤토리 초기화 함수
void initializeInventory() {
    playerInventory.itemCount = 0;
}

// 아이템 추가 함수
void addItemToInventory(Item newItem) {
    if (playerInventory.itemCount >= MAX_ITEMS) {
        printf("인벤토리가 가득 찼습니다!\n");
        return;
    }

    // 동일한 아이템 확인
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
int navigateMenu(const char* menuItems[], int itemCount) {
    int selected = 0;

    while (1) {
        clearScreen();
        for (int i = 0; i < itemCount; i++) {
            gotoxy(1, i + 1);
            if (i == selected) {
                SetColor(0x0E); // 노란색 표시
                printf("> %s\n", menuItems[i]);
                SetColor(0x0F); // 기본 색상 복원
            } else {
                printf("  %s\n", menuItems[i]);
            }
        }

        // 방향키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selected = (selected - 1 + itemCount) % itemCount;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selected = (selected + 1) % itemCount;
            Sleep(150);
        } else if (isKeyPressed(KEY_SPACE)) {
            return selected; // 선택된 항목 반환
        }
    }
}

// 인벤토리 메인 메뉴
void showInventory() {
    const char* categories[] = {"Equipment", "Consumables", "Loot", "Back"};
    int selected;

    while (1) {
        selected = navigateMenu(categories, 4);

        switch (selected) {
            case 0:
                manageEquipment(NULL);
                break;
            case 1:
                manageConsumables();
                break;
            case 2:
                manageLoots();
                break;
            case 3:
                return;
        }
    }
}

// 장비 관리 메뉴
void manageEquipment(InventoryState* state) {
    const char* equipmentTypes[] = {"Weapons", "Armor", "Back"};
    int selected;

    while (1) {
        selected = navigateMenu(equipmentTypes, 3);

        if (selected == 0) {
            manageWeapons(state);
        } else if (selected == 1) {
            manageArmors(state);
        } else if (selected == 2) {
            return; // 돌아가기
        }
    }
}

// 무기 관리
void manageWeapons(InventoryState* state) {
    int selectedItem = 0;

    while (1) {
        clearScreen();
        printf("Weapons Management\n");
        printf("================\n");

        for (int i = 0; i < WEAPON_COUNT; i++) {
            gotoxy(1, i + 1);
            printf("  %s (Qty: %d) [Str: %d Agi: %d]", weapons[i].name, weapons[i].quantity, weapons[i].effect.strength, weapons[i].effect.agility);
            if (state && state->equippedWeaponIndex == i) {
                printf(" [E]");
            }
            printf("\n");
        }

        if (isKeyPressed(KEY_UP)) {
            selectedItem = (selectedItem - 1 + WEAPON_COUNT) % WEAPON_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selectedItem = (selectedItem + 1) % WEAPON_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_SPACE)) {
            if (state) {
                state->equippedWeaponIndex = selectedItem;
                printf("\nEquipped %s!\n", weapons[selectedItem].name);
                Sleep(1000);
            }
        } else if (isKeyPressed(KEY_ESCAPE)) {
            return;
        }
    }
}

// 방어구 관리
void manageArmors(InventoryState* state) {
    int selectedItem = 0;

    while (1) {
        clearScreen();
        printf("Armor Management\n");
        printf("================\n");

        for (int i = 0; i < ARMOR_COUNT; i++) {
            gotoxy(1, i + 1);
            printf("  %s (Qty: %d) [HP: %d Int: %d]", armors[i].name, armors[i].quantity, armors[i].effect.health, armors[i].effect.intelligence);
            if (state) {
                for (int j = 0; j < state->equippedArmorCount; j++) {
                    if (state->equippedArmors[j] == i) {
                        printf(" [E]");
                    }
                }
            }
            printf("\n");
        }

        if (isKeyPressed(KEY_UP)) {
            selectedItem = (selectedItem - 1 + ARMOR_COUNT) % ARMOR_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selectedItem = (selectedItem + 1) % ARMOR_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_SPACE)) {
            if (state && state->equippedArmorCount < MAX_ARMOR_EQUIPPED) {
                state->equippedArmors[state->equippedArmorCount++] = selectedItem;
                printf("\nEquipped %s!\n", armors[selectedItem].name);
                Sleep(1000);
            } else {
                printf("\nCannot equip more armor!\n");
                Sleep(1000);
            }
        } else if (isKeyPressed(KEY_ESCAPE)) {
            return;
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

        for (int i = 0; i < CONSUMABLE_COUNT; i++) {
            gotoxy(1, i + 1);
            printf("  %s (Qty: %d) [Effect: HP+%d Str+%d]\n", consumables[i].name, consumables[i].quantity, consumables[i].effect.health, consumables[i].effect.strength);
        }

        if (isKeyPressed(KEY_UP)) {
            selectedItem = (selectedItem - 1 + CONSUMABLE_COUNT) % CONSUMABLE_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selectedItem = (selectedItem + 1) % CONSUMABLE_COUNT;
            Sleep(150);
        } else if (isKeyPressed(KEY_SPACE)) {
            if (consumables[selectedItem].quantity > 0) {
                consumables[selectedItem].quantity--;
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

    for (int i = 0; i < LOOT_COUNT; i++) {
        printf("  %s (Qty: %d) - %s\n", loots[i].name, loots[i].quantity, loots[i].description);
    }

    printf("\nPress any key to return...");
    system("pause > nul");
}
