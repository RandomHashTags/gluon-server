//
//  inventory.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "inventory.h"

void setItem(struct Inventory inventory, int slot, struct ItemStack *item) {
    if (slot < inventory.size) {
        inventory.items[slot] = item;
    }
}
