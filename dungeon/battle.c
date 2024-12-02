#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "battle.h"

// 공격 함수
void attack(Character *attacker, Character *defender) {
    if (dodge(attacker, defender)) {
        printf("%s이(가) 공격을 회피했습니다!\n", defender->name);
        return;
    }

    int damage = (attacker->strength * 2) - (defender->agility / 2);
    if (damage < 0) damage = 0;

    // 치명타 계산
    if (rand() % 100 < attacker->luck) {
        damage *= 2;
        printf("치명타! ");
    }

    defender->health -= damage;
    printf("%s이(가) %s에게 %d 데미지를 입혔습니다! (남은 체력: %d)\n",
           attacker->name, defender->name, damage, defender->health);
}

// 도망 함수
int escape(Character *player, Character *enemy) {
    int escapeChance = (player->agility * 100) / (enemy->agility + 50);
    int randomRoll = rand() % 100;
    printf("도망 확률: %d%%, 결과: %d\n", escapeChance, randomRoll);
    if (randomRoll < escapeChance) {
        printf("성공적으로 도망쳤습니다!\n");
        return 1; // 도망 성공
    } else {
        printf("도망에 실패했습니다!\n");
        return 0; // 도망 실패
    }
}

// 회피 함수
int dodge(Character *attacker, Character *defender) {
    int dodgeChance = defender->agility - (attacker->agility / 2);
    if (dodgeChance < 0) dodgeChance = 0;
    int randomRoll = rand() % 100;
    return randomRoll < dodgeChance;
}

// 아이템 사용 함수
void useItem(Character *player) {
    printf("사용할 아이템을 선택하세요:\n");
    printf("1. 체력 포션 (+20 HP)\n");
    printf("2. 공격력 증가 포션 (+5 Strength)\n");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        player->health += 20;
        printf("체력이 회복되었습니다! (현재 체력: %d)\n", player->health);
    } else if (choice == 2) {
        player->strength += 5;
        printf("공격력이 증가했습니다! (현재 공격력: %d)\n", player->strength);
    }
}

// 상태 표시 함수
void displayStats(Character *character) {
    printf("\n%s의 상태:\n", character->name);
    printf("Health: %d, Strength: %d, Agility: %d, Intelligence: %d, Sensory: %d, Luck: %d\n",
           character->health, character->strength, character->agility,
           character->intelligence, character->sensory, character->luck);
}

// 전투 함수
void battle(Character *player, Monster *enemy) {
    int enamy_hp = enemy->M_hp; // 적 체력을 지역 변수로 복사
    while (player->health > 0 && enamy_hp > 0) {
        displayStats(player);

        printf("\n행동을 선택하세요:\n");
        printf("1. 전투  2. 도망  3. 인벤토리\n");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) { // 전투
            int damage = (player->strength * 2) - (enemy->M_def);
            if (damage < 0) damage = 0;

            enamy_hp -= damage; // 적 체력을 지역 변수에서 수정
            if (enamy_hp < 0) enamy_hp = 0;

            enemy->M_hp = enamy_hp; // 수정된 체력을 실제 구조체에 반영
            printf("%s가 %s에게 %d의 피해를 입혔습니다! (적 남은 체력: %d)\n",
                   player->name, enemy->name, damage, enemy->M_hp);

            if (enemy->M_hp > 0) {
                monsterAttack(enemy, player);
            }
        } else if (choice == 2) { // 도망
            if (escape(player, enemy)) return;
        } else if (choice == 3) { // 인벤토리
            useItem(player);
        } else {
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }

        if (player->health <= 0) {
            printf("\n플레이어가 쓰러졌습니다. 게임 오버!\n");
        } else if (enemy->M_hp <= 0) {
            printf("\n적을 물리쳤습니다!\n");
        }
    }
}
