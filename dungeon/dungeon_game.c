#include <stdio.h>
#include <stdlib.h>
#include "Character.h"
#include "console_util.h"
#include "menu.h"
//#include "dungeon.h"
#include "key_input.h"
//#include "battle.h"

int mainMenu(void);
void InitializeSystem(void);

int main() {
    InitializeSystem();
    Character *player = getPlayer();
    int selectedOption = mainMenu(); // 메인 메뉴 표시 및 선택값 반환
    //  select newgame
    if (selectedOption == 1) {
        showStatusAllocation();
        clearScreen();

        printf("%d %d %d %d %d %d\n", player->health, player->strength, player->agility, player->intelligence, player->sensory, player->luck);
        printf("설정한 스탯 저장하고 마을 화면 넘어가기.\nPress Enter.\n"); //여기가 while문 0층이 되어야함.
        wait(); // 지우기
        //Dungeon();
        
        clearScreen();
        printf("test complete: \n");
    }
    //  select loadgame
    else if (selectedOption == 2) {
        // Load Game 처리
        printf("Load Game\n");
    }
    //  select exit
    else if (selectedOption == 3) {
        exit(0);
    }
    pause;
    return 0;
}

void InitializeSystem(void){
    SetConsoleOutputCP(CP_UTF8); // 콘솔 출력 코드 페이지를 UTF-8로 설정
    CursorView(0);                // 커서 숨기기
    system("COLOR 0F");           // 배경: 검정, 글자색: 흰색
    system("mode con: cols=52 lines=30");       // 콘솔 크기 설정
    system("title Dungeon Game"); // 콘솔 창 제목 설정
}