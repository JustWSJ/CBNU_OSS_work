#include <stdio.h>
#include "hotel.h"
#include "save.h"

// 호텔 방문: 체력 회복 및 진행 상황 저장
void visitHotel(Character* player) {
    printf("\n[호텔 방문]\n");

    // 체력 회복
    player->health = player->maxHealth;
    printf("체력이 완전히 회복되었습니다! (현재 체력: %d/%d)\n", player->health, player->maxHealth);

    // 진행 상황 저장
    saveStatus(player);
    printf("진행 상황이 저장되었습니다!\n");
}
