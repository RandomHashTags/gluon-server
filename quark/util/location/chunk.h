//
//  chunk.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef chunk_h
#define chunk_h

#include <stdio.h>
#include "block.h"

struct Chunk {
    const int x;
    const int z;
};

struct Block getBlockAt(struct Chunk *chunk, int x, int y, int z);

#endif /* chunk_h */
