#ifndef CHARACTER_H
#define CHARACTER_H

// 기본 공격력 방어력 10
// 

typedef struct {
    char name[8];
    int health;         //  최대체력, 기본 방어력 증가
    int strength;       //  기본 공격력 증가
    int agility;        //  회피, 공격 성골률 증가
    int intelligence;   //  ?
    int sensory;        //  치명타 확률 증가
    int luck;           //  치명타 확률, 기타 긍정 랜덤 이벤트 증가

    int max_health;     //  최대체력 = health * 20;

    int Maxfloor;       //  최대 도달 계층
} Character;

// Getter/Setter 함수 선언
Character* getPlayer();
void setPlayer(Character newPlayer);
void updatePlayerStat(const char* stat, int value);

#endif // CHARACTER_H
