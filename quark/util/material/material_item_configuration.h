//
//  material_item_configuration.h
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#ifndef material_item_configuration_h
#define material_item_configuration_h

#include "../recipe/crafting_recipe.h"

struct MaterialItemConfiguration {
    const unsigned char item_stack_size_maximum;
    
    const _Bool has_durability;
    const short durability;
    
    const struct CraftingRecipe *crafting_recipe;
    union { // TODO: free these
        const char *spawned_entity;
        const char *placed_block_material;
    };
};

void material_item_configuration_destroy(struct MaterialItemConfiguration *configuration);

#endif /* material_item_configuration_h */
