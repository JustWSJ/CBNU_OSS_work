#include <stdio.h>
#include <string.h>
#include <windows.h> // Sleep 함수 사용
#include "console_util.h"
#include "key_input.h"
#include "inventory.h"

#define INDENT 53 // 인벤토리 시작 X좌표
#define INVENTORY_AREA_HEIGHT 20 // 인벤토리 출력 영역의 높이

// 전역 인벤토리 초기화
Inventory playerInventory = { .itemCount = 0 };

// 화면 덮어쓰기 함수: 특정 영역만 지우기
void clearInventoryArea(int lines) {
    for (int i = 0; i < lines; i++) {
        gotoxy(INDENT, i + 1);
        printf("%-50s", " "); // 빈 공간 출력
    }
}

// 인벤토리 초기화 함수
void initializeInventory() {
    playerInventory.itemCount = 0;
}

// 아이템 추가 함수
void addItemToInventory(Item newItem) {
    if (playerInventory.itemCount >= MAX_ITEMS) {
        gotoxy(INDENT, 1);
        printf("인벤토리가 가득 찼습니다!\n");
        return;
    }

    for (int i = 0; i < playerInventory.itemCount; i++) {
        if (strcmp(playerInventory.items[i].name, newItem.name) == 0) {
            playerInventory.items[i].quantity += newItem.quantity;
            gotoxy(INDENT, 1);
            printf("%s 수량이 증가했습니다: %d\n", newItem.name, playerInventory.items[i].quantity);
            return;
        }
    }

    playerInventory.items[playerInventory.itemCount++] = newItem;
    gotoxy(INDENT, 1);
    printf("%s을(를) 인벤토리에 추가했습니다.\n", newItem.name);
}

// 메뉴 탐색 함수
int navigateMenu(const char* menuItems[], int itemCount) {
    int selected = 0;
    int updated = 1;

    while (1) {
        if (updated) {
            clearInventoryArea(itemCount + 2);
            gotoxy(INDENT, 1);
            printf("========== 인벤토리 ==========\n");

            for (int i = 0; i < itemCount; i++) {
                gotoxy(INDENT, i + 2);
                if (i == selected) {
                    SetColor(0x0E);
                    printf("> %s", menuItems[i]);
                    SetColor(0x0F);
                } else {
                    printf("  %s", menuItems[i]);
                }
            }
            updated = 0;
        }

        if (isKeyPressed(KEY_UP)) {
            selected = (selected - 1 + itemCount) % itemCount;
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selected = (selected + 1) % itemCount;
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_SPACE)) {
            return selected;
        }
    }
}

// 인벤토리 메인 메뉴
void showInventory() {
    const char* categories[] = { "Equipment", "Consumables", "Loot", "Back" };
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
    const char* equipmentTypes[] = { "Weapons", "Armor", "Back" };
    int selected;

    while (1) {
        selected = navigateMenu(equipmentTypes, 3);

        if (selected == 0) {
            manageWeapons(state);
        } else if (selected == 1) {
            manageArmors(state);
        } else if (selected == 2) {
            return;
        }
    }
}

// 무기 관리
void manageWeapons(InventoryState* state) {
    int selectedItem = 0;

    while (1) {
        clearInventoryArea(WEAPON_COUNT + 2);
        gotoxy(INDENT, 1);
        printf("Weapons Management\n");
        gotoxy(INDENT, 2);
        printf("================\n");

        for (int i = 0; i < WEAPON_COUNT; i++) {
            gotoxy(INDENT, i + 3);
            printf("  %s (Qty: %d) [Str: %d Agi: %d]", weapons[i].name, weapons[i].quantity, weapons[i].effect.strength, weapons[i].effect.agility);
            if (state && state->equippedWeaponIndex == i) {
                printf(" [E]");
            }
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
                gotoxy(INDENT, WEAPON_COUNT + 5);
                printf("Equipped %s!\n", weapons[selectedItem].name);
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
        clearInventoryArea(ARMOR_COUNT + 2);
        gotoxy(INDENT, 1);
        printf("Armor Management\n");
        gotoxy(INDENT, 2);
        printf("================\n");

        for (int i = 0; i < ARMOR_COUNT; i++) {
            gotoxy(INDENT, i + 3);
            printf("  %s (Qty: %d) [HP: %d Int: %d]", armors[i].name, armors[i].quantity, armors[i].effect.health, armors[i].effect.intelligence);
            for (int j = 0; j < state->equippedArmorCount; j++) {
                if (state->equippedArmors[j] == i) {
                    printf(" [E]");
                }
            }
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
                gotoxy(INDENT, ARMOR_COUNT + 5);
                printf("Equipped %s!\n", armors[selectedItem].name);
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
        clearInventoryArea(CONSUMABLE_COUNT + 2);
        gotoxy(INDENT, 1);
        printf("Consumables Management\n");
        gotoxy(INDENT, 2);
        printf("================\n");

        for (int i = 0; i < CONSUMABLE_COUNT; i++) {
            gotoxy(INDENT, i + 3);
            printf("  %s (Qty: %d) [Effect: HP+%d Str+%d]", consumables[i].name, consumables[i].quantity, consumables[i].effect.health, consumables[i].effect.strength);
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
                gotoxy(INDENT, CONSUMABLE_COUNT + 5);
                printf("Used %s!\n", consumables[selectedItem].name);
                Sleep(1000);
            } else {
                printf("Out of stock!\n");
                Sleep(1000);
            }
        } else if (isKeyPressed(KEY_ESCAPE)) {
            return;
        }
    }
}

// 전리품 관리
void manageLoots() {
    clearInventoryArea(5);
    gotoxy(INDENT, 1);
    printf("Loot Management\n");
}
