//
//  block.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef block_h
#define block_h

#include "block_location.h"
#include "../item/item_stack.h"

struct Block {
    struct Material *material;
    unsigned char light_level;
    
    struct BlockLocation *location;
};

struct Block *block_create(struct Material *material, struct BlockLocation *location);
void block_destroy(struct Block *block);

void block_break_naturally(struct Block *block, struct ItemStack *item);

_Bool block_is_preferred_tool(struct Block *block, struct ItemStack *item);
struct ItemStack *block_get_drops(struct Block *block, struct ItemStack *item);

#endif /* block_h */
