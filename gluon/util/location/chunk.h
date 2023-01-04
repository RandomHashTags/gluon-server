//
//  chunk.h
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef chunk_h
#define chunk_h

#include "world.h"
#include "chunk_data.h"

struct Chunk {
    const struct World *world;
    const long x;
    const long z;
    
    unsigned long data_count;
    struct ChunkData **data;
};

struct Chunk *chunk_create(struct World *world, const long x, const long z);
void chunk_destroy(struct Chunk *chunk);

struct ChunkData *chunk_get_or_load_data(struct Chunk *chunk, const long y);
struct Block *chunk_get_loaded_block_at_xyz(struct Chunk *chunk, const long x, const long y, const long z);
struct LivingEntity **chunk_get_living_entities(const struct Chunk *chunk, unsigned int *count);

#endif /* chunk_h */
