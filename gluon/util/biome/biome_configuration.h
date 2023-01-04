//
//  biome_configuration.h
//  gluon
//
//  Created by Evan Anderson on 11/18/22.
//

#ifndef biome_configuration_h
#define biome_configuration_h

struct BiomeConfiguration {
    const float temperature;
    const long temperature_starting_y;
    const long temperature_ending_y;
    const float temperature_drop_rate;
    
    const float downfall;
};

struct BiomeConfiguration *biome_configuration_create(const float temperature, const long temperature_starting_y, const long temperature_ending_y, const float temperature_drop_rate);
void biome_configuration_destroy(struct BiomeConfiguration *configuration);

#endif /* biome_configuration_h */
