//
//  inventory.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef inventory_h
#define inventory_h

#include <stdio.h>
#include "inventory_type.h"

struct Inventory {
    const enum InventoryType type;
    
    int size;
    
    struct ItemStack (*getItem)(int slot);
    void (*setItem)(int slot, struct ItemStack item);
};

#endif /* inventory_h */
