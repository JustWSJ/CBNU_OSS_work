#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ======== 전역 변수 및 구조체 ========
typedef struct {
    int hp, max_hp, str, agi, men, lck, ap, sp;
} Stats;

typedef struct {
    char name[30];
    char description[150];
    Stats stats;
} Character;

typedef struct {
    int food, water, medicine, weapons, special_items;
} Resources;

typedef struct {
    char name[30];
    int hp_effect;
    int str_effect;
} Item;

// ======== 함수 선언 ========
void initializeGame();
void selectCharacter(Character *player);
void startDay(Character *player, Resources *resources, int *day, int *explored);
void explore(Character *player, Resources *resources, int *explored, int day);
void exploreSubLocation(Character *player, Resources *resources, char *location, int day);
void applyItemEffect(Character *player, Item item);
void rest(Character *player, Resources *resources, int *explored);
void displayStatus(Character *player, Resources *resources, int day);
int randomEvent(Character *player, Resources *resources, int day);
void combat(Character *player, int day);
int attemptEscape(Character *player, int day);

// ======== 메인 함수 ========
int main() {
    srand(time(NULL));
    Character player;
    Resources resources = {3, 3, 2, 1, 0}; // 초기 자원 설정
    int day = 1;

    initializeGame();
    selectCharacter(&player);

    while (day <= 7) {
        int explored = 0; // 탐험 여부 플래그
        startDay(&player, &resources, &day, &explored);

        // 하루 종료 후 탐험하지 않은 경우 체력 감소
        if (!explored) {
            printf("\n=== 탐험하지 않았습니다! 체력을 잃습니다. ===\n");
            player.stats.hp -= 10;
            if (player.stats.hp <= 0) {
                printf("탐험을 하지 않아 생존에 실패했습니다...\n");
                exit(0);
            }
            printf("남은 체력: %d/%d\n", player.stats.hp, player.stats.max_hp);
        }
    }

    printf("게임 종료! 생존 여부는 당신의 선택에 달려있었습니다.\n");
    return 0;
}

// ======== 함수 구현 ========

// 초기화 메시지
void initializeGame() {
    printf("=== 텍스트 기반 좀비 아포칼립스 생존 게임 ===\n");
    printf("7일 안에 안전 지대에 도달하세요.\n");
}

// 캐릭터 선택
void selectCharacter(Character *player) {
    int choice;
    printf("\n=== 캐릭터 선택 ===\n");
    printf("1. 방패의 수호자\n");
    printf("   전직 군인으로, 좀비 사태 초기 대피소 방어를 맡던 영웅입니다.\n");
    printf("   추가 스탯: HP +15, STR +3\n");
    printf("2. 명사수\n");
    printf("   스포츠 사격 대회 챔피언으로, 위험한 지역에서 자원을 회수하는 전문가입니다.\n");
    printf("   추가 스탯: HP +10, STR +5, AGI +5\n");
    printf("3. 행운의 탐험가\n");
    printf("   환경 과학자로 자연과 인간의 조화를 연구하던 학자입니다.\n");
    printf("   추가 스탯: HP +10, MEN +3, LCK +5\n");
    printf("캐릭터를 선택하세요 (1~3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(player->name, "방패의 수호자");
            strcpy(player->description, "좀비 사태 초기 대피소 방어를 맡던 영웅입니다.");
            player->stats = (Stats){45, 45, 8, 5, 5, 5, 0, 0};
            break;
        case 2:
            strcpy(player->name, "명사수");
            strcpy(player->description, "스포츠 사격 대회 챔피언으로, 자원 회수 전문가입니다.");
            player->stats = (Stats){40, 40, 10, 10, 5, 5, 0, 0};
            break;
        case 3:
            strcpy(player->name, "행운의 탐험가");
            strcpy(player->description, "환경 과학자로, 지혜와 운을 활용하여 생존합니다.");
            player->stats = (Stats){40, 40, 7, 8, 8, 10, 0, 0};
            break;
        default:
            printf("잘못된 입력입니다. 기본 캐릭터로 설정합니다.\n");
            strcpy(player->name, "방패의 수호자");
            strcpy(player->description, "좀비 사태 초기 대피소 방어를 맡던 영웅입니다.");
            player->stats = (Stats){45, 45, 8, 5, 5, 5, 0, 0};
    }

    printf("선택한 캐릭터: %s\n", player->name);
    printf("%s\n", player->description);
    printf("HP: %d, STR: %d, AGI: %d, MEN: %d, LCK: %d\n",
           player->stats.hp, player->stats.str, player->stats.agi, player->stats.men, player->stats.lck);
}

// 하루 시작
void startDay(Character *player, Resources *resources, int *day, int *explored) {
    int choice;
    printf("\n=== Day %d ===\n", *day);
    displayStatus(player, resources, *day);

    printf("1. 탐험\n");
    printf("2. 휴식\n");
    printf("행동을 선택하세요 (1~2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            explore(player, resources, explored, *day);
            break;
        case 2:
            rest(player, resources, explored);
            break;
        default:
            printf("잘못된 선택입니다. 휴식을 취합니다.\n");
            rest(player, resources, explored);
    }

    (*day)++;
}

// 탐험 기능
void explore(Character *player, Resources *resources, int *explored, int day) {
    *explored = 1; // 탐험 여부 플래그 설정

    char *locations[] = {"폐허", "숲", "습지", "연구소", "군사 기지"};
    int locationIndex = rand() % 5;
    char *location = locations[locationIndex];

    printf("\n=== 탐험 ===\n");
    printf("현재 위치: %s\n", location);

    // 하위 장소 설정
    char *sublocations[3];
    if (strcmp(location, "폐허") == 0) {
        sublocations[0] = "버려진 건물";
        sublocations[1] = "붕괴된 다리";
        sublocations[2] = "파괴된 거리";
    } else if (strcmp(location, "숲") == 0) {
        sublocations[0] = "깊은 숲속";
        sublocations[1] = "작은 호수";
        sublocations[2] = "낡은 오두막";
    } else if (strcmp(location, "습지") == 0) {
        sublocations[0] = "늪지대 중심부";
        sublocations[1] = "나무다리";
        sublocations[2] = "흐린 물 웅덩이";
    } else if (strcmp(location, "연구소") == 0) {
        sublocations[0] = "실험실";
        sublocations[1] = "기숙사";
        sublocations[2] = "폐기물 처리장";
    } else if (strcmp(location, "군사 기지") == 0) {
        sublocations[0] = "무기고";
        sublocations[1] = "지휘 본부";
        sublocations[2] = "훈련장";
    }

    int visited[3] = {0, 0, 0};
    int completed = 0;

    while (!completed) {
        printf("\n=== 탐험 가능한 장소 ===\n");
        for (int i = 0; i < 3; i++) {
            if (!visited[i]) {
                printf("%d. %s\n", i + 1, sublocations[i]);
            }
        }
        printf("4. 탐험 종료\n");
        printf("선택: ");
        int choice;
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3 && !visited[choice - 1]) {
            visited[choice - 1] = 1;
            exploreSubLocation(player, resources, sublocations[choice - 1], day);
        } else if (choice == 4) {
            completed = 1;
        } else {
            printf("잘못된 선택이거나 이미 탐험한 장소입니다.\n");
        }
    }

    printf("탐험 완료! %s 지역 탐색 종료.\n", location);
}

// 하위 장소 탐험
void exploreSubLocation(Character *player, Resources *resources, char *location, int day) {
    printf("\n=== %s 탐험 ===\n", location);
    int event = randomEvent(player, resources, day);
    if (event == 0) {
        combat(player, day);
    } else {
        Item items[] = {
            {"강화제", 10, 2},
            {"부서진 칼", 0, -2},
            {"기운 난 의약품", -5, 0},
            {"전투용 도끼", 0, 5},
            {"감염된 음식", -10, 0}
        };
        int itemIndex = rand() % 5;
        Item foundItem = items[itemIndex];
        printf("아이템 발견: %s (HP 효과: %d, STR 효과: %d)\n",
               foundItem.name, foundItem.hp_effect, foundItem.str_effect);
        applyItemEffect(player, foundItem);
    }
}
// 랜덤 이벤트
int randomEvent(Character *player, Resources *resources, int day) {
    int chance = rand() % 100;
    int success_threshold = 70 - (day * 5); // Day마다 성공 확률 감소
    printf("랜덤 이벤트 성공 확률: %d%%\n", success_threshold);
    if (chance < success_threshold) {
        return 1; // 성공
    } else {
        return 0; // 실패
    }
}

// 전투 시스템
void combat(Character *player, int day) {
    printf("\n=== 전투 발생! ===\n");

    // Day에 따라 적의 스탯 강화
    int base_enemy_hp = 20;
    int base_enemy_attack = 5;
    int enemy_hp = base_enemy_hp + (day * 5);  // Day마다 체력 +5
    int enemy_attack = base_enemy_attack + (day * 2);  // Day마다 공격력 +2

    printf("적 체력: %d, 적 공격력: %d\n", enemy_hp, enemy_attack);
    printf("플레이어 체력: %d, 플레이어 공격력: %d\n", player->stats.hp, player->stats.str);

    int choice;
    printf("1. 전투 진행\n");
    printf("2. 도망 시도\n");
    printf("선택하세요 (1~2): ");
    scanf("%d", &choice);

    if (choice == 2) {
        if (attemptEscape(player, day)) {
            printf("도망에 성공했습니다!\n");
            return;
        } else {
            printf("도망에 실패했습니다! 적과의 전투가 시작됩니다.\n");
        }
    }

    // 전투 진행
    while (enemy_hp > 0 && player->stats.hp > 0) {
        printf("적 체력: %d, 플레이어 체력: %d\n", enemy_hp, player->stats.hp);
        printf("공격합니다!\n");
        enemy_hp -= player->stats.str;
        if (enemy_hp > 0) {
            printf("적의 반격!\n");
            player->stats.hp -= enemy_attack;
        }
        if (player->stats.hp <= 0) {
            printf("당신은 적에게 당했습니다... 게임 종료.\n");
            exit(0);
        }
    }
    printf("전투에서 승리했습니다!\n");
}

// 도망 시도
int attemptEscape(Character *player, int day) {
    int chance = rand() % 100;
    int escape_chance = 50 + player->stats.agi - (day * 5);  // Day마다 도망 확률 감소
    printf("도망 성공 확률: %d%%\n", escape_chance);
    if (chance < escape_chance) {
        return 1; // 도망 성공
    } else {
        return 0; // 도망 실패
    }
}

// 휴식 기능
void rest(Character *player, Resources *resources, int *explored) {
    printf("\n=== 휴식 ===\n");
    if (resources->food > 0 && resources->water > 0) {
        resources->food--;
        resources->water--;
        player->stats.hp += 10;
        if (player->stats.hp > player->stats.max_hp)
            player->stats.hp = player->stats.max_hp;
        printf("체력 회복 완료! 현재 HP: %d\n", player->stats.hp);
        *explored = 0; // 휴식만 했으므로 탐험 여부는 충족되지 않음
    } else {
        printf("자원이 부족합니다! 체력을 회복할 수 없습니다.\n");
    }
}

// 아이템 효과 적용
void applyItemEffect(Character *player, Item item) {
    player->stats.hp += item.hp_effect;
    if (player->stats.hp > player->stats.max_hp)
        player->stats.hp = player->stats.max_hp;
    if (player->stats.hp < 0)
        player->stats.hp = 0;

    player->stats.str += item.str_effect;
    if (player->stats.str < 0)
        player->stats.str = 0;

    printf("현재 상태: HP = %d, STR = %d\n", player->stats.hp, player->stats.str);
}

// 현재 상태 표시
void displayStatus(Character *player, Resources *resources, int day) {
    printf("\n=== 현재 상태 ===\n");
    printf("Day: %d\n", day);
    printf("HP: %d/%d\n", player->stats.hp, player->stats.max_hp);
    printf("자원: 식량(%d), 물(%d), 의약품(%d), 무기(%d), 특별 아이템(%d)\n",
           resources->food, resources->water, resources->medicine, resources->weapons, resources->special_items);
}
