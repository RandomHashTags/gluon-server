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

struct Block *block_create(struct Material *material, struct Boundary *boundary, struct BlockLocation *location) {
    struct Block *block = malloc(sizeof(struct Block));
    if (!block) {
        printf("failed to allocate memory for a Block\n");
        return NULL;
    }
    block->material = material;
    block->boundary = boundary;
    block->location = location;
    return block;
}
void block_destroy(struct Block *block) {
    block_location_destroy(block->location);
    free(block->material);
    free(block->boundary); // TODO: check to destroy source or not
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

const float block_get_height(struct Block *block) {
    const struct Boundary *boundary = block->boundary;
    const enum BoundaryType boundary_type = boundary->type;
    switch (boundary_type) {
        case BOUNDARY_TYPE_BOX:
            return bounding_box_calculate_height(boundary->box);
        case BOUNDARY_TYPE_CIRCLE:
            return bounding_circle_calculate_height(boundary->circle);
        default:
            return 0;
    }
}
