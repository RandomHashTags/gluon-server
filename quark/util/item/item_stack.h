//
//  itemstack.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef itemstack_h
#define itemstack_h

#include <stdio.h>
#include <stdlib.h>
#include "material.h"
#include "item_meta.h"
#include "../enchantment.h"

struct ItemStack {
    const enum Material type;
    struct ItemMeta *meta;
    
    int amount;
};

void item_stack_destroy(struct ItemStack *item);

_Bool item_stack_can_be_enchanted(struct ItemStack *item);
struct Enchant *item_stack_get_enchants(struct ItemStack *item);
_Bool item_stack_has_enchant(struct ItemStack *item, enum Enchantment enchantment);

#endif /* itemstack_h */
