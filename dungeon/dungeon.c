#include <stdio.h>
#include <stdlib.h>
#include "console_util.h"
#include "key_input.h"
#include "dungeon.h"

#define MENU_COUNT 10       // 메뉴 항목 개수
#define INDENT 1            // 메뉴의 왼쪽 들여쓰기
#define GAP 1

void Dungeon(){
    int floor = SelectFloor();
    int option = DungeonEntrance(floor);
    while (1){
        if (option==0) {
            floor++;
            DungeonAdventure(floor);
            if (floor == 100) {
                clearScreen();
                printf("Dungeon Clear!\n");
                wait();
                exit(0);
            } else if (isClear(floor)) option = DungeonEntrance(floor);
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
    int **map = CreateDungeon(floor);

    return;
}

int SelectFloor(){
    clearScreen();
    const int floors[MENU_COUNT] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90}; // 층수 배열
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
                    SetColor(0x0E); // 선택된 메뉴: 노란색
                    printf("> %s", options[i]);
                    SetColor(0x0F); // 기본 색상 복구
                } else {
                    printf("  %s", options[i]);
                }
            }
            updated = 0; // 출력 후 갱신 플래그 해제
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            choice = (choice - 1 + menu_count) % menu_count; // 위로 이동
            updated = 1; // 선택 항목 변경, 화면 갱신 필요
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            choice = (choice + 1) % menu_count; // 아래로 이동
            updated = 1; // 선택 항목 변경, 화면 갱신 필요
            Sleep(150);
        } else if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
            Sleep(150);
            clearScreen();
            return choice; // 선택된 메뉴 반환 (0: 다음 층, 1: 마을로 돌아가기)
        }
    } 
}

int isClear(int floor){
    // 나중에 조건 바꿔야함
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
    }else {
        // 일반 던전 처리
        return (floor / 5) + 5;
    }
}

int** CreateDungeon(int floor) {
    int size = DungeonSize(floor);
    
    if (size == -1) {
        printf("Boss floor! No dungeon grid created.\n");
        return NULL;
    } else if (size == -2) {
        printf("already cleared floor.\n");
        return NULL;
    }

    //size *= size; // 이차원 배열의 크기는 DungeonSize의 결과값을 제곱한 값

    // 이차원 배열 동적 할당
    int** dungeon = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        dungeon[i] = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            dungeon[i][j] = 0; // 기본값 초기화 (0으로 설정)
        }
    }

    printf("Dungeon of size %dx%d created for floor %d.\n", size, size, floor);
    wait(); // 지우기
    return dungeon;
}

void DrawDungeon(int dungeonSize){
     for (int i = 0; i < dungeonSize; i++) {
        for (int j = 0; j < dungeonSize; j++) {
            gotoxy(j, i); // x 좌표는 칸당 두 칸씩 띄움
            printf("□");
        }
    }
}