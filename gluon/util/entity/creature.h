//
//  creature.h
//  gluon
//
//  Created by Evan Anderson on 11/4/22.
//

#ifndef creature_h
#define creature_h

#include "living_entity.h"

struct Creature {
    struct LivingEntity *living_entity;
    struct LivingEntity *target;
};

void creature_destroy(struct Creature *creature);

#endif /* creature_h */
