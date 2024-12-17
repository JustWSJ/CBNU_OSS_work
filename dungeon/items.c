#include "items.h"

Item weapons[WEAPON_COUNT] = {
    {"Steel Sword", ITEM_WEAPON, 1, {0, 10, 2, 0, 5, 1}, ""},
    {"Iron Axe", ITEM_WEAPON, 1, {0, 12, 1, 0, 3, 2}, ""},
    {"Elven Bow", ITEM_WEAPON, 1, {0, 8, 5, 0, 6, 4}, ""},
    {"Magic Staff", ITEM_WEAPON, 1, {5, 0, 0, 10, 2, 3}, ""},
    {"Dagger", ITEM_WEAPON, 1, {0, 6, 8, 0, 7, 5}, ""}
};

// 방어구 데이터
Item armors[ARMOR_COUNT] = {
    {"Iron Shield", ITEM_ARMOR, 1, {10, 0, 0, 0, 3, 2}, ""},
    {"Steel Armor", ITEM_ARMOR, 1, {20, 0, 0, 0, 2, 1}, ""},
    {"Leather Boots", ITEM_ARMOR, 1, {0, 0, 5, 0, 5, 2}, ""},
    {"Mage Robe", ITEM_ARMOR, 1, {5, 0, 0, 10, 1, 4}, ""},
    {"Helm of Insight", ITEM_ARMOR, 1, {5, 0, 0, 5, 4, 3}, ""}
};

// 소모품 데이터 (강화 버전 포함)
Item consumables[CONSUMABLE_COUNT] = {
    {"Health Potion", ITEM_CONSUMABLE, 10, {20, 0, 0, 0, 0, 0}, ""},
    {"Mana Elixir", ITEM_CONSUMABLE, 7, {0, 0, 0, 20, 0, 0}, ""},
    {"Strength Tonic", ITEM_CONSUMABLE, 5, {0, 5, 0, 0, 0, 2}, ""},
    {"Agility Brew", ITEM_CONSUMABLE, 8, {0, 0, 5, 0, 1, 1}, ""},
    {"Intelligence Syrup", ITEM_CONSUMABLE, 6, {0, 0, 0, 5, 0, 3}, ""},
    // 강화 버전 소모품
    {"Health Potion +1", ITEM_CONSUMABLE, 5, {30, 0, 0, 0, 0, 0}, ""},
    {"Health Potion +2", ITEM_CONSUMABLE, 3, {50, 0, 0, 0, 0, 0}, ""},
    {"Health Potion +3", ITEM_CONSUMABLE, 1, {70, 0, 0, 0, 0, 0}, ""},

    {"Mana Elixir +1", ITEM_CONSUMABLE, 5, {0, 0, 0, 30, 0, 0}, ""},
    {"Mana Elixir +2", ITEM_CONSUMABLE, 3, {0, 0, 0, 50, 0, 0}, ""},
    {"Mana Elixir +3", ITEM_CONSUMABLE, 1, {0, 0, 0, 70, 0, 0}, ""},

    {"Strength Tonic +1", ITEM_CONSUMABLE, 5, {0, 3, 0, 0, 0, 0}, ""},
    {"Strength Tonic +2", ITEM_CONSUMABLE, 3, {0, 5, 0, 0, 0, 0}, ""},
    {"Strength Tonic +3", ITEM_CONSUMABLE, 1, {0, 7, 0, 0, 0, 0}, ""},

    {"Agility Brew +1", ITEM_CONSUMABLE, 5, {0, 0, 3, 0, 0, 0}, ""},
    {"Agility Brew +2", ITEM_CONSUMABLE, 3, {0, 0, 5, 0, 0, 0}, ""},
    {"Agility Brew +3", ITEM_CONSUMABLE, 1, {0, 0, 7, 0, 0, 0}, ""},

    {"Intelligence Syrup +1", ITEM_CONSUMABLE, 5, {0, 0, 0, 3, 0, 0}, ""},
    {"Intelligence Syrup +2", ITEM_CONSUMABLE, 3, {0, 0, 0, 5, 0, 0}, ""},
    {"Intelligence Syrup +3", ITEM_CONSUMABLE, 1, {0, 0, 0, 7, 0, 0}, ""}
};

// 전리품 데이터
Item loots[LOOT_COUNT] = {
    {"Golden Coin", ITEM_LOOT, 50, {0, 0, 0, 0, 0, 0}, "A shiny coin made of gold."},
    {"Emerald Gem", ITEM_LOOT, 3, {0, 0, 0, 0, 0, 0}, "A precious green gem."},
    {"Ancient Relic", ITEM_LOOT, 1, {0, 0, 0, 0, 0, 0}, "A mysterious relic from the past."},
    {"Silver Ring", ITEM_LOOT, 10, {0, 0, 0, 0, 0, 0}, "A small ring made of silver."},
    {"Dragon Scale", ITEM_LOOT, 2, {0, 0, 0, 0, 0, 0}, "A rare scale from a dragon."}
};