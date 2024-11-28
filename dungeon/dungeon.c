#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "console_util.h"
#include "key_input.h"

#define DUNGEON_SIZE_INCREASE_STEP 5  // 던전 크기 증가 값
#define LEVEL_INCREASE_STEP 5  // 던전 크기 증가 주기 (5계층마다)

#include <stdio.h>
#include <stdlib.h>
#include "console_util.h"
#include "key_input.h"

#define MENU_COUNT 10       // 메뉴 항목 개수
#define INDENT 1            // 메뉴의 왼쪽 들여쓰기
#define GAP 1


int SelectFloor(){
    clearScreen();
    const int floors[MENU_COUNT] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90}; // 층수 배열
    int selected = 0;       // 선택된 항목 인덱스
    int updated = 1;        // 화면 갱신 여부 (1: 갱신 필요, 0: 갱신 불필요)


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
            return choice; // 선택된 메뉴 반환 (0: 다음 층, 1: 마을로 돌아가기)
        }
    } 
}
