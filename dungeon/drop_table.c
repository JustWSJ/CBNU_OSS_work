#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "drop_table.h"
#include "inventory.h"

// 드롭 테이블 데이터
static DropTable dropTable[] = {
    {0, 50, {"Health Potion", ITEM_CONSUMABLE, 1, {20, 0, 0, 0, 0, 0}, "HP를 회복하는 포션"}},
    {0, 30, {"Mana Elixir", ITEM_CONSUMABLE, 1, {0, 0, 0, 20, 0, 0}, "MP를 회복하는 포션"}},
    {1, 70, {"Steel Sword", ITEM_WEAPON, 1, {0, 10, 2, 0, 5, 1}, "강철로 만든 검"}},
    {2, 40, {"Iron Shield", ITEM_ARMOR, 1, {10, 0, 0, 0, 0, 0}, "튼튼한 철 방패"}}
};

// 드롭 테이블 반환
const DropTable* getDropTable(int monsterID, int* count) {
    static DropTable result[10]; // 몬스터 ID에 해당하는 드롭 데이터 저장
    int index = 0;

    for (int i = 0; i < sizeof(dropTable) / sizeof(dropTable[0]); i++) {
        if (dropTable[i].monsterID == monsterID) {
            result[index++] = dropTable[i];
        }
    }
    *count = index; // 해당 몬스터의 드롭 아이템 개수
    return result;
}

// 드롭 아이템 처리
void dropItem(int monsterID) {
    int dropCount = 0;
    const DropTable* drops = getDropTable(monsterID, &dropCount);

    for (int i = 0; i < dropCount; i++) {
        int randomValue = rand() % 100; // 난수 생성

        if (randomValue < drops[i].dropRate) {
            // 드롭 성공: 아이템 획득
            printf("축하합니다! %s을(를) 획득했습니다!\n", drops[i].dropItem.name);
            addItemToInventory(drops[i].dropItem);
        }
    }
}