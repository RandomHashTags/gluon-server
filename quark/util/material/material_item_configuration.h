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
    /// Maximum amount of the same item that can be stacked in one slot.
    const unsigned char item_stack_size_maximum;
    
    /// If the item has durability.
    const _Bool has_durability;
    /// The item's maximum durability.
    const unsigned short durability;
    
    /// Amount of health points this item inflicts to a LivingEntity.
    const float attack_damage;
    /// Amount of durability to reduced this item by when attacking a LivingEntity.
    const unsigned short attack_durability_damage;
    /// Amount of durability to reduce this item by if the block broken does prefer the item's material.
    const unsigned short break_preferred_block_durability_damage;
    /// Amount of durability to reduce this item by if the block broken doesn't prefer the item's material.
    const unsigned short break_nonpreferred_block_durability_damage;
    
    /// The Crafting Recipe that creates this item.
    const struct CraftingRecipe *crafting_recipe;
    union { // TODO: free these
        const char *spawned_entity;
        const char *placed_block_material;
    };
};

struct MaterialItemConfiguration *material_item_configuration_create(const unsigned char item_stack_size_maximum, const _Bool has_durability, const unsigned short durability,
                                                                     const float attack_damage, const unsigned short attack_durability_damage,
                                                                     const unsigned short break_preferred_block_durability_damage,
                                                                     struct CraftingRecipe *crafting_recipe);
void material_item_configuration_destroy(struct MaterialItemConfiguration *configuration);

#endif /* material_item_configuration_h */
