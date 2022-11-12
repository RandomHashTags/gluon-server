//
//  inventory.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdlib.h>
#include <string.h>
#include "inventory.h"

void inventory_destroy(struct Inventory *inventory) {
    const int viewers_count = inventory->viewers_count;
    struct Player *viewers = inventory->viewers;
    for (int i = 0; i < viewers_count; i++) {
        //struct Player *viewer = viewers[i]; // TODO: fix this bruh
    }
    free(viewers);
    
    const int size = inventory->size;
    struct ItemStack *items = inventory->items;
    for (int i = 0; i < size; i++) {
        struct ItemStack *item = &items[i];
        item_stack_destroy(item);
    }
    free(items);
    
    free(inventory);
}

struct ItemStack *inventory_get_item(struct Inventory *inventory, int slot) {
    return &inventory->items[slot];
}
void inventory_set_item(struct Inventory *inventory, int slot, struct ItemStack *item) {
    if (slot < inventory->size) {
        struct ItemStack *items = inventory->items;
        memmove(&items[slot], item, sizeof(struct ItemStack));
    }
}
