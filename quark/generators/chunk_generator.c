//
//  chunk_generator.c
//  quark
//
//  Created by Evan Anderson on 11/17/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "chunk_generator.h"
#include "../utilities.h"

struct ChunkGenerator *chunk_generator_create(const char *identifier) {
    struct ChunkGenerator *generator = malloc(sizeof(struct ChunkGenerator));
    if (!generator) {
        printf("failed to allocate memory for a ChunkGenerator\n");
        return NULL;
    }
    const char *target_identifier = malloc_string(identifier);
    if (!target_identifier) {
        free(generator);
        printf("failed to allocate memory for a ChunkGenerator target_identifier\n");
        return NULL;
    }
    generator->identifier = target_identifier;
    return generator;
}
void chunk_generator_destroy(struct ChunkGenerator *generator) {
    free((char *) generator->identifier);
    free(generator);
}
