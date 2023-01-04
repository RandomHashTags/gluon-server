//
//  material_smelting_configuration.h
//  gluon
//
//  Created by Evan Anderson on 11/13/22.
//

#ifndef material_smelting_configuration_h
#define material_smelting_configuration_h

struct MaterialSmeltingConfiguration {
    const char *smelts_to_material;
    const unsigned short smelted_experience;
};

void material_smelting_configuration_destroy(struct MaterialSmeltingConfiguration *configuration);

#endif /* material_smelting_configuration_h */
