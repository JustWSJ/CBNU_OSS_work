#ifndef ITEMS_H
#define ITEMS_H

#define MAX_ITEMS 100        // 인벤토리 최대 아이템 수
#define WEAPON_COUNT 5       // 무기 종류 수
#define ARMOR_COUNT 5        // 방어구 종류 수
#define CONSUMABLE_COUNT 20  // 소모품 종류 수
#define LOOT_COUNT 5         // 전리품 종류 수

// 아이템 타입 정의
typedef enum {
    ITEM_WEAPON,
    ITEM_ARMOR,
    ITEM_CONSUMABLE,
    ITEM_LOOT
} ItemType;

// 능력치 구조체
typedef struct {
    int health;       // 체력
    int strength;     // 힘
    int agility;      // 민첩성
    int intelligence; // 지능
    int sensory;      // 감각
    int luck;         // 운
} Stats;

// 통합된 아이템 구조체
typedef struct {
    char name[50];       // 아이템 이름
    ItemType type;       // 아이템 타입
    int quantity;        // 아이템 수량
    Stats effect;        // 아이템 효과
    char description[100]; // 아이템 설명 (전리품 등)
} Item;

// 무기, 방어구, 소모품, 전리품 데이터
extern Item weapons[WEAPON_COUNT];
extern Item armors[ARMOR_COUNT];
extern Item consumables[CONSUMABLE_COUNT];
extern Item loots[LOOT_COUNT];

#endif // ITEMS_H