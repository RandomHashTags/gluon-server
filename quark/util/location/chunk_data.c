//
//  chunk_data.c
//  quark
//
//  Created by Evan Anderson on 11/20/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chunk_data.h"

struct ChunkData *chunk_data_create(const long min_y, const long max_y, unsigned long blocks_count, struct Block **blocks) {
    struct ChunkData *data = malloc(sizeof(struct ChunkData));
    if (!data) {
        printf("failed to allocate memory for a ChunkData\n");
        return NULL;
    }
    const size_t sizeof_long = sizeof(long);
    memcpy((long *) &data->min_y, &min_y, sizeof_long);
    memcpy((long *) &data->max_y, &max_y, sizeof_long);
    data->blocks_count = blocks_count;
    data->blocks = blocks;
    return data;
}
void chunk_data_destroy(struct ChunkData *data) {
    const unsigned long blocks_count = data->blocks_count;
    struct Block **blocks = data->blocks;
    for (unsigned long i = 0; i < blocks_count; i++) {
        struct Block *block = blocks[i];
        block_destroy(block);
    }
    free(data);
}

void chunk_data_remove_block(struct ChunkData *data, struct Block *block, _Bool destroy_block) {
    const unsigned long blocks_count = data->blocks_count;
    struct Block **blocks = data->blocks;
    for (unsigned long i = 0; i < blocks_count; i++) {
        struct Block *target_block = blocks[i];
        if (block == target_block) {
            for (unsigned long j = i; j < blocks_count-1; j++) {
                blocks[j] = blocks[j+1];
            }
            blocks[blocks_count-1] = NULL;
            data->blocks_count -= 1;
            if (destroy_block) {
                block_destroy(block);
            }
            break;
        }
    }
}
void chunk_data_add_block(struct ChunkData *data, struct Block *block) {
    struct Block **blocks = data->blocks;
    blocks[data->blocks_count] = block;
    data->blocks_count += 1;
}
