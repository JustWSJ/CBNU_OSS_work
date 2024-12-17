#include <stdio.h>
#include <stdlib.h>
#include "Character.h"
#include "console_util.h"
#include "menu.h"
#include "saveLoad.h"
#include "dungeon.h"
#include "key_input.h"
#include "battle.h"
#include "hotel.h"
#include "inventory.h"


int mainMenu(void);
void InitializeSystem(void);
void StartingOption(int, Character *);

void villageMenu(Character *player) {
    int selected = 0; // 메뉴 선택 초기값
    char* villageOptions[2] = { "1. 호텔 방문", "2. 던전 입장" };

    while (1) {
        // 메뉴 출력
        gotoxy(0, 20); // 20번째 줄부터 시작
        printf("==================== 마을 ====================\n");
        for (int i = 0; i < 2; i++) {
            gotoxy(2, 22 + i); // 메뉴 위치
            printf("                                     "); // 기존 글씨 지우기
            gotoxy(2, 22 + i);
            if (i == selected) {
                SetColor(0x0E); // 선택 항목은 노란색
                printf("> %s", villageOptions[i]);
                SetColor(0x0F); // 원래 색상
            } else {
                printf("  %s", villageOptions[i]);
            }
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selected = (selected - 1 + 2) % 2; // 위로 이동
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selected = (selected + 1) % 2; // 아래로 이동
            Sleep(150);
        } else if (isKeyPressed(KEY_ENTER)) {
            if (selected == 0) { // 호텔 방문 선택
                gotoxy(0, 25);
                printf("호텔을 방문합니다...\n");
                visitHotel(player); // 호텔 기능 호출
            } else if (selected == 1) { // 던전 입장 선택
                gotoxy(0, 25);
                printf("던전에 입장합니다...\n");
                Dungeon(); // 던전 입장
            }
            break; // 메뉴 반복 종료 후 마을 메인으로 돌아감
        }
    }
}

int main() {
    InitializeSystem();
    Character *player = getPlayer();
    int selectedOption = mainMenu(); // 메인 메뉴 표시 및 선택값 반환
    StartingOption(selectedOption, player);
   
    while (1) { // 마을 루프
        villageMenu(player); // 마을 메뉴 표시 및 선택 처리
        saveStatus(player); // 상태 저장
    }

    clearScreen();
    printf("test complete: \n");

    pause;
    return 0;
}

void InitializeSystem(void){
    SetConsoleOutputCP(CP_UTF8); // 콘솔 출력 코드 페이지를 UTF-8로 설정
    CursorView(0);                // 커서 숨기기
    system("COLOR 0F");           // 배경: 검정, 글자색: 흰색
    system("mode con: cols=52 lines=45");       // 콘솔 크기 설정
    system("title Dungeon Game"); // 콘솔 창 제목 설정
    initializeInventory();
}

void StartingOption(int selectedOption, Character *player){
 //  select newgame
    if (selectedOption == 1) {
        for (int i = 0; i <= 100; i++){
            deleteDungeonFiles1(i);
            deleteDungeonFiles2(i);
        }
        if (remove("save\\save_000.txt") == 0) {
            ;
        } else {
            ;
        }
        showStatusAllocation();
        saveStatus(player);
        clearScreen();
    }
    //  select loadgame
    else if (selectedOption == 2) {
        // Load Game 처리
        printf("\n\nLoading Game...\n");
        wait(); // 지우기
        if (loadStatus(player) != -1){
            printf("Found savefile.\n");
            //테스트용
            printf("%d %d %d %d %d %d\n", player->health, player->strength, player->agility, player->intelligence, player->sensory, player->luck);
        } else {
            printf("Can't find savefile.\nStarting a new game. ▼\n");
            wait();
            showStatusAllocation();
            saveStatus(player);
            clearScreen();
        }
    }
    //  select exit
    else if (selectedOption == 3) {
        exit(0);
    }
}