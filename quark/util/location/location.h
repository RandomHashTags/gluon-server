//
//  location.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef location_h
#define location_h

#include <stdio.h>
#include "world.h"

struct Location {
    const struct World *world;
    float x;
    float y;
    float z;
};

#endif /* location_h */
