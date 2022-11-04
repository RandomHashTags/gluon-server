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

void loadChunk(struct World *world, int x, int z);
void unloadChunk(struct World *world, int x, int z);

#endif /* world_h */
