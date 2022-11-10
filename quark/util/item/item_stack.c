//
//  itemstack.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "item_stack.h"

void item_stack_destroy(struct ItemStack *item) {
    item_meta_destroy(item->meta);
    free(item);
}

_Bool item_stack_can_be_enchanted(struct ItemStack *item) {
    if (material_can_be_enchanted(item->type)) {
        return 1;
    }
    return 0;
}
struct Enchant *item_stack_get_enchants(struct ItemStack *item) {
    return item_meta_get_enchants(item->meta);
}
_Bool item_stack_has_enchant(struct ItemStack *item, enum Enchantment enchantment) {
    return item_meta_has_enchant(item->meta, enchantment);
}
