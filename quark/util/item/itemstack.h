//
//  itemstack.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef itemstack_h
#define itemstack_h

#include <stdio.h>
#include "material.h"
#include "itemmeta.h"
#include "../enchantment.h"

struct ItemStack {
    const enum Material type;
    struct ItemMeta item_meta;
    
    int amount;
    
    struct Enchant enchants[MAXIMUM_ENCHANTMENT_COUNT];
};

_Bool canEnchantItem(struct ItemStack *item);
void getEnchants(struct ItemStack *item, struct Enchant enchants[MAXIMUM_ENCHANTMENT_COUNT]);
_Bool hasEnchant(struct ItemStack *item, enum Enchantment enchantment);

#endif /* itemstack_h */
