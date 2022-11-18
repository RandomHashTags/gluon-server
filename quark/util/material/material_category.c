//
//  material_category.c
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "material_category.h"
#include "../../utilities.h"

struct MaterialCategory *material_category_create(const char *identifier, const struct MaterialConfiguration *configuration) {
    struct MaterialCategory *category = malloc(sizeof(struct MaterialCategory));
    if (!category) {
        printf("failed to allocate memory for a MaterialCategory\n");
        return NULL;
    }
    const char *target_identifier = malloc_string(identifier);
    if (!target_identifier) {
        free(category);
        printf("failed to allocate memory for a MaterialCategory target_identifier\n");
        return NULL;
    }
    category->identifier = identifier;
    category->configuration = configuration;
    return category;
}
void material_category_destroy(struct MaterialCategory *category) {
    free((char *) category->identifier);
    free((struct MaterialConfiguration *) category->configuration);
    free(category);
}
