//
//  block_location.h
//  quark
//
//  Created by Evan Anderson on 11/10/22.
//

#ifndef block_location_h
#define block_location_h

#include "../location/world.h"

struct BlockLocation {
    const struct World *world;
    const long x;
    const long y;
    const long z;
};

struct BlockLocation *block_location_create(struct World *world, const long x, const long y, const long z);
void block_location_destroy(struct BlockLocation *location);

#endif /* block_location_h */
