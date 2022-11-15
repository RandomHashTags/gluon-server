//
//  item.h
//  quark
//
//  Created by Evan Anderson on 11/12/22.
//

#ifndef item_h
#define item_h

#include "entity.h"
#include "../item/item_stack.h"

struct Item {
    struct Entity *entity;
    struct ItemStack *item_stack;
    unsigned short pickup_delay;
};

void item_destroy(struct Item *item, _Bool destroy_item_stack);

#endif /* item_h */
