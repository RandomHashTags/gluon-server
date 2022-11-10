//
//  block.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef block_h
#define block_h

#include "material.h"
#include "location.h"

struct Block {
    enum Material material;
    int light_level;
    
    const struct Location *location;
};

#endif /* block_h */
