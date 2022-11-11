//
//  chunk.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdlib.h>
#include "chunk.h"

void chunk_destroy(struct Chunk *chunk) {
    free(chunk);
}
