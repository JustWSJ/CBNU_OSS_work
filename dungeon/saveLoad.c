#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "character.h"

void saveStatus(Character* player) {
    // 상대 경로로 지정된 저장 폴더와 파일 이름
    char *folder = "save";
    char *filename = "save/save_000.txt";

    // 디렉터리 생성 (이미 존재하면 무시)
    struct stat st = {0};
    if (stat(folder, &st) == -1) {
        if (mkdir(folder, 0700) != 0) {
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
    fprintf(file, "Maxfloor: %d", player->Maxfloor);

    fclose(file); // 파일 닫기
    printf("저장 완료: %s\n", filename);
}

void loadStatus(Character* player) {
    // 저장된 파일 경로
    char *filename = "save/save_000.txt";
    
    // 파일 열기
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("파일을 열 수 없습니다: %s\n", filename);
        return;
    }

    // 파일에서 데이터 읽기
    if (fscanf(file, "Health: %d", &player->health) != 1 ||
        fscanf(file, "Strength: %d", &player->strength) != 1 ||
        fscanf(file, "Agility: %d", &player->agility) != 1 ||
        fscanf(file, "Intelligence: %d", &player->intelligence) != 1 ||
        fscanf(file, "Sensory: %d", &player->sensory) != 1 ||
        fscanf(file, "Luck: %d", &player->luck) != 1 ||
        fscanf(file, "Maxfloor: %d", &player->Maxfloor) != 1) {
        printf("파일 형식이 잘못되었습니다: %s\n", filename);
        fclose(file);
        return;
    }

    fclose(file); // 파일 닫기
}