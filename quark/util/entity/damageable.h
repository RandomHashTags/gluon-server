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

struct Damageable {
    struct Entity *entity;
    
    float health;
    float health_maximum;
};

void damageable_destroy(struct Damageable *damageable);

enum EntityDamageResult damageable_damage(struct Damageable *damageable, double amount);
_Bool damageable_is_dead(struct Damageable *damageable);

#endif /* damageable_h */
