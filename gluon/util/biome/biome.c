//
//  biome.c
//  gluon
//
//  Created by Evan Anderson on 11/17/22.
//

#include <stdlib.h>
#include "../biome/biome.h"
#include "../../utilities.h"

struct Biome *biome_parse_from_json_file(const char *identifier, FILE *file) {
    struct BiomeConfiguration *configuration = NULL;
    struct Biome *biome = biome_create(identifier, configuration);
    if (!biome) {
        biome_configuration_destroy(configuration);
    }
    return biome;
}
struct Biome *biome_create(const char *identifier, const struct BiomeConfiguration *configuration) {
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
    biome->configuration = configuration;
    return biome;
}
void biome_destroy(struct Biome *biome) {
    biome_configuration_destroy((struct BiomeConfiguration *) biome->configuration);
    free((char *) biome->identifier);
    free(biome);
}
