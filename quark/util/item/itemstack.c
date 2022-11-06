//
//  itemstack.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "itemstack.h"

_Bool canEnchantItem(struct ItemStack *item) {
    return canEnchantMaterial(item->type);
}

void getEnchants(struct ItemStack *item, struct Enchant enchants[MAXIMUM_ENCHANTMENT_COUNT]) {
    enchants = item->enchants;
}
_Bool hasEnchant(struct ItemStack *item, enum Enchantment enchantment) {
    struct Enchant enchants[MAXIMUM_ENCHANTMENT_COUNT];
    getEnchants(item, enchants);
    for (int i = 0; i < MAXIMUM_ENCHANTMENT_COUNT; i++) {
        if (enchants[i].type == enchantment) {
            return 1;
        }
    }
    return 0;
}
