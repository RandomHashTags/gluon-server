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
    float x;
    float y;
    float z;
    float yaw;
    float pitch;
    const struct World *world;
};

void location_destroy(struct Location *location);

struct Chunk *location_get_chunk(struct Location *location);

#endif /* location_h */
