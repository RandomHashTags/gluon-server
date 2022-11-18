//
//  biome.h
//  quark
//
//  Created by Evan Anderson on 11/17/22.
//

#ifndef biome_h
#define biome_h

#include "biome_configuration.h"

struct Biome {
    const char *identifier;
    
    const struct BiomeConfiguration *configuration;
};

struct Biome *biome_create(const char *identifier, const struct BiomeConfiguration *configuratino);
void biome_destroy(struct Biome *biome);

#endif /* biome_h */
