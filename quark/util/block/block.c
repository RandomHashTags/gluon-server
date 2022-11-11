//
//  block.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdlib.h>
#include "block.h"

void block_destroy(struct Block *block) {
    block_location_destroy((struct BlockLocation *) &block->location);
    free(block);
}

void block_break_naturally(struct Block *block, struct ItemStack *item) {
    if (item != NULL && material_is_tool(item->material)) {
    }
    block_destroy(block);
}

_Bool block_is_preferred_tool(struct Block *block, struct ItemStack *item) {
    const Material block_material = block->material;
    if (item != NULL) {
        const Material item_material = item->material;
        return 1;
    }
    return 0;
}
