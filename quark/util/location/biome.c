//
//  biome.c
//  quark
//
//  Created by Evan Anderson on 11/17/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "biome.h"
#include "../../utilities.h"

struct Biome *biome_create(const char *identifier) {
    struct Biome *biome = malloc(sizeof(struct Biome));
    if (!biome) {
        printf("failed to allocate memory for a Biome\n");
        return NULL;
    }
    const char *target_identifier = malloc_string(identifier);
    if (!target_identifier) {
        free(biome);
        printf("failed to allocate memory for a Biome target_identifier\n");
        return NULL;
    }
    biome->identifier = target_identifier;
    return biome;
}
void biome_destroy(struct Biome *biome) {
    free((char *) biome->identifier);
    free(biome);
}
