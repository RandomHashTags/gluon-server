//
//  chunk.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef chunk_h
#define chunk_h

struct Chunk {
    const long x;
    const long z;
};

void chunk_destroy(struct Chunk *chunk);

struct Block chunk_get_block_at(struct Chunk *chunk, long x, long y, long z);

#endif /* chunk_h */
