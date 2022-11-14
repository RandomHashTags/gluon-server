//
//  entity.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef entity_h
#define entity_h

#include "entity_type.h"
#include "../location/location.h"
#include "../vector.h"

struct Entity {
    const struct EntityType type;
    const unsigned int uuid;
    
    char *display_name;
    
    struct Location location;
    struct Vector vector;
    
    unsigned short fire_ticks;
    unsigned short fire_ticks_maximum;
};

void entity_destroy(struct Entity *entity);

void entity_tick(struct Entity *entity);

void entity_teleport(struct Entity *entity, struct Location *location);
void entity_get_nearby_entities(struct Entity *entity, double x, double y, double z);

#endif /* entity_h */
