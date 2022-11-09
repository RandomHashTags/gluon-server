//
//  damageable.h
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#ifndef damageable_h
#define damageable_h

#include <stdio.h>
#include "entity.h"
#include "entity_damage_result.h"

typedef struct Damageable {
    Entity *entity;
    
    double health;
    double health_maximum;
} Damageable;

void freeDamageable(Damageable *damageable);

enum EntityDamageResult damageDamageable(Damageable *damageable, double amount);
_Bool isDead(Damageable *damageable);

#endif /* damageable_h */
