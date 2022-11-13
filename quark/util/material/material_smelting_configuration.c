//
//  material_smelting_configuration.c
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#include <stdlib.h>
#include "material_smelting_configuration.h"

void material_smelting_configuration_destroy(struct MaterialSmeltingConfiguration *configuration) {
    free((char *) configuration->smelts_to_material);
    free(configuration);
}
