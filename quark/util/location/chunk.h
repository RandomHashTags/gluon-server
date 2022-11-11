//
//  chunk.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef chunk_h
#define chunk_h

struct Chunk {
    const int x;
    const int z;
};

void chunk_destroy(struct Chunk *chunk);

struct Block chunk_get_block_at(struct Chunk *chunk, int x, int y, int z);

#endif /* chunk_h */
