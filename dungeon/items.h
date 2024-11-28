#ifndef ITEMS_H
#define ITEMS_H

#define WEAPON_COUNT 5       // 무기 종류 수
#define ARMOR_COUNT 5        // 방어구 종류 수
#define CONSUMABLE_COUNT 5   // 소모품 종류 수
#define LOOT_COUNT 5         // 전리품 종류 수

// 능력치 구조체
typedef struct {
    int health;       // 체력
    int strength;     // 힘
    int agility;      // 민첩성
    int intelligence; // 지능
} Stats;

// 무기 구조체
typedef struct {
    char name[50];   // 무기 이름
    Stats statBoost; // 무기로 증가하는 능력치
    int quantity;    // 무기 개수
} Weapon;

// 방어구 구조체
typedef struct {
    char name[50];   // 방어구 이름
    Stats statBoost; // 방어구로 증가하는 능력치
    int quantity;    // 방어구 개수
} Armor;

// 소모품 구조체
typedef struct {
    char name[50];   // 소모품 이름
    Stats effect;    // 소모품 사용 시 능력치 변화
    int quantity;    // 소모품 개수
} Consumable;

// 전리품 구조체
typedef struct {
    char name[50];   // 전리품 이름
    char effect[100]; // 전리품 설명
    int quantity;    // 전리품 개수
} Loot;

// 외부에서 접근 가능한 아이템 배열 선언
extern Weapon weapons[WEAPON_COUNT];
extern Armor armors[ARMOR_COUNT];
extern Consumable consumables[CONSUMABLE_COUNT];
extern Loot loots[LOOT_COUNT];

#endif 