//
//  damageable.h
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#ifndef damageable_h
#define damageable_h

#include "entity.h"
#include "entity_damage_result.h"

typedef struct Damageable {
    Entity *entity;
    
    double health;
    double health_maximum;
} Damageable;

void damageable_destroy(Damageable *damageable);

enum EntityDamageResult damageable_damage(Damageable *damageable, double amount);
_Bool damageable_is_dead(Damageable *damageable);

#endif /* damageable_h */
