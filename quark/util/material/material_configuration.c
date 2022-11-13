//
//  material_configuration.c
//  quark
//
//  Created by Evan Anderson on 11/12/22.
//

#include <stdlib.h>
#include "material_configuration.h"

void material_configuration_destroy(struct MaterialConfiguration *configuration) {
    material_names_destroy((struct MaterialNames *) configuration->names);
    material_item_configuration_destroy((struct MaterialItemConfiguration *) configuration->item_configuration);
    material_block_configuration_destroy((struct MaterialBlockConfiguration *) configuration->block_configuration);
    material_smelting_configuration_destroy((struct MaterialSmeltingConfiguration *) configuration->smelting_configuration);
    free((struct MaterialCategory *) configuration->material_categories);
    free(configuration);
}
