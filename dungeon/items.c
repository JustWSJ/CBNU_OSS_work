#include "items.h"

// 무기 데이터
Weapon weapons[WEAPON_COUNT] = {
    {"Steel Sword", {0, 10, 2, 0, 5, 1}, 1},
    {"Iron Axe", {0, 12, 1, 0, 3, 2}, 1},
    {"Elven Bow", {0, 8, 5, 0, 6, 4}, 1},
    {"Magic Staff", {5, 0, 0, 10, 2, 3}, 1},
    {"Dagger", {0, 6, 8, 0, 7, 5}, 1}
};

// 방어구 데이터
Armor armors[ARMOR_COUNT] = {
    {"Iron Shield", {10, 0, 0, 0, 3, 2}, 1},
    {"Steel Armor", {20, 0, 0, 0, 2, 1}, 1},
    {"Leather Boots", {0, 0, 5, 0, 5, 2}, 1},
    {"Mage Robe", {5, 0, 0, 10, 1, 4}, 1},
    {"Helm of Insight", {5, 0, 0, 5, 4, 3}, 1}
};

// 소모품 데이터
Consumable consumables[CONSUMABLE_COUNT] = {
    {"Health Potion", {20, 0, 0, 0, 0, 0}, 10},
    {"Mana Elixir", {0, 0, 0, 20, 0, 0}, 7},
    {"Strength Tonic", {0, 5, 0, 0, 0, 2}, 5},
    {"Agility Brew", {0, 0, 5, 0, 1, 1}, 8},
    {"Intelligence Syrup", {0, 0, 0, 5, 0, 3}, 6}
};

// 전리품 데이터
Loot loots[LOOT_COUNT] = {
    {"Golden Coin", "A shiny coin made of gold.", 50},
    {"Emerald Gem", "A precious green gem.", 3},
    {"Ancient Relic", "A mysterious relic from the past.", 1},
    {"Silver Ring", "A small ring made of silver.", 10},
    {"Dragon Scale", "A rare scale from a dragon.", 2}
};