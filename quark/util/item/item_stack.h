//
//  item_stack.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef item_stack_h
#define item_stack_h

#include "material.h"
#include "item_meta.h"

struct ItemStack {
    const enum Material material;
    struct ItemMeta *meta;
    
    int amount;
};

void item_stack_destroy(struct ItemStack *item);

_Bool item_stack_can_be_enchanted(struct ItemStack *item);
struct Enchant *item_stack_get_enchants(struct ItemStack *item);
_Bool item_stack_has_enchant(struct ItemStack *item, enum Enchantment enchantment);

#endif /* item_stack_h */
