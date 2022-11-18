//
//  material_block_configuration.h
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#ifndef material_block_configuration_h
#define material_block_configuration_h

#include "../item/item_stack.h"

struct MaterialBlockConfiguration {
    /// If this block breaks instantly when attacked.
    const _Bool breaks_instantly;
    const short resistance;
    
    const unsigned short dropped_items_count;
    const struct ItemStack *dropped_items;
};

void material_block_configuration_destroy(struct MaterialBlockConfiguration *configuration);

#endif /* material_block_configuration_h */
