//
//  inventory.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

struct Inventory *inventory_create(struct InventoryType type, struct ItemStack *items) {
    struct Inventory *inventory = malloc(sizeof(struct Inventory));
    if (!inventory) {
        printf("failed to allocate memory for a Inventory\n");
        return NULL;
    }
    inventory->items = items;
    inventory->viewers_count = 0;
    
    struct Player *viewers = malloc(2 * sizeof(struct Player));
    inventory->viewers = viewers;
    return inventory;
}
void inventory_destroy(struct Inventory *inventory) {
    const int viewers_count = inventory->viewers_count;
    struct Player *viewers = inventory->viewers;
    for (int i = 0; i < viewers_count; i++) {
        //struct Player *viewer = viewers[i]; // TODO: fix this bruh
    }
    free(viewers);
    
    const int size = inventory->type->size;
    struct ItemStack *items = inventory->items;
    for (int i = 0; i < size; i++) {
        struct ItemStack *item = &items[i];
        item_stack_destroy(item);
    }
    free(items);
    
    free(inventory);
}

struct ItemStack *inventory_get_item(struct Inventory *inventory, unsigned short slot) {
    return &inventory->items[slot];
}
void inventory_set_item(struct Inventory *inventory, unsigned short slot, struct ItemStack *item) {
    if (slot < inventory->type->size) {
        inventory->items[slot] = *item;
    }
}
