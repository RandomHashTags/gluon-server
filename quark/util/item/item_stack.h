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
    const struct Material *material;
    struct ItemMeta *meta;
    
    unsigned short amount;
    unsigned short durability;
};

struct ItemStack *item_stack_create(struct Material *material, short amount, short durability, struct ItemMeta *meta);
struct ItemStack *item_stack_clone(struct ItemStack *item);
void item_stack_destroy(struct ItemStack *item);
void item_stacks_destroy(const unsigned short count, struct ItemStack *items);

_Bool item_stack_is_similar(struct ItemStack *item_stack1, struct ItemStack *item_stack2);

_Bool item_stack_can_be_enchanted(struct ItemStack *item);
struct Enchant *item_stack_get_enchants(struct ItemStack *item);
struct Enchant *item_stack_get_enchant(struct ItemStack *item, struct EnchantmentType enchantment);
_Bool item_stack_try_applying_enchant(struct ItemStack *item, struct Enchant *enchant);
void item_stack_apply_unsafe_enchant(struct ItemStack *item, struct Enchant *enchant);

#endif /* item_stack_h */
