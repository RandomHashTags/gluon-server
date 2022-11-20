//
//  block.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "block.h"

struct Block *block_create(struct Material *material, struct BlockLocation *location) {
    struct Block *block = malloc(sizeof(struct Block));
    if (!block) {
        printf("failed to allocate memory for a Block\n");
        return NULL;
    }
    block->material = material;
    block->location = location;
    return block;
}
void block_destroy(struct Block *block) {
    bounding_box_destroy(block->boundary);
    block_location_destroy(block->location);
    free(block->material);
    free(block);
}

void block_break_naturally(struct Block *block, struct ItemStack *item) {
    if (item) {
    }
    block_destroy(block);
}

_Bool block_is_preferred_tool(struct Block *block, struct ItemStack *item) {
    const struct MaterialBlockConfiguration *block_configuration = block->material->configuration->block;
    const struct Material *item_material = item->material;
    return 0;
}
