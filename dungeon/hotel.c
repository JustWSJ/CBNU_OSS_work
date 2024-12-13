#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hotel.h"

// 세이브 데이터 저장 함수
void saveProgress(const char* dungeonName, int clearedFloor) {
    FILE *file = fopen("save_data.txt", "w");
    if (file == NULL) {
        printf("세이브 파일을 열 수 없습니다.\n");
        return;
    }

    fprintf(file, "%s\n%d\n", dungeonName, clearedFloor);
    fclose(file);
    printf("진행 상황이 저장되었습니다! (%s 던전, %d층 클리어)\n", dungeonName, clearedFloor);
}
