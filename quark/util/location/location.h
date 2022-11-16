//
//  location.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef location_h
#define location_h

#include "world.h"

struct Location {
    const struct World *world;
    long x;
    long y;
    long z;
    unsigned short x_float;
    unsigned short y_float;
    unsigned short z_float;
    float yaw;
    float pitch;
};

struct Location *location_create(struct World *world, const long x, const long y, const long z, const unsigned x_float, const unsigned short y_float, const unsigned short z_float, const float yaw, const float pitch);
void location_destroy(struct Location *location);

struct Chunk *location_get_loaded_chunk(struct Location *location);

#endif /* location_h */
