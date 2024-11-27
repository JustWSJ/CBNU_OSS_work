#include <stdio.h>
#include "console_util.h"
#include "key_input.h"
#define MENU_COUNT 3
#define INDENT 15

int mainMenu(void) {
    int selected = 0; // 현재 선택된 메뉴 (0부터 시작)
    char* menu[MENU_COUNT] = {
        "1. New Game",
        "2. Load Game",
        "3. Exit"
    };

    // 고정된 화면 출력 (한 번만 출력) 19v7v4v19
    printf("\n");
    printf("=================== Dungeon Game ===================\n");
    printf("\n");

    for (int i = 0; i < MENU_COUNT; i++) {
        gotoxy(INDENT, 3 + i);
        printf("  %s", menu[i]);
    }

    while (1) {
        for (int i = 0; i < MENU_COUNT; i++) {
            gotoxy(INDENT, 3 + i);
            if (i == selected) {
                SetColor(0x0E); // 선택된 메뉴: 잠시 노란색으로
                printf("> %s", menu[i]);
                SetColor(0x0F); // 다시 기본 색상 흰색으로 돌아가기
            }
            else {
                printf("  %s", menu[i]);
            }
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selected = (selected - 1 + MENU_COUNT) % MENU_COUNT;
            Sleep(150);
        }
        else if (isKeyPressed(KEY_DOWN)) {
            selected = (selected + 1) % MENU_COUNT;
            Sleep(150);
        }
        else if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
            return selected + 1; // 선택된 메뉴 반환 (1부터 시작)
        }
    }
}

void showStatusAllocation() {
    int health = 5, strength = 5, agility = 5, intelligence = 5, sensory = 5, luck = 5;
    int points = 15;
    int selectedStat = 0;  // 현재 선택된 스테이터스(0: health, 1: strength, ..., 5: luck)
    int updated = 1;  // 화면 갱신 여부를 추적하는 변수
    int baseY = 3;
    char stat_name[6][15] = {"Health", "Strength", "Agility", "Intelligence", "Sensory", "Luck"};
    clearScreen();
    printf(" Character Status Allocation\n");
    printf(" Remaining points: %d      \n\n", points);

    int stat_idx[6] = {health, strength, agility, intelligence, sensory, luck}; 
    for (int i = 0; i < 6; i++) {
        gotoxy(3, baseY + i);
        printf("%s: %d   ", stat_name[i], stat_idx[i]);
    }

    gotoxy(1, baseY + 7);                               // 마지막 스탯 아래로 이동
    printf("Press Space to finalize allocation.     "); // 기존 내용 덮어쓰기

    while (1) {
        if (updated) {
            int stat_idx[6] = {health, strength, agility, intelligence, sensory, luck};
            gotoxy(1,1);
            printf("Remaining points: %d      \n\n", points);

            for (int i = 0; i < 6; i++) {
                gotoxy(1, baseY + i); // 각 스탯의 줄로 이동
                if (i == selectedStat) {
                    SetColor(0x0E);
                    printf("> %s: %d   ", stat_name[i], stat_idx[i]);
                    SetColor(0x0F);
                } else {
                    printf("  %s: %d   ", stat_name[i], stat_idx[i]);
                }
            }
            // 고정된 하단 메시지
            updated = 0;
        }


        if (isKeyPressed(KEY_UP)) {
            selectedStat--;
            if (selectedStat < 0) selectedStat = 5;
            updated = 1;
            Sleep(150);
        }
        if (isKeyPressed(KEY_DOWN)) {
            selectedStat++;
            if (selectedStat > 5) selectedStat = 0;
            updated = 1;
            Sleep(150);
        }

        // if 조건에 각 스탯의 최소치를 1로 지정함. 이후에 0을 상수로 조정 가능
        if (isKeyPressed(KEY_LEFT) && points >= 0 ) {
            if (selectedStat == 0 && health > 0 + 1) {
                health--; points++; updated = 1;
            } else if (selectedStat == 1 && strength > 0 + 1) {
                strength--; points++; updated = 1;
            } else if (selectedStat == 2 && agility > 0 + 1) {
                agility--; points++; updated = 1;
            } else if (selectedStat == 3 && intelligence > 0 + 1) {
                intelligence--; points++; updated = 1;
            } else if (selectedStat == 4 && sensory > 0 + 1) {
                sensory--; points++; updated = 1;
            } else if (selectedStat == 5 && luck > 0 + 1) {
                luck--; points++; updated = 1;
            }
            Sleep(150);
        }
        if (isKeyPressed(KEY_RIGHT) && points > 0) {
            switch (selectedStat) {
                case 0: health++; points--; break;
                case 1: strength++; points--; break;
                case 2: agility++; points--; break;
                case 3: intelligence++; points--; break;
                case 4: sensory++; points--; break;
                case 5: luck++; points--; break;
            }
            updated = 1;
            Sleep(150);
        }

        if (points <= 0 && (isKeyPressed(KEY_SPACE)||isKeyPressed(KEY_ENTER))) {
            int choice = 0;
            clearScreen();
            printf(" Apply status allocation?\n");
            printf(" > 1. Yes\n");
            printf("   2. No\n");
            while (1) {
                if (choice == 0) {
                    gotoxy(1, choice + 1);
                    SetColor(0x0E);
                    printf("> 1. Yes\n");
                    SetColor(0x0F);
                    printf("   2. No\n");
                } else if (choice == 1) {
                    gotoxy(1, choice + 1);
                    printf("  1. Yes\n");
                    SetColor(0x0E);
                    printf(" > 2. No\n");
                    SetColor(0x0F);
                }

                if (isKeyPressed(KEY_UP)) {
                    choice--;
                    if (choice < 0) choice = 1;
                    Sleep(150);
                }
                if (isKeyPressed(KEY_DOWN)) {
                    choice++;
                    if (choice > 1) choice = 0;
                    Sleep(150);
                }

                if (isKeyPressed(KEY_SPACE)||isKeyPressed(KEY_ENTER)) {
                    if (choice == 0) {
                        printf(" Dungeon generated and saved.\n");
                        Sleep(1000);
                        return;
                    } else if (choice == 1) {
                        printf(" Status allocation reset.\n");
                        Sleep(1000);
                        return;
                    } else {
                        printf(" choice error\n");
                        Sleep(1000);
                        return;
                    }
                }
                Sleep(100);
            }
        }
        Sleep(100);
    }
}