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
    const int uuid;
    char display_name[16];
    struct Location location;
    int fire_ticks;
    int fire_ticks_maximum;
} Entity;

void tickEntity(Entity *entity);
void teleport(Entity *entity, struct Location location);
void getNearbyEntities(Entity *entity, double x, double y, double z);

#endif /* entity_h */
