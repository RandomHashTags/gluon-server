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
    const int seed;
    char name[18];
    
    void (*loadChunk)(int x, int z);
    void (*unloadChunk)(int x, int z);
};

#endif /* world_h */
