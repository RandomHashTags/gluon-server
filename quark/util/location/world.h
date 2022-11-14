//
//  world.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef world_h
#define world_h

#include "chunk.h"
#include "../difficulty.h"
//#include "../entity/entity.h" // TODO: FIX - WHY BROKEN ??

struct World {
    const int seed[32];
    const char *name;
    
    struct Difficulty difficulty;
    
    unsigned int chunks_loaded_count;
    const unsigned int chunks_loaded_count_maximum;
    struct Chunk *chunks_loaded;
};

void world_destroy(struct World *world);

void world_load_chunk(struct World *world, struct Chunk *chunk);
void world_unload_chunk(struct World *world, struct Chunk *chunk);

//void world_entity_joined(Entity *entity);

#endif /* world_h */
