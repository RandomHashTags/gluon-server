//
//  crafting_recipe.h
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#ifndef crafting_recipe_h
#define crafting_recipe_h

struct CraftingRecipe {
    const _Bool enforce_format;
};

void crafting_recipe_destroy(struct CraftingRecipe *recipe);

#endif /* crafting_recipe_h */
