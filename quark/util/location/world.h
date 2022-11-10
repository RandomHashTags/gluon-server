//
//  world.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef world_h
#define world_h

#include <stdio.h>
#include "chunk.h"

struct World {
    const int seed[32];
    char name[16];
};

void world_load_chunk(struct World *world, int x, int z);
void world_unload_chunk(struct World *world, int x, int z);

#endif /* world_h */
