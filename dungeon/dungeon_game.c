#include <stdio.h>
#include <stdlib.h>
#include "console_util.h"
#include "menu.h"

int mainMenu(void);
void InitializeSystem(void);

int main() {
    InitializeSystem();
    int selectedOption = mainMenu(); // 메인 메뉴 표시 및 선택값 반환
    gotoxy(17, 7);
    if (selectedOption == 1) {
        showStatusAllocation();  // 새 게임
        //printf("New Game\n");
    } else if (selectedOption == 2) {
        // Load Game 처리
        printf("Load Game\n");
    } else if (selectedOption == 3) {
        exit(0);  // 종료
    }
    pause;                    
    return 0;
}

void InitializeSystem(void){
    CursorView(0);                // 커서 숨기기
    system("COLOR 0F");           // 배경: 검정, 글자색: 흰색
    system("mode con: cols=52 lines=15");       // 콘솔 크기 설정
    system("title Zombie Survival - Main Menu"); // 콘솔 창 제목 설정
}