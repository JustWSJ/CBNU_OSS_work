#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ======== 전역 변수 및 구조체 ========
#define MAX_INVENTORY 10

typedef struct {
    int hp, max_hp, str, agi, men, lck, ap, sp;
} Stats;

typedef struct {
    char name[30];
    char description[150];
    Stats stats;
} Character;

typedef struct {
    char name[30];
    int hp_effect;
    int str_effect;
} Item;

typedef struct {
    int food, water, medicine, weapons, special_items;
    int key_items[4];
    Item inventory[MAX_INVENTORY];
    int inventory_count;
} Resources;

// ======== 함수 선언 ========
void initializeGame();
void selectCharacter(Character *player);
void startChapter(Character *player, Resources *resources, int chapter);
void explore(Character *player, Resources *resources, int chapter);
void exploreSubLocation(Character *player, Resources *resources, char *location, int chapter);
void rest(Character *player, Resources *resources);
void displayStatus(Character *player, Resources *resources, int chapter);
void openInventory(Character *player, Resources *resources);
void applyItemEffect(Character *player, Item item);
void combat(Character *player, int chapter, Resources *resources);
int randomEvent(Character *player, Resources *resources, int chapter);
void gameMenu(Character *player, Resources *resources, int *chapter);

// ======== 메인 함수 ========
int main() {
    srand(time(NULL));
    Character player;
    Resources resources = {3, 3, 2, 1, 0, {0, 0, 0, 0}, {}, 0};
    int chapter = 1;

    initializeGame();
    selectCharacter(&player);

    while (chapter <= 4) {
        startChapter(&player, &resources, chapter);
        if (resources.key_items[chapter - 1] == 0) {
            printf("챕터 %d에서 키 아이템을 획득하지 못했습니다. 게임 실패...\n", chapter);
            exit(0);
        }
        chapter++;
    }

    printf("\n축하합니다! 모든 챕터를 완료하고 모든 키 아이템을 획득했습니다.\n");
    printf("게임 클리어!\n");
    return 0;
}

void initializeGame() {
    printf("=== 텍스트 기반 좀비 아포칼립스 생존 게임 ===\n");
    printf("4개의 챕터를 클리어하고 모든 키 아이템을 획득하세요.\n");
}

void selectCharacter(Character *player) {
    int choice;
    printf("\n=== 캐릭터 선택 ===\n");
    printf("1. 방패의 수호자\n   추가 스탯: HP +15, STR +3\n");
    printf("2. 명사수\n   추가 스탯: HP +10, STR +5, AGI +5\n");
    printf("3. 행운의 탐험가\n   추가 스탯: HP +10, MEN +3, LCK +5\n");
    printf("캐릭터를 선택하세요 (1~3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(player->name, "방패의 수호자");
            player->stats = (Stats){45, 45, 8, 5, 5, 5, 0, 0};
            break;
        case 2:
            strcpy(player->name, "명사수");
            player->stats = (Stats){40, 40, 10, 10, 5, 5, 0, 0};
            break;
        case 3:
            strcpy(player->name, "행운의 탐험가");
            player->stats = (Stats){40, 40, 7, 8, 8, 10, 0, 0};
            break;
        default:
            strcpy(player->name, "방패의 수호자");
            player->stats = (Stats){45, 45, 8, 5, 5, 5, 0, 0};
    }

    printf("선택한 캐릭터: %s\n", player->name);
}

void startChapter(Character *player, Resources *resources, int chapter) {
    printf("\n=== 챕터 %d 시작 ===\n", chapter);
    printf("목표: 키 아이템을 획득하세요.\n");

    int completed = 0;
    while (!completed) {
        printf("\n1. 탐험\n2. 휴식\n3. 챕터 종료 (키 아이템 획득 시 가능)\n4. 메뉴\n");
        printf("행동을 선택하세요 (1~4): ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                explore(player, resources, chapter);
                break;
            case 2:
                rest(player, resources);
                break;
            case 3:
                if (resources->key_items[chapter - 1]) {
                    printf("챕터 %d를 완료했습니다.\n", chapter);
                    completed = 1;
                } else {
                    printf("키 아이템을 획득하지 못했습니다. 챕터를 종료할 수 없습니다.\n");
                }
                break;
            case 4:
                gameMenu(player, resources, &chapter);
                break;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}

void explore(Character *player, Resources *resources, int chapter) {
    char *locations[] = {"폐허", "숲", "습지", "연구소"};
    char *location = locations[chapter - 1];
    printf("\n=== 탐험: %s ===\n", location);

    char *sublocations[3] = {"위치1", "위치2", "위치3"};
    int visited[3] = {0, 0, 0};
    int completed = 0;

    while (!completed) {
        printf("\n1. %s\n2. %s\n3. %s\n4. 종료\n", sublocations[0], sublocations[1], sublocations[2]);
        printf("선택: ");
        int choice;
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3 && !visited[choice - 1]) {
            visited[choice - 1] = 1;
            exploreSubLocation(player, resources, sublocations[choice - 1], chapter);
        } else if (choice == 4) {
            completed = 1;
        } else {
            printf("잘못된 선택입니다.\n");
        }
    }
}

void exploreSubLocation(Character *player, Resources *resources, char *location, int chapter) {
    printf("\n=== %s 탐험 ===\n", location);

    int event = randomEvent(player, resources, chapter);
    if (event == 0) {
        printf("적과 마주쳤습니다! 전투를 시작합니다.\n");
        combat(player, chapter, resources);
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

        if (resources->inventory_count < MAX_INVENTORY) {
            resources->inventory[resources->inventory_count++] = foundItem;
            printf("아이템 발견: %s (HP 효과: %d, STR 효과: %d)\n",
                   foundItem.name, foundItem.hp_effect, foundItem.str_effect);
            printf("아이템이 인벤토리에 추가되었습니다!\n");
        } else {
            printf("인벤토리가 가득 찼습니다! 아이템을 추가할 수 없습니다.\n");
        }
    }
}

int randomEvent(Character *player, Resources *resources, int chapter) {
    return rand() % 2; // 0: 전투 발생, 1: 아이템 발견
}

void combat(Character *player, int chapter, Resources *resources) {
    printf("\n=== 전투 시작! ===\n");

    int monster_hp = 50 + (chapter * 20);
    int monster_attack = 10 + (chapter * 5);

    printf("적 몬스터 등장! HP: %d, 공격력: %d\n", monster_hp, monster_attack);

    while (monster_hp > 0 && player->stats.hp > 0) {
        printf("\n1. 공격\n2. 아이템 사용\n3. 도망치기\n");
        printf("선택: ");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            int damage = player->stats.str + (rand() % 5);
            monster_hp -= damage;
            printf("적에게 %d의 피해를 입혔습니다! 남은 HP: %d\n", damage, monster_hp);
            if (monster_hp <= 0) {
                printf("적을 물리쳤습니다!\n");
                break;
            }
        } else if (choice == 2) {
            if (resources->inventory_count > 0) {
                openInventory(player, resources);
            } else {
                printf("사용할 아이템이 없습니다.\n");
            }
        } else if (choice == 3) {
            printf("도망치기에 성공했습니다.\n");
            break;
        } else {
            printf("잘못된 선택입니다.\n");
        }

        int monster_damage = monster_attack + (rand() % 5);
        player->stats.hp -= monster_damage;
        printf("적의 공격! 당신은 %d의 피해를 입었습니다. 남은 HP: %d\n", monster_damage, player->stats.hp);

        if (player->stats.hp <= 0) {
            printf("당신은 전투에서 패배했습니다.\n");
            exit(0);
        }
    }
}

void openInventory(Character *player, Resources *resources) {
    printf("\n=== 인벤토리 ===\n");
    for (int i = 0; i < resources->inventory_count; i++) {
        printf("%d. %s (HP: %d, STR: %d)\n", i + 1, resources->inventory[i].name, resources->inventory[i].hp_effect, resources->inventory[i].str_effect);
    }
    printf("0. 종료\n");

    int choice;
    printf("아이템 번호를 선택하세요: ");
    scanf("%d", &choice);

    if (choice > 0 && choice <= resources->inventory_count) {
        applyItemEffect(player, resources->inventory[choice - 1]);
    } else {
        printf("인벤토리 닫기.\n");
    }
}

void applyItemEffect(Character *player, Item item) {
    printf("\n=== 아이템 사용 ===\n");
    player->stats.hp += item.hp_effect;
    if (player->stats.hp > player->stats.max_hp)
        player->stats.hp = player->stats.max_hp;
    printf("HP 회복: %d/%d\n", player->stats.hp, player->stats.max_hp);
    player->stats.str += item.str_effect;
    printf("STR 증가: %d\n", player->stats.str);
}

void rest(Character *player, Resources *resources) {
    printf("\n휴식 중...\n");
    if (resources->food > 0 && resources->water > 0) {
        resources->food--;
        resources->water--;
        player->stats.hp += 10;
        if (player->stats.hp > player->stats.max_hp)
            player->stats.hp = player->stats.max_hp;
        printf("체력 회복 완료! 현재 HP: %d\n", player->stats.hp);
    } else {
        printf("자원이 부족합니다! 체력을 회복할 수 없습니다.\n");
    }
}

void displayStatus(Character *player, Resources *resources, int chapter) {
    printf("\n=== 현재 상태 ===\n");
    printf("챕터: %d\n", chapter);
    printf("HP: %d/%d\n", player->stats.hp, player->stats.max_hp);
    printf("STR: %d, AGI: %d, MEN: %d, LCK: %d\n",
           player->stats.str, player->stats.agi, player->stats.men, player->stats.lck);
    printf("자원: 식량(%d), 물(%d), 의약품(%d), 무기(%d), 특별 아이템(%d)\n",
           resources->food, resources->water, resources->medicine, resources->weapons, resources->special_items);
}

void gameMenu(Character *player, Resources *resources, int *chapter) {
    int choice;
    printf("\n=== 메뉴 ===\n");
    printf("1. 인벤토리 열기\n2. 현재 상태 확인\n3. 게임 종료\n선택: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            openInventory(player, resources);
            break;
        case 2:
            displayStatus(player, resources, *chapter);
            break;
        case 3:
            printf("게임을 종료합니다.\n");
            exit(0);
        default:
            printf("잘못된 선택입니다.\n");
    }
}
