//
//  material.c
//  quark
//
//  Created by Evan Anderson on 11/5/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "material.h"
#include "../../utilities.h"

struct Material *material_create(const char *identifier, const struct MaterialNames *names, const struct MaterialConfiguration *configuration) {
    struct Material *material = malloc(sizeof(struct Material));
    if (!material) {
        printf("failed to allocate memory for a Material\n");
        return NULL;
    }
    const char *target_identifier = malloc_string(identifier);
    if (!target_identifier) {
        free(material);
        printf("failed to allocate memory for a Material target_identifier\n");
        return NULL;
    }
    material->identifier = target_identifier;
    material->names = names;
    material->configuration = configuration;
    return material;
}
void material_destroy(struct Material *material) {
    material_names_destroy((struct MaterialNames *) material->names);
    material_configuration_destroy((struct MaterialConfiguration *) material->configuration);
    free((char *) material->identifier);
    free((struct MaterialCategory *) material->categories);
    free(material);
}

struct Material MINECRAFT_AIR = {
    .identifier = "minecraft.air"
};
struct Material MINECRAFT_BEDROCK = {
    .identifier = "minecraft.bedrock"
};
