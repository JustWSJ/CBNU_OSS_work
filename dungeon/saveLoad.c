#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include "Character.h"
#include "inventory.h"
#include "saveLoad.h"

void saveStatus(Character* player) {
    // 상대 경로로 지정된 저장 폴더와 파일 이름
    char *folder = "save";
    char *filename = "save/save_000.txt";

    // 디렉터리 생성 (이미 존재하면 무시)
    struct stat st = {0};
    if (stat(folder, &st) == -1) {
        if (mkdir(folder) != 0) { //mkdir(folder, 0700)이었는데 too many argu가 뜸
            printf("디렉터리를 생성할 수 없습니다: %s\n", folder);
            return;
        }
    }

    // 파일 열기
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("파일을 열 수 없습니다: %s\n", filename);
        return;
    }

    // 스테이터스 저장
    fprintf(file, "Health: %d", player->health);
    fprintf(file, "Strength: %d", player->strength);
    fprintf(file, "Agility: %d", player->agility);
    fprintf(file, "Intelligence: %d", player->intelligence);
    fprintf(file, "Sensory: %d", player->sensory);
    fprintf(file, "Luck: %d", player->luck);
    fprintf(file, "max_health: %d", player->max_health);
    fprintf(file, "cur_health: %d", player->cur_health);
    fprintf(file, "Maxfloor: %d", player->Maxfloor);

    fclose(file); // 파일 닫기
    //printf("저장 완료: %s\n", filename);
}

int loadStatus(Character* player) {
    // 저장된 파일 경로
    char *filename = "save/save_000.txt";
    
    // 파일 열기
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("파일을 열 수 없습니다: %s\n", filename);
        return -1;
    }

    // 파일에서 데이터 읽기
    if (fscanf(file, "Health: %d", &player->health) != 1 ||
        fscanf(file, "Strength: %d", &player->strength) != 1 ||
        fscanf(file, "Agility: %d", &player->agility) != 1 ||
        fscanf(file, "Intelligence: %d", &player->intelligence) != 1 ||
        fscanf(file, "Sensory: %d", &player->sensory) != 1 ||
        fscanf(file, "Luck: %d", &player->luck) != 1 ||
        fscanf(file, "max_health: %d", &player->max_health) != 1 ||
        fscanf(file, "cur_health: %d", &player->cur_health) != 1 ||
        fscanf(file, "Maxfloor: %d", &player->Maxfloor) != 1) {
        printf("파일 형식이 잘못되었습니다: %s\n", filename);
        fclose(file);
        return 1;
    }

    

    fclose(file); // 파일 닫기
}


// 인벤토리 저장
void saveInventory(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("인벤토리를 저장할 수 없습니다: %s\n", filename);
        return;
    }

    fprintf(file, "ItemCount: %d\n", playerInventory.itemCount);

    for (int i = 0; i < playerInventory.itemCount; i++) {
        Item item = playerInventory.items[i];
        fprintf(file, "\"%s\" %d %d %d %d %d %d %d %d \"%s\"\n",
                item.name, item.type, item.quantity,
                item.effect.health, item.effect.strength, item.effect.agility,
                item.effect.intelligence, item.effect.sensory, item.effect.luck,
                item.description);
    }

    fclose(file);
    printf("인벤토리가 저장되었습니다: %s\n", filename);
}

// 인벤토리 로드
void loadInventory(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("저장된 인벤토리를 불러올 수 없습니다: %s\n", filename);
        return;
    }

    initializeInventory();

    int itemCount;
    if (fscanf(file, "ItemCount: %d\n", &itemCount) != 1 || itemCount < 0 || itemCount > MAX_ITEMS) {
        printf("잘못된 파일 형식 또는 아이템 개수 초과: %s\n", filename);
        fclose(file);
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        Item item;

        if (fscanf(file, "\"%49[^\"]\" %d %d %d %d %d %d %d %d \"%99[^\"]\"\n",
                   item.name, &item.type, &item.quantity,
                   &item.effect.health, &item.effect.strength, &item.effect.agility,
                   &item.effect.intelligence, &item.effect.sensory, &item.effect.luck,
                   item.description) != 10) {
            printf("파일 읽기 오류 또는 잘못된 데이터 형식.\n");
            fclose(file);
            return;
        }

        addItemToInventory(item);
    }

    fclose(file);
    printf("인벤토리가 불러와졌습니다: %s\n", filename);
}