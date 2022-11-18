//
//  chunk.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef chunk_h
#define chunk_h

#include "world.h"

struct Chunk {
    const struct World *world;
    const long x;
    const long z;
};

struct Chunk *chunk_create(struct World *world, const long x, const long z);
void chunk_destroy(struct Chunk *chunk);

void chunk_get_loaded_block_at(struct Chunk *chunk, const long x, const long y, const long z, struct Block *block); // TODO: fix circular dependency problem
void chunk_get_living_entities(const struct Chunk *chunk, unsigned int *count, struct LivingEntity **entities); // TODO: fix circular dependency problem

#endif /* chunk_h */
