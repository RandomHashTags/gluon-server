//
//  item_stack.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item_stack.h"

struct ItemStack *item_stack_create(struct Material *material, short amount, short durability, struct ItemMeta *meta) {
    struct ItemStack *item_stack = malloc(sizeof(struct ItemStack));
    if (!item_stack) {
        printf("failed to allocate memory for a ItemStack\n");
        return NULL;
    }
    memcpy((struct Material *) item_stack->material, material, sizeof(struct Material));
    item_stack->amount = amount;
    item_stack->durability = durability;
    item_stack->meta = meta;
    return item_stack;
}
void item_stack_destroy(struct ItemStack *item) {
    item_meta_destroy(item->meta);
    free((struct Material *) item->material);
    free(item);
}

_Bool item_stack_is_similar(struct ItemStack *item_stack1, struct ItemStack *item_stack2) {
    if (item_stack1 == item_stack2) {
        return 1;
    } else if ((item_stack1 == NULL && item_stack2 != NULL) || (item_stack2 == NULL && item_stack2 != NULL) || (item_stack1->material != item_stack2->material)) {
        return 0;
    } else {
        return item_meta_is_similar(item_stack1->meta, item_stack2->meta);
    }
}

_Bool item_stack_can_be_enchanted(struct ItemStack *item) {
    return 0;
}
struct Enchant *item_stack_get_enchants(struct ItemStack *item) {
    return item_meta_get_enchants(item->meta);
}
struct Enchant *item_stack_has_enchant(struct ItemStack *item, struct EnchantmentType enchantment) {
    return item_meta_get_enchant(item->meta, enchantment);
}
