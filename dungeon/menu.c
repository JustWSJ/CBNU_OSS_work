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
    clearScreen();
    printf("             Character Status Allocation\n");
    while (1) {
        if (updated) {
            gotoxy(0,1);
            printf("             Remaining points: %d\n\n", points);

            int baseY = 3;

            for (int i = 0; i < 6; i++) {
                gotoxy(15, baseY + i); // 각 스탯의 줄로 이동
                if (i == selectedStat) {
                    printf("> ");
                } else {
                    printf("  ");
                }

                switch (i) {
                    case 0:
                        printf("Health: %d   ", health);
                        break;
                    case 1:
                        printf("Strength: %d   ", strength);
                        break;
                    case 2:
                        printf("Agility: %d   ", agility);
                        break;
                    case 3:
                        printf("Intelligence: %d   ", intelligence);
                        break;
                    case 4:
                        printf("Sensory: %d   ", sensory);
                        break;
                    case 5:
                        printf("Luck: %d   ", luck);
                        break;
                }
            }
            // 고정된 하단 메시지
            gotoxy(9, baseY + 7);                               // 마지막 스탯 아래로 이동
            printf("Press Space to finalize allocation.     "); // 기존 내용 덮어쓰기
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

        if (isKeyPressed(KEY_LEFT) && points >= 0) {
            switch (selectedStat) {
                case 0: health--; points++; break;
                case 1: strength--; points++; break;
                case 2: agility--; points++; break;
                case 3: intelligence--; points++; break;
                case 4: sensory--; points++; break;
                case 5: luck--; points++; break;
            }
            updated = 1;
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
            while (1) {
                clearScreen();
                printf("Apply status allocation?\n");
                printf("1. Yes\n");
                printf("2. No\n");

                switch (choice) {
                    case 0: printf("> Yes\n"); break;
                    case 1: printf("> No\n"); break;
                    default: choice = 0; break;
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
                        //srand(time(NULL));

                        //char dungeon[MAX_DUNGEON_SIZE][MAX_DUNGEON_SIZE];  // 최대 던전 크기 100x100
                        //int level = 1;  // 첫 번째 레벨부터 시작
                        //generateDungeonForLevel(level, dungeon);

                        //static int saveCounter = 1;
                        //char filename[50];
                        //snprintf(filename, sizeof(filename), "save/save_%03d.txt", saveCounter++);
                        //saveDungeonAndStats(filename, health, strength, agility, intelligence, sensory, luck, dungeon[][]);

                        printf("Dungeon generated and saved.\n");
                        Sleep(1000);
                        return;
                    } else if (choice == 1) {
                        printf("Status allocation reset.\n");
                        Sleep(1000);
                        return;
                    } else {
                        printf("choice error\n");
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