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
#include "../entity/player/player.h"

struct Inventory {
    struct InventoryType *type;
    struct ItemStack *items;
    
    unsigned short viewers_count;
    struct Player *viewers;
};

struct Inventory *inventory_create(struct InventoryType type, struct ItemStack *items);
void inventory_destroy(struct Inventory *inventory);

struct ItemStack *inventory_get_item(struct Inventory *inventory, unsigned short slot);
void inventory_set_item(struct Inventory *inventory, unsigned short slot, struct ItemStack *item);

#endif /* inventory_h */
