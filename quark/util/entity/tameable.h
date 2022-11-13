//
//  tameable.h
//  quark
//
//  Created by Evan Anderson on 11/12/22.
//

#ifndef tameable_h
#define tameable_h

#include "living_entity.h"

struct Tameable {
    struct LivingEntity *entity;
    
    int owner_uuid;
    _Bool is_tamed;
};

#endif /* tameable_h */
