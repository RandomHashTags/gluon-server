//
//  biome.c
//  quark
//
//  Created by Evan Anderson on 11/17/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "biome.h"

struct Biome *biome_create(const char *identifier) {
    struct Biome *biome = malloc(sizeof(struct Biome));
    if (!biome) {
        printf("failed to allocate memory for a Biome\n");
        return NULL;
    }
    biome->identifier = identifier;
    return biome;
}
void biome_destroy(struct Biome *biome) {
    free((char *) biome->identifier);
    free(biome);
}
