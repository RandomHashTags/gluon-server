//
//  material_configuration.h
//  quark
//
//  Created by Evan Anderson on 11/12/22.
//

#ifndef material_configuration_h
#define material_configuration_h

#include "material_names.h"
#include "material_category.h"
#include "material_block_configuration.h"
#include "material_item_configuration.h"
#include "material_smelting_configuration.h"

struct MaterialConfiguration {
    const struct MaterialNames *names;
    const struct MaterialCategory *material_categories;
    union {
        const _Bool is_only_item;
        const _Bool is_only_block;
        const _Bool is_block_and_item;
    };
    const struct MaterialItemConfiguration *item_configuration;
    const struct MaterialBlockConfiguration *block_configuration;
    const struct MaterialSmeltingConfiguration *smelting_configuration;
};

void material_configuration_destroy(struct MaterialConfiguration *configuration);

#endif /* material_configuration_h */
