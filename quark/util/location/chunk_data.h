//
//  chunk_data.h
//  quark
//
//  Created by Evan Anderson on 11/20/22.
//

#ifndef chunk_data_h
#define chunk_data_h

#include "../block/block.h"

struct ChunkData {
    const long min_y;
    const long max_y;
    
    unsigned long blocks_count;
    struct Block **blocks;
};

struct ChunkData *chunk_data_create(const long min_y, const long max_y, unsigned long blocks_count, struct Block **blocks);
void chunk_data_destroy(struct ChunkData *data);

void chunk_data_remove_block(struct ChunkData *data, struct Block *block, _Bool destroy);
void chunk_data_add_block(struct ChunkData *data, struct Block *block);

#endif /* chunk_data_h */
