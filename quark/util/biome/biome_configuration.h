//
//  biome_configuration.h
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#ifndef biome_configuration_h
#define biome_configuration_h

struct BiomeConfiguration {
    const short temperature_starting;
    const long temperature_starting_y;
    const long temperature_ending_y;
    const short temperature_drop_rate;
};

struct BiomeConfiguration *biome_configuration_create(const short temperature_starting, const long temperature_starting_y, const long temperature_ending_y, const short temperature_drop_rate);
void biome_configuration_destroy(struct BiomeConfiguration *configuration);

#endif /* biome_configuration_h */
