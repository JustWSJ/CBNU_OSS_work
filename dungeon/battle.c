#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 캐릭터 구조체 정의
typedef struct {
    char name[50];
    int health;
    int strength;
    int agility;
    int intelligence;
    int sensory;
    int luck;
} Character;

// 전투 시스템 단일 함수
void battle(Character *player, Character *enemy) {
    while (player->health > 0 && enemy->health > 0) {
        printf("\n--- 전투 메뉴 ---\n");
        printf("1. 전투하기\n");
        printf("2. 도망가기\n");
        printf("3. 스킬 사용\n");
        printf("4. 인벤토리 열기\n");
        printf("선택: ");

        int choice;
        scanf("%d", &choice);

        if (choice == 1) { // 전투
            // 공격 로직
            int base_damage = (player->strength * 2) - (enemy->agility / 2);
            if (base_damage < 0) base_damage = 0;

            // 치명타 계산
            int crit_chance = player->sensory + player->luck;
            int is_crit = (rand() % 100) < crit_chance;
            if (is_crit) {
                base_damage *= 2;
                printf("치명타! ");
            }

            // 회피 계산
            int dodge_chance = enemy->agility + (enemy->luck / 2);
            if ((rand() % 100) < dodge_chance) {
                printf("%s가 공격을 회피했습니다!\n", enemy->name);
            } else {
                enemy->health -= base_damage;
                if (enemy->health < 0) enemy->health = 0;
                printf("%s가 %s에게 %d의 피해를 입혔습니다! (남은 체력: %d)\n",
                       player->name, enemy->name, base_damage, enemy->health);
            }

            if (enemy->health > 0) { // 적의 반격
                base_damage = (enemy->strength * 2) - (player->agility / 2);
                if (base_damage < 0) base_damage = 0;

                dodge_chance = player->agility + (player->luck / 2);
                if ((rand() % 100) < dodge_chance) {
                    printf("%s가 공격을 회피했습니다!\n", player->name);
                } else {
                    player->health -= base_damage;
                    if (player->health < 0) player->health = 0;
                    printf("%s가 %s에게 %d의 피해를 입혔습니다! (남은 체력: %d)\n",
                           enemy->name, player->name, base_damage, player->health);
                }
            } else {
                printf("%s를 물리쳤습니다!\n", enemy->name);
                if ((rand() % 100) < player->luck + 20) { // 희귀 아이템 이벤트
                    printf("희귀 아이템 획득! 공격력이 증가했습니다.\n");
                    player->strength += 5;
                }
                break;
            }
        } else if (choice == 2) { // 도망
            int escape_chance = (player->agility * 100) / (enemy->agility + 50);
            if ((rand() % 100) < escape_chance) {
                printf("%s가 성공적으로 도망쳤습니다!\n", player->name);
                break;
            } else {
                printf("%s가 도망에 실패했습니다!\n", player->name);
                int base_damage = (enemy->strength * 2) - (player->agility / 2);
                if (base_damage < 0) base_damage = 0;
                player->health -= base_damage;
                if (player->health < 0) player->health = 0;
                printf("%s가 %s에게 %d의 피해를 입혔습니다! (남은 체력: %d)\n",
                       enemy->name, player->name, base_damage, player->health);
            }
        } else if (choice == 3) { // 스킬 사용
            printf("스킬 사용: 적의 방어력을 감소시킵니다.\n");
            int debuff = player->intelligence / 2;
            enemy->agility -= debuff;
            if (enemy->agility < 0) enemy->agility = 0;
            printf("%s의 민첩성이 %d 감소했습니다! (현재 민첩성: %d)\n",
                   enemy->name, debuff, enemy->agility);
        } else if (choice == 4) { // 아이템 사용
            printf("아이템 사용: 체력을 회복합니다.\n");
            int heal = 20 + (player->intelligence / 2);
            player->health += heal;
            printf("%s의 체력이 %d 회복되었습니다! (현재 체력: %d)\n",
                   player->name, heal, player->health);
        } else {
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }

        if (player->health <= 0) {
            printf("플레이어가 쓰러졌습니다. 게임 오버!\n");
            break;
        }
    }
}

// 메인 함수
int main() {
    srand(time(NULL)); // 랜덤 시드 초기화

    // 플레이어와 적 초기화
    Character player = {"플레이어", 100, 20, 15, 20, 10, 10};
    Character enemy = {"적", 80, 15, 10, 5, 5, 5};

    // 전투 시작
    printf("%s와 %s의 전투가 시작됩니다!\n", player.name, enemy.name);
    printf("\n--- 적 스탯 ---\n");
    printf("체력: %d, 공격력: %d, 민첩성: %d, 지능: %d, 감각: %d, 운: %d\n\n",
           enemy.health, enemy.strength, enemy.agility, enemy.intelligence, enemy.sensory, enemy.luck);
    battle(&player, &enemy);

    return 0;
}
