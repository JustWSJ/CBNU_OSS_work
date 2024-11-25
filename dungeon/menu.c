#include <stdio.h>
#include <stdlib.h>  // exit 함수와 system 함수 사용을 위해 추가
#include <windows.h> // Sleep 함수 사용을 위해 추가
#include "menu.h"
#include "key_input.h"
#include "console_util.h"  // clearScreen 함수 선언을 포함한 헤더 파일
#include "save.h"
#include "dungeon.h"

void showMainMenu() {
    int choice = 0;

    while (1) {
        clearScreen();
        printf("******** Dungeon Game ********\n");
        printf("1. New Game\n");
        printf("2. Load Game\n");
        printf("3. Exit\n");

        switch (choice) {
            case 0: printf("> New Game\n"); break;
            case 1: printf("> Load Game\n"); break;
            case 2: printf("> Exit\n"); break;
            default: choice = 0; break;
        }

        if (isKeyPressed(KEY_UP)) {
            choice--;
            if (choice < 0) choice = 2;
            Sleep(200);
        }
        if (isKeyPressed(KEY_DOWN)) {
            choice++;
            if (choice > 2) choice = 0;
            Sleep(200);
        }

        if (isKeyPressed(KEY_SPACE)) {
            if (choice == 0) {
                showStatusAllocation();  // 새 게임
                break;
            } else if (choice == 1) {
                // Load Game 처리
                break;
            } else if (choice == 2) {
                exit(0);  // 종료
            }
        }
        Sleep(100);
    }
}

void showStatusAllocation() {
    int health = 5, strength = 5, agility = 5, intelligence = 5, sensory = 5, luck = 5;
    int points = 15;
    int selectedStat = 0;  // 현재 선택된 스테이터스(0: health, 1: strength, ..., 5: luck)
    int updated = 1;  // 화면 갱신 여부를 추적하는 변수

    while (1) {
        if (updated) {
            clearScreen();
            printf("Character Status Allocation\n");
            printf("Remaining points: %d\n", points);
            printf("\n");

            for (int i = 0; i < 6; i++) {
                if (i == selectedStat) {
                    printf("> ");
                } else {
                    printf("  ");
                }

                switch (i) {
                    case 0: printf("Health: %d\n", health); break;
                    case 1: printf("Strength: %d\n", strength); break;
                    case 2: printf("Agility: %d\n", agility); break;
                    case 3: printf("Intelligence: %d\n", intelligence); break;
                    case 4: printf("Sensory: %d\n", sensory); break;
                    case 5: printf("Luck: %d\n", luck); break;
                }
            }

            printf("Press Space to finalize allocation.\n");
            updated = 0;
        }

        if (isKeyPressed(KEY_UP)) {
            selectedStat--;
            if (selectedStat < 0) selectedStat = 5;
            updated = 1;
            Sleep(200);
        }
        if (isKeyPressed(KEY_DOWN)) {
            selectedStat++;
            if (selectedStat > 5) selectedStat = 0;
            updated = 1;
            Sleep(200);
        }

        if (isKeyPressed(KEY_LEFT) && points > 0) {
            switch (selectedStat) {
                case 0: health--; points++; break;
                case 1: strength--; points++; break;
                case 2: agility--; points++; break;
                case 3: intelligence--; points++; break;
                case 4: sensory--; points++; break;
                case 5: luck--; points++; break;
            }
            updated = 1;
            Sleep(200);
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
            Sleep(200);
        }

        if (points <= 0 && isKeyPressed(KEY_SPACE)) {
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
                    Sleep(200);
                }
                if (isKeyPressed(KEY_DOWN)) {
                    choice++;
                    if (choice > 1) choice = 0;
                    Sleep(200);
                }

                if (isKeyPressed(KEY_SPACE)) {
                    if (choice == 0) {
                        srand(time(NULL));

                        char dungeon[MAX_DUNGEON_SIZE][MAX_DUNGEON_SIZE];  // 최대 던전 크기 100x100
                        int level = 1;  // 첫 번째 레벨부터 시작
                        generateDungeonForLevel(level, dungeon);

                        static int saveCounter = 1;
                        char filename[50];
                        snprintf(filename, sizeof(filename), "save/save_%03d.txt", saveCounter++);
                        saveDungeonAndStats(filename, health, strength, agility, intelligence, sensory, luck, dungeon[][]);

                        printf("Dungeon generated and saved.\n");
                        Sleep(1000);
                        return;
                    } else if (choice == 1) {
                        printf("Status allocation reset.\n");
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
