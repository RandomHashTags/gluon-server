//
//  entity.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef entity_h
#define entity_h

#include <stdio.h>
#include "entity_type.h"
#include "../location/location.h"

typedef struct Entity {
    const enum EntityType type;
    const char uuid[36];
    char display_name[16];
    struct Location location;
} Entity;

#endif /* entity_h */
