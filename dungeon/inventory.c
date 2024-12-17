#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "console_util.h"
#include "key_input.h"
#include "inventory.h"
#include "items.h" // 아이템 데이터 포함

// 전역 인벤토리 초기화
Inventory playerInventory = { .itemCount = 0 };

// 인벤토리 초기화 함수
void initializeInventory() {
    playerInventory.itemCount = 0;
}

// 아이템 추가 함수
void addItemToInventory(Item newItem) {
    for (int i = 0; i < playerInventory.itemCount; i++) {
        if (strcmp(playerInventory.items[i].name, newItem.name) == 0) {
            playerInventory.items[i].quantity += newItem.quantity;
            printf("아이템 수량 증가: %s (수량: %d)\n", newItem.name, playerInventory.items[i].quantity);
            return;
        }
    }

    if (playerInventory.itemCount < MAX_ITEMS) {
        playerInventory.items[playerInventory.itemCount++] = newItem;
        printf("아이템 추가: %s\n", newItem.name);
    } else {
        printf("인벤토리가 가득 찼습니다!\n");
    }
}

// 인벤토리 보기
void showInventory() {
    printf("\n===== 인벤토리 =====\n");
    for (int i = 0; i < playerInventory.itemCount; i++) {
        printf("%d. %s (수량: %d)\n", i + 1, playerInventory.items[i].name, playerInventory.items[i].quantity);
    }
    printf("===================\n");
    Sleep(1000);
}