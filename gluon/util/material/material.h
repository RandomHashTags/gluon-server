//
//  material.h
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef material_h
#define material_h

#include "material_category.h"
#include "material_configuration.h"
#include "../names.h"

struct Material {
    const char *identifier;
    const struct Names *names;
    const struct MaterialCategory *categories;
    const struct MaterialConfiguration *configuration;
};

struct Material *material_create(const char *identifier, const struct Names *names, const struct MaterialConfiguration *configuration);
void material_destroy(struct Material *material);

extern struct Material MINECRAFT_AIR;
extern struct Material MINECRAFT_BEDROCK;

#endif /* material_h */
