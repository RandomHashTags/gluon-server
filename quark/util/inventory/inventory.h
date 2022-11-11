//
//  inventory.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef inventory_h
#define inventory_h

#include "inventory_type.h"
#include "../item/item_stack.h"

struct Inventory {
    const enum InventoryType type;
    
    int size;
    struct ItemStack *items;
};

struct ItemStack *inventory_get_item(struct Inventory *inventory, int slot);
void inventory_set_item(struct Inventory *inventory, int slot, struct ItemStack *item);

#endif /* inventory_h */
