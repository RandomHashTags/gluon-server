//
//  inventory.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <string.h>
#include "inventory.h"

struct ItemStack *inventory_get_item(struct Inventory *inventory, int slot) {
    return &inventory->items[slot];
}
void inventory_set_item(struct Inventory *inventory, int slot, struct ItemStack *item) {
    if (slot < inventory->size) {
        struct ItemStack *items = inventory->items;
        memmove(&items[slot], item, sizeof(struct ItemStack));
    }
}
