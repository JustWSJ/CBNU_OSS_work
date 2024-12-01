#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console_util.h"
#include "key_input.h"
#include "dungeon.h"

#define INDENT 1            // 메뉴의 왼쪽 들여쓰기
#define GAP 1

void Dungeon(){
    int floor = SelectFloor(10);
    int option = DungeonEntrance(floor);
    while (1){
        if (option==0) {
            floor++;
            if (floor == 100) {
                clearScreen();
                printf("Dungeon Clear!\n");
                wait();
                exit(0);
            } else if (isClear(floor)) option = DungeonEntrance(floor);
            else DungeonAdventure(floor);

        } else {
            clearScreen();
            printf("마을로 돌아갑니다.\n");
            wait();
            return;
        }
    }
    return;
}

void DungeonAdventure(int floor){
    clearScreen();
    int size = DungeonSize(floor);
    char **map;
    map = CreateDungeon(floor, size);
    if (*map == NULL) {
        printf("NULL");
    } else {
        MoveDungeon(map, size);
    }
    wait(); // 지우기
    return;
}

int SelectFloor(int MENU_COUNT){
    clearScreen();
    const int floors[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90}; // 층수 배열
    int selected = 0;       // 선택된 항목 인덱스
    int updated = 1;        // 화면 갱신 여부 (1: 갱신 필요, 0: 갱신 불필요)

    printf("던전 입구 선택");
    while (1) {
        // 메뉴 출력 (updated가 1일 때만)
        if (updated) {
                for (int i = 0; i < MENU_COUNT; i++) {
                gotoxy(INDENT, GAP + i);
                if (i == selected) {
                    SetColor(0x0E); // 선택된 메뉴: 노란색
                    printf("> %d", floors[i]);
                    SetColor(0x0F); // 기본 색상 흰색으로 복구
                } else {
                    printf("  %d", floors[i]);
                }
            }
            updated = 0; // 출력 후 갱신 플래그 해제
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selected = (selected - 1 + MENU_COUNT) % MENU_COUNT; // 위로 이동
            updated = 1; // 선택 항목 변경, 화면 갱신 필요
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selected = (selected + 1) % MENU_COUNT; // 아래로 이동
            updated = 1; // 선택 항목 변경, 화면 갱신 필요
            Sleep(150);
        } else if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
            Sleep(150);
            return floors[selected]; // 선택된 층 반환
        }
    }
}

int DungeonEntrance(int Floor){
    clearScreen();
    printf(" 던전 %d층\n", Floor);
    const char* options[] = {
        "다음 층으로 가기",
        "마을로 돌아가기"
    };
    int choice = 0;    // 선택된 항목 인덱스
    int updated = 1;   // 화면 갱신 여부 (1: 갱신 필요, 0: 갱신 불필요)
    int menu_count = sizeof(options) / sizeof(options[0]);

    while (1) {
        // 메뉴 출력 (updated가 1일 때만)
        if (updated) {
            clearScreen();
            printf(" 던전 %d층\n", Floor);
            for (int i = 0; i < menu_count; i++) {
                gotoxy(INDENT, GAP + i);
                if (i == choice) {
                    SetColor(0x0E);
                    printf("> %s", options[i]);
                    SetColor(0x0F);
                } else {
                    printf("  %s", options[i]);
                }
            }
            updated = 0; // 출력 후 갱신 플래그 해제
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            choice = (choice - 1 + menu_count) % menu_count;
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            choice = (choice + 1) % menu_count;
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
            Sleep(150);
            clearScreen();
            return choice; // 선택된 메뉴 반환 (0: 다음 층, 1: 마을로 돌아가기)
        }
    } 
}

int isClear(int floor){
    // 나중에 &&으로 조건 추가해야함 일단은 10층 단위가 클리어 된 판정
    if (floor % 10 == 0) {
        return 1;
    } else return 0;
}

int DungeonSize(int floor) {
    if (isClear(floor) == 0 && floor % 10 == 0) {
        // 보스 방 처리
        return -1;
    } else if (floor % 10 == 0) {
        //클리어 된 보스 방
        return -2;
    } else if (floor / 10 < 1) {
        // 저층 던전 처리
        return 7;
    } else {
        // 나머지 층
        return 17;
    }
}

char** CreateDungeon(int floor, int size) {
    
    if (size == -1 || size == -2) {
        return NULL;
    }

    // 이차원 배열 동적 할당
    char** dungeon = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        dungeon[i] = (char*)malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) dungeon[i][j] = 'W'; // 테두리 W로 설정
            else dungeon[i][j] = 'R'; // 나머지 길
        }
    }

    dungeon[0][size/2] = 'E';
    //draw Map
    clearScreen();
    printf(" 던전 %d층: %dx%d", floor, size - 2, size - 2);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            gotoxy(INDENT + (j * 2), GAP + i);
            if (dungeon[i][j] == 'W'){
                printf("□ ");
            } else if (dungeon[i][j] == 'E') {
                printf("● ");
            }
        }
    }

    return dungeon;
}

void MoveDungeon(char **map, int size){
    int locv, loch;
    locv = 0;
    loch = size/2;
    locv++;
    gotoxy((loch*2) + INDENT, locv + GAP);
    printf("● ");
    return;
}