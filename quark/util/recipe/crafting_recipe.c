//
//  crafting_recipe.c
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#include <stdlib.h>
#include "crafting_recipe.h"

void crafting_recipe_destroy(struct CraftingRecipe *recipe) {
    free(recipe);
}
