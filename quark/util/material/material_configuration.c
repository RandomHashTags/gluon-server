//
//  material_configuration.c
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#include <stdlib.h>
#include "material_configuration.h"

void material_configuration_destroy(struct MaterialConfiguration *configuration) {
    material_item_configuration_destroy((struct MaterialItemConfiguration *) configuration->item);
    material_block_configuration_destroy((struct MaterialBlockConfiguration *) configuration->block);
    material_smelting_configuration_destroy((struct MaterialSmeltingConfiguration *) configuration->smelting);
    free((struct MaterialCategory *) configuration->material_categories);
    free(configuration);
}
