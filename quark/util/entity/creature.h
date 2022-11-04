//
//  creature.h
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#ifndef creature_h
#define creature_h

#include <stdio.h>
#include "living_entity.h"

typedef struct Creature {
    struct LivingEntity living_entity;
    struct LivingEntity *target;
} Creature;

#endif /* creature_h */
