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
    const int x;
    const int y;
    const int z;
    const struct World *world;
};

void block_location_destroy(struct BlockLocation *location);

#endif /* block_location_h */
