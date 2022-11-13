//
//  material_block_configuration.h
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#ifndef material_block_configuration_h
#define material_block_configuration_h

struct MaterialBlockConfiguration {
    const short resistance;
    
    const char *dropped_items;
};

void material_block_configuration_destroy(struct MaterialBlockConfiguration *configuration);

#endif /* material_block_configuration_h */
