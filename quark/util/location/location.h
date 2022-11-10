//
//  location.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef location_h
#define location_h

#include <stdio.h>
#include <stdlib.h>
#include "world.h"

struct Location {
    const struct World *world;
    float x;
    float y;
    float z;
};

void location_destroy(struct Location *location);

#endif /* location_h */
