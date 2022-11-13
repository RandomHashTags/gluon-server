//
//  material.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef material_h
#define material_h

#include "material_configuration.h"
//#include "../color.h"

struct Material {
    const char identifier[40];
    const struct MaterialConfiguration *configuration;
};

void material_destroy(struct Material *material);

#endif /* material_h */
