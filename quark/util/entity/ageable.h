//
//  ageable.h
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#ifndef ageable_h
#define ageable_h

#include "creature.h"

struct Ageable {
    struct Creature *creature;
    
    int age;
    _Bool age_locked;
    
    _Bool is_adult;
    _Bool can_breed;
};

void ageable_destroy(struct Ageable *ageable);

#endif /* ageable_h */
