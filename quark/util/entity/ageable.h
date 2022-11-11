//
//  ageable.h
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#ifndef ageable_h
#define ageable_h

#include "creature.h"

typedef struct Ageable {
    Creature *creature;
    
    int age;
    _Bool age_locked;
    
    _Bool is_adult;
    _Bool can_breed;
} Ageable;

void ageable_destroy(Ageable *ageable);

#endif /* ageable_h */
