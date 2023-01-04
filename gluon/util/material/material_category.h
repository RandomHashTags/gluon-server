//
//  material_category.h
//  gluon
//
//  Created by Evan Anderson on 11/13/22.
//

#ifndef material_category_h
#define material_category_h

#include "material_configuration.h"

struct MaterialCategory {
    const char *identifier;
    const struct MaterialConfiguration *configuration;
};

struct MaterialCategory *material_category_create(const char *identifier, const struct MaterialConfiguration *configuration);
void material_category_destroy(struct MaterialCategory *category);

#endif /* material_category_h */
