#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "console_util.h"
#include "key_input.h"
#include "battle.h"
#include "inventory.h"//
#define INDENT 1
#define GAP 20

// 공격 함수 (Character vs Monster)
void attackCharacterToMonster(Character *attacker, Monster *defender, int * enemy_cur_hp) {
    int damage = (attacker->strength * 2) - (defender->M_def / 2);
    if (damage < 0) damage = 0;

    printf("%s이(가) %s를 공격합니다!                        \n", attacker->name, defender->name);

    *enemy_cur_hp -= damage;
    if (*enemy_cur_hp < 0) *enemy_cur_hp = 0;

    printf("%s이(가) %d 데미지를 입혔습니다!                        \n(%s의 남은 체력: %d)                      \n", attacker->name, damage, defender->name, *enemy_cur_hp);
}

// 공격 함수 (Monster vs Character)
void attackMonsterToCharacter(Monster *attacker, Character *defender) {
    int damage = (attacker->M_atk * 2) - (defender->health / 2);
    if (damage < 0) damage = 0;

    printf("%s이(가) %s를 공격합니다!                        \n", attacker->name, defender->name);

    defender->cur_health -= damage;
    if (defender->cur_health < 0) defender->cur_health = 0;

    printf("%s이(가) %d 데미지를 입혔습니다! (남은 체력: %d)                    \n", 
           attacker->name, damage, defender->cur_health);
}


// 도망 함수
int escape(Character *player, Monster *enemy) {
    int baseAgility = player->agility; // 플레이어의 현재 민첩성
    int randomRoll = (rand() % 30) + 1; // 1~30 사이의 랜덤 숫자
    int escapeValue = baseAgility + randomRoll; // 민첩성 + 랜덤 값

    printf("민첩성: %d, 랜덤 값: %d -> 도망 시도 값: %d                     \n", baseAgility, randomRoll, escapeValue);

    if (escapeValue >= 30) { // 도망 시도 값이 30 이상일 때 성공
        printf("성공적으로 도망쳤습니다!              \n");
        return 1; // 도망 성공
    } else {
        printf("도망에 실패했습니다...                \n");
        return 0; // 도망 실패
    }
}

void battle(Character *player, Monster *enemy) {
    int enemy_cur_hp = enemy->M_hp;
    int selected = 0; // 메뉴 선택 초기값
    char* menu[3] = { "1. 공격", "2. 도망", "3. 인벤토리" };

    while (player->health > 0 && enemy_cur_hp > 0) {
        // 상태 표시 (20번째 줄 아래로 고정)
        gotoxy(0, 20);
        printf("==================== 전투 상황 ====================\n");

        // 플레이어 상태 표시 (왼쪽 20번째 줄 아래)
        gotoxy(2, 22);
        printf("플레이어 상태:                          ");
        displayStats(player);

        // 몬스터 상태 표시 (오른쪽)
        gotoxy(35, 22);
        printf("%s 상태: 체력: %d            ", enemy->name, enemy_cur_hp);

        // 행동 선택 메뉴 출력 (아래쪽 30번째 줄부터)
        gotoxy(0, 30);
        printf("========== 행동 선택 ==========\n");
        for (int i = 0; i < 3; i++) {
            gotoxy(2, 32 + i); // 메뉴 출력 위치 (고정)
            printf("                              "); // 기존 글씨 지우기
            gotoxy(2, 32 + i);
            if (i == selected) {
                SetColor(0x0E); // 노란색 강조
                printf("> %s", menu[i]);
                SetColor(0x0F); // 기본 색상
            } else {
                printf("  %s", menu[i]);
            }
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selected = (selected - 1 + 3) % 3; // 위로 이동
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selected = (selected + 1) % 3; // 아래로 이동
            Sleep(150);
        } else if (isKeyPressed(KEY_ENTER)) {
            break; // 선택 확정
        }
    }

    // 선택된 행동 실행 (20번째 줄 하단에 표시)
    gotoxy(0, 37);
    printf("                                             "); // 기존 내용 지우기
    gotoxy(0, 37);
    if (selected == 0) { // 공격
        attackCharacterToMonster(player, enemy, &enemy_cur_hp);
    } else if (selected == 1) { // 도망
        if (escape(player, enemy)) return;
    } else if (selected == 2) { // 인벤토리
        showInventory();  
        //printf("인벤토리 기능은 아직 구현되지 않았습니다.\n");
    }

    // 몬스터의 턴
    if (enemy_cur_hp > 0) {
        gotoxy(0, 39);
        attackMonsterToCharacter(enemy, player);
    }

    // 전투 결과 출력 (20번째 줄 아래)
    gotoxy(0, 42);
    if (player->health <= 0) {
        printf("플레이어가 패배했습니다... 게임 종료.\n");
    } else {
        printf("%s를 물리쳤습니다!\n", enemy->name);
    }
}

// 상태 표시 함수
void displayStats(Character *character) {
    printf(" %s의 상태:\n", character->name);
    printf(" 체력: %d/%d               \n 힘: %d               \n 민첩: %d                     \n 운: %d                      \n", 
           character->cur_health, character->max_health, character->strength, character->agility, character->luck);
}
