#include <stdio.h>
#include "character.h"
#include "console_util.h"
#include "key_input.h"

// 캐릭터 스탯 이름
const char *stat_name[6] = {"Health", "Strength", "Agility", "Intelligence", "Sensory", "Luck"};

// 스탯 ID에 따라 값을 업데이트
void updateStat(Character *player, int statID, int delta) {
    switch (statID) {
        case 0: player->health += delta; break;
        case 1: player->strength += delta; break;
        case 2: player->agility += delta; break;
        case 3: player->intelligence += delta; break;
        case 4: player->sensory += delta; break;
        case 5: player->luck += delta; break;
        case 6: player->max_health = player->health * 20; break;
    }
}

// 현재 스탯 값을 가져오기
int getStatValue(Character *player, int statID) {
    switch (statID) {
        case 0: return player->health;
        case 1: return player->strength;
        case 2: return player->agility;
        case 3: return player->intelligence;
        case 4: return player->sensory;
        case 5: return player->luck;
        case 6: return player->max_health;
        default: return 0;
    }
}

// 스탯 배분 함수
void showStatusAllocation(Character *player) {
    int points = 15;                 // 배분 가능한 포인트
    int selectedStat = 0;            // 현재 선택된 스탯 (0: Health, ..., 5: Luck)
    int updated = 1;                 // 화면 갱신 여부
    int baseY = 3;                   // UI 출력 시작 위치

    clearScreen();
    printf(" Character Status Allocation\n");
    gotoxy(1, baseY + 7);
    printf("Press Space to finalize allocation.     ");

    while (1) {
        // 화면 갱신
        if (updated) {
            gotoxy(1, 1);
            printf("Remaining points: %d      \n\n", points);

            for (int i = 0; i < 6; i++) {
                gotoxy(1, baseY + i); // 각 스탯 위치로 이동
                if (i == selectedStat) {
                    SetColor(0x0E); // 강조 표시
                    printf("> %s: %d   ", stat_name[i], getStatValue(player, i));
                    SetColor(0x0F);
                } else {
                    printf("  %s: %d   ", stat_name[i], getStatValue(player, i));
                }
            }
            updated = 0;
        }

        // 사용자 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selectedStat = (selectedStat - 1 + 6) % 6; // 이전 스탯 선택
            updated = 1;
            Sleep(150);
        }
        if (isKeyPressed(KEY_DOWN)) {
            selectedStat = (selectedStat + 1) % 6; // 다음 스탯 선택
            updated = 1;
            Sleep(150);
        }
        if (isKeyPressed(KEY_LEFT)) {
            if (getStatValue(player, selectedStat) > 5) { // 최소값 5로 제한
                updateStat(player, selectedStat, -1); // 스탯 감소
                if (selectedStat == 0) { // Health 감소 시 max_health 업데이트
                    player->max_health = getStatValue(player, selectedStat) * 20;
                }
                points++;
                updated = 1;
            }
            Sleep(150);
        }
        if (isKeyPressed(KEY_RIGHT)) {
            if (points > 0) {
                updateStat(player, selectedStat, 1); // 스탯 증가
                if (selectedStat == 0) { // Health 증가 시 max_health 업데이트
                    player->max_health = getStatValue(player, selectedStat) * 20;
                }
                points--;
                updated = 1;
            }
            Sleep(150);
        }

        // 완료 조건
        if (points == 0 && (isKeyPressed(KEY_SPACE) || isKeyPressed(KEY_ENTER))) {
            clearScreen();
            printf("Apply status allocation?\n");
            printf("  1. Yes\n");
            printf("  2. No\n");

            int choice = 0;
            while (1) {
                gotoxy(1, 3);
                if (choice == 0) {
                    SetColor(0x0E);
                    printf("> 1. Yes\n");
                    SetColor(0x0F);
                    printf("  2. No\n");
                } else {
                    printf("  1. Yes\n");
                    SetColor(0x0E);
                    printf("> 2. No\n");
                    SetColor(0x0F);
                }

                if (isKeyPressed(KEY_UP) || isKeyPressed(KEY_DOWN)) {
                    choice = 1 - choice; // 선택 전환
                    Sleep(150);
                }
                if (isKeyPressed(KEY_SPACE) || isKeyPressed(KEY_ENTER)) {
                    if (choice == 0) {
                        printf("Status allocation applied.\n");
                        wait();
                        return; // 종료
                    } else {
                        points = 15; // 포인트 초기화
                        updated = 1;
                        break;
                    }
                }
            }
        }
        Sleep(100);
    }
}
