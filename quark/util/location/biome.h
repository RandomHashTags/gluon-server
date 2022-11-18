//
//  biome.h
//  quark
//
//  Created by Evan Anderson on 11/17/22.
//

#ifndef biome_h
#define biome_h

struct Biome {
    const char *identifier;
};

struct Biome *biome_create(const char *identifier);
void biome_destroy(struct Biome *biome);

#endif /* biome_h */
