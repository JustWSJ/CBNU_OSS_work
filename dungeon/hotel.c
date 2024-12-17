#include <stdio.h>
#include "Character.h"
#include "hotel.h"
#include "saveLoad.h"

// 호텔 방문: 체력 회복 및 진행 상황 저장
void visitHotel(Character* player) {
    printf("\n[호텔 방문]\n");

    // 체력 회복
    player->cur_health = player->max_health;
    printf("체력이 완전히 회복되었습니다! (현재 체력: %d/%d)\n", player->cur_health, player->max_health);

    // 진행 상황 저장
    saveStatus(player);
    printf("진행 상황이 저장되었습니다!\n");
}
