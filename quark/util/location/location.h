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
    float x;
    float y;
    float z;
    float yaw;
    float pitch;
};

struct Location *location_create(struct World *world, const float x, const float y, const float z, const float yaw, const float pitch);
void location_destroy(struct Location *location);

struct Chunk *location_get_loaded_chunk(struct Location *location);

#endif /* location_h */
