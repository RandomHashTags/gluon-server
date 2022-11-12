//
//  tameable.h
//  quark
//
//  Created by Evan Anderson on 11/12/22.
//

#ifndef tameable_h
#define tameable_h

#include "living_entity.h"

typedef struct Tameable {
    LivingEntity *entity;
    
    int owner_uuid;
    _Bool is_tamed;
} Tameable;

#endif /* tameable_h */
