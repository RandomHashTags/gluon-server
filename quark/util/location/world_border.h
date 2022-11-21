//
//  world_border.h
//  quark
//
//  Created by Evan Anderson on 11/21/22.
//

#ifndef world_border_h
#define world_border_h

#include "location.h"

struct WorldBorder {
    struct Location *center;
    float damage;
    
    long x;
    long y;
    long z;
};

#endif /* world_border_h */
