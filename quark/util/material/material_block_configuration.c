//
//  material_block_configuration.c
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#include <stdlib.h>
#include "material_block_configuration.h"

void material_block_configuration_destroy(struct MaterialBlockConfiguration *configuration) {
    item_stacks_destroy(configuration->dropped_items_count, (struct ItemStack *) configuration->dropped_items);
    free(configuration);
}
