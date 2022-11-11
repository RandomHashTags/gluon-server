//
//  world.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef world_h
#define world_h

#include "chunk.h"
//#include "../entity/entity.h" // TODO: FIX - WHY BROKEN ??

struct World {
    const int seed[32];
    const char *name;
    
    int chunks_loaded_count;
    struct Chunk *chunks_loaded;
};

void world_destroy(struct World *world);

void world_load_chunk(struct World *world, struct Chunk *chunk);
void world_unload_chunk(struct World *world, struct Chunk *chunk);

//void world_entity_joined(Entity *entity);

#endif /* world_h */
