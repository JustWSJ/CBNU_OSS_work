#ifndef BATTLE_H
#define BATTLE_H

typedef struct {
    char name[20];
    int health;       // 체력
    int strength;     // 공격력
    int agility;      // 민첩성
    int intelligence; // 지능
    int sensory;      // 감각
    int luck;         // 운
} Character;

// 함수 선언
void attack(Character *attacker, Character *defender);
int escape(Character *player, Character *enemy);
int dodge(Character *attacker, Character *defender);
void useItem(Character *player);
void displayStats(Character *character);
void battle(Character *player, Character *enemy);

#endif
