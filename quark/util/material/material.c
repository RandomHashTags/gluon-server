//
//  material.c
//  quark
//
//  Created by Evan Anderson on 11/5/22.
//

#include <stdlib.h>
#include "material.h"

void material_destroy(struct Material *material) {
    material_configuration_destroy((struct MaterialConfiguration *) material->configuration);
    free(material);
}
