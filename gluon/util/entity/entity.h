//
//  entity.h
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef entity_h
#define entity_h

#include "entity_type.h"
#include "../collision/boundary.h"
#include "../location/location.h"
#include "../vector.h"

struct Entity {
    const struct EntityType *type;
    const unsigned int uuid;
    
    char *display_name;
    
    struct Boundary *boundary;
    struct Location *location;
    struct Vector velocity;
    float fall_distance;
    
    _Bool is_affected_by_gravity;
    _Bool is_damageable;
    _Bool is_in_block_passthroughable;
    _Bool is_on_fire;
    _Bool is_on_ground;
    
    float height;
    
    unsigned short fire_ticks;
    unsigned short fire_ticks_maximum;
    
    unsigned short freeze_ticks;
    unsigned short freeze_ticks_maximum;
    
    unsigned char passengers_count;
    struct Entity **passengers;
    struct Entity *vehicle;
};

void entity_destroy(struct Entity *entity);

void entity_tick(struct Entity *entity);

void entity_teleport(struct Entity *entity, struct Location *location);
void entity_get_nearby_entities(struct Entity *entity, double x, double y, double z);

void entity_eject_passengers(struct Entity *entity);

#endif /* entity_h */
