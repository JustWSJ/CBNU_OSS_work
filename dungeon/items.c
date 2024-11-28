#include "items.h"

// 무기 데이터
Weapon weapons[] = {
    {"Steel Sword", {0, 10, 2, 0}, 5},
    {"Iron Axe", {0, 12, 1, 0}, 3},
    {"Elven Bow", {0, 8, 5, 0}, 4},
    {"Magic Staff", {5, 0, 0, 10}, 2},
    {"Dagger", {0, 6, 8, 0}, 6}
};

// 방어구 데이터
Armor armors[] = {
    {"Iron Shield", {10, 0, 0, 0}, 5},
    {"Steel Armor", {20, 0, 0, 0}, 3},
    {"Leather Boots", {0, 0, 5, 0}, 4},
    {"Mage Robe", {5, 0, 0, 10}, 2},
    {"Helm of Insight", {5, 0, 0, 5}, 6}
};

// 소모품 데이터
Consumable consumables[] = {
    {"Health Potion", {20, 0, 0, 0}, 10},
    {"Mana Elixir", {0, 0, 0, 20}, 7},
    {"Strength Tonic", {0, 5, 0, 0}, 5},
    {"Agility Brew", {0, 0, 5, 0}, 8},
    {"Intelligence Syrup", {0, 0, 0, 5}, 6}
};

// 전리품 데이터
Loot loots[] = {
    {"Golden Coin", "A shiny coin made of gold.", 50},
    {"Emerald Gem", "A precious green gem.", 3},
    {"Ancient Relic", "A mysterious relic from the past.", 1},
    {"Silver Ring", "A small ring made of silver.", 10},
    {"Dragon Scale", "A rare scale from a dragon.", 2}
};