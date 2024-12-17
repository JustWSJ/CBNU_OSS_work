#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "battle.h"
#include "inventory.h"

// 공격 함수 (Character vs Monster)
void attackCharacterToMonster(Character *attacker, Monster *defender) {
    int damage = (attacker->strength * 2) - (defender->M_def / 2);
    if (damage < 0) damage = 0;

    printf("%s이(가) %s를 공격합니다!\n", attacker->name, defender->name);

    defender->M_hp -= damage;
    if (defender->M_hp < 0) defender->M_hp = 0;

    printf("%s이(가) %d 데미지를 입혔습니다! (남은 체력: %d)\n", 
           attacker->name, damage, defender->M_hp);
}

// 공격 함수 (Monster vs Character)
void attackMonsterToCharacter(Monster *attacker, Character *defender) {
    int damage = (attacker->M_atk * 2) - (defender->health / 2);
    if (damage < 0) damage = 0;

    printf("%s이(가) %s를 공격합니다!\n", attacker->name, defender->name);

    defender->health -= damage;
    if (defender->cur_health < 0) defender->cur_health = 0;

    printf("%s이(가) %d 데미지를 입혔습니다! (남은 체력: %d)\n", 
           attacker->name, damage, defender->cur_health);
}


// 도망 함수
int escape(Character *player, Monster *enemy) {
    int baseAgility = player->agility; // 플레이어의 현재 민첩성
    int randomRoll = (rand() % 30) + 1; // 1~30 사이의 랜덤 숫자
    int escapeValue = baseAgility + randomRoll; // 민첩성 + 랜덤 값

    printf("민첩성: %d, 랜덤 값: %d -> 도망 시도 값: %d\n", baseAgility, randomRoll, escapeValue);

    if (escapeValue >= 30) { // 도망 시도 값이 30 이상일 때 성공
        printf("성공적으로 도망쳤습니다!\n");
        return 1; // 도망 성공
    } else {
        printf("도망에 실패했습니다...\n");
        return 0; // 도망 실패
    }
}


// 전투 함수
void battle(Character *player, Monster *enemy) {
    while (player->health > 0 && enemy->M_hp > 0) {
        // 상태 표시
        printf("\n==== 전투 상황 ====\n");
        displayStats(player);
        printf("\n%s의 상태: 체력: %d\n", enemy->name, enemy->M_hp);

        // 플레이어의 턴
        printf("\n행동을 선택하세요:\n");
        printf("1. 공격  2. 도망  3. 인벤토리\n");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {  // 공격
            attackCharacterToMonster(player, enemy);
        } else if (choice == 2) {  // 도망
            if (escape(player, enemy)) return;
        } else if (choice == 3) {  // 인벤토리 사용
            useItem(player);
        } else {
            printf("잘못된 선택입니다.\n");
        }

        // 몬스터의 턴 (몬스터가 살아있을 때만 공격)
        if (enemy->M_hp > 0) {
            attackMonsterToCharacter(enemy, player);
        }
    }

    // 전투 결과
    if (player->health <= 0) {
        printf("\n플레이어가 패배했습니다... 게임 종료.\n");
    } else {
        printf("\n%s를 물리쳤습니다!\n", enemy->name);
    }
}

// 상태 표시 함수
void displayStats(Character *character) {
    printf("%s의 상태:\n", character->name);
    printf("체력: %d/%d | 힘: %d | 민첩: %d | 운: %d\n", 
           character->cur_health, character->max_health, character->strength, character->agility, character->luck);
}
