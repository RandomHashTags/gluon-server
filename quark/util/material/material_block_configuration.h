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
    /// If entities can passthrough (walk/sprint/swim through) this block or not.
    const _Bool can_passthrough;
    const float passthrough_velocity_dampen_x;
    const float passthrough_velocity_dampen_y;
    const float passthrough_velocity_dampen_z;
    
    /// Whether an Entity gets damaged from falling on this block or not.
    const _Bool breaks_fall;
    
    /// If this block breaks instantly when attacked.
    const _Bool breaks_instantly;
    const short resistance;
    
    const unsigned short dropped_items_count;
    const struct ItemStack *dropped_items;
};

void material_block_configuration_destroy(struct MaterialBlockConfiguration *configuration);

#endif /* material_block_configuration_h */
