//
//  living_entity.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef living_entity_h
#define living_entity_h

#include <stdio.h>
#include "entity.h"
#include "entity_equipment.h"

typedef struct LivingEntity {
    Entity entity;
    struct EntityEquipment equipment;
    
    _Bool canPickupItems;
    _Bool hasAI;
    
    _Bool is_collidable;
    _Bool is_leashed;
    _Bool is_swimming;
    _Bool is_riptiding;
    
    int no_damage_ticks;
    
    int air_remaining;
    int air_maximum;
    
    double health;
    double health_maximum;
} LivingEntity;

#endif /* living_entity_h */
