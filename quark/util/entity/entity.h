//
//  entity.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef entity_h
#define entity_h

#include <stdio.h>
#include <stdlib.h>
#include "entity_type.h"
#include "../location/location.h"

typedef struct Entity {
    enum EntityType type;
    int uuid;
    char display_name[16];
    struct Location location;
    int fire_ticks;
    int fire_ticks_maximum;
} Entity;

void entity_destroy(Entity *entity);
void entity_tick(Entity *entity);
void entity_teleport(Entity *entity, struct Location location);
void entity_get_nearby_entities(Entity *entity, double x, double y, double z);

#endif /* entity_h */
