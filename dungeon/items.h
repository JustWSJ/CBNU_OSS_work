#ifndef ITEMS_H
#define ITEMS_H

// 능력치 구조체
typedef struct {
    int health;
    int strength;
    int agility;
    int intelligence;
} Stats;

// 무기 구조체
typedef struct {
    char name[50];   // 무기 이름
    Stats statBoost; // 무기가 제공하는 능력치 증가
    int quantity;    // 무기 개수
} Weapon;

// 방어구 구조체
typedef struct {
    char name[50];   // 방어구 이름
    Stats statBoost; // 방어구가 제공하는 능력치 증가
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

// 외부에서 접근할 수 있는 아이템 배열 선언
extern Weapon weapons[];
extern Armor armors[];
extern Consumable consumables[];
extern Loot loots[];

#endif // ITEMS_H