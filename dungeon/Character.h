#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct {
    char name[8];
    int health;
    int strength;
    int agility;
    int intelligence;
    int sensory;
    int luck;
} Character;

// Getter/Setter 함수 선언
Character* getPlayer();
void setPlayer(Character newPlayer);
void updatePlayerStat(const char* stat, int value);

#endif // CHARACTER_H
