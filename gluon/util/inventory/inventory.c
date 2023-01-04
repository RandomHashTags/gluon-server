//
//  inventory.c
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"

struct Inventory *inventory_create(struct InventoryType *type, struct ItemStack **items) {
    struct Inventory *inventory = malloc(sizeof(struct Inventory));
    if (!inventory) {
        printf("failed to allocate memory for a Inventory\n");
        return NULL;
    }
    struct Player **viewers = malloc(2 * sizeof(struct Player *));
    if (!viewers) {
        free(inventory);
        printf("failed to allocate memory for a Inventory viewers pointer\n");
        return NULL;
    }
    inventory->type = type;
    inventory->items = items;
    inventory->viewers_count = 0;
    inventory->viewers = viewers;
    return inventory;
}
void inventory_destroy(struct Inventory *inventory) {
    const unsigned short viewers_count = inventory->viewers_count;
    struct Player **viewers = inventory->viewers;
    for (unsigned short i = 0; i < viewers_count; i++) {
        struct Player *viewer = viewers[i];
        player_close_open_inventories(viewer, 0);
        free(viewer);
    }
    free(viewers);
    
    const unsigned short size = inventory->type->size;
    struct ItemStack **items = inventory->items;
    for (unsigned short i = 0; i < size; i++) {
        struct ItemStack *item = items[i];
        item_stack_destroy(item);
    }
    free(items);
    
    free(inventory->type);
    free(inventory);
}

struct ItemStack *inventory_get_item(struct Inventory *inventory, unsigned short slot) {
    return inventory->items[slot];
}
void inventory_set_item(struct Inventory *inventory, unsigned short slot, struct ItemStack *item) {
    inventory->items[slot] = item;
}

_Bool inventory_add_item(struct Inventory *inventory, struct ItemStack *item) {
    const unsigned short max_stack_size = item->material->configuration->item->item_stack_size_maximum;
    const unsigned short slots = inventory->type->size;
    struct ItemStack **items = inventory->items;
    for (unsigned short i = 0; i < slots; i++) {
        struct ItemStack *target_item = items[i];
        if (!target_item) {
            items[i] = item;
            return 1;
        } else if (item_stack_is_similar(target_item, item) && target_item->amount < max_stack_size) {
            const unsigned short target_item_amount = target_item->amount, item_amount = item->amount;
            const unsigned short new_amount = target_item_amount + item_amount;
            if (new_amount <= max_stack_size) {
                target_item->amount = new_amount;
                item_stack_destroy(item);
                return 1;
            } else {
                target_item->amount = max_stack_size;
                item->amount -= target_item_amount;
            }
        }
    }
    return 0;
}
