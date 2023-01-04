//
//  biome_configuration.c
//  gluon
//
//  Created by Evan Anderson on 11/18/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biome_configuration.h"

struct BiomeConfiguration *biome_configuration_create(const float temperature, const long temperature_starting_y, const long temperature_ending_y, const float temperature_drop_rate) {
    struct BiomeConfiguration *configuration = malloc(sizeof(struct BiomeConfiguration));
    if (!configuration) {
        printf("failed to allocate memory for a BiomeConfiguration\n");
        return NULL;
    }
    const size_t sizeof_float = sizeof(float), sizeof_long = sizeof(long);
    memcpy((float *) &configuration->temperature, &temperature, sizeof_float);
    memcpy((long *) &configuration->temperature_starting_y, &temperature_starting_y, sizeof_long);
    memcpy((long *) &configuration->temperature_ending_y, &temperature_ending_y, sizeof_long);
    memcpy((float *) &configuration->temperature_drop_rate, &temperature_drop_rate, sizeof_float);
    return configuration;
}
void biome_configuration_destroy(struct BiomeConfiguration *configuration) {
    free(configuration);
}
