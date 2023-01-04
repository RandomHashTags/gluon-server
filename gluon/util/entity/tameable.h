//
//  tameable.h
//  gluon
//
//  Created by Evan Anderson on 11/12/22.
//

#ifndef tameable_h
#define tameable_h

#include "living_entity.h"

struct Tameable {
    struct LivingEntity *entity;
    
    unsigned int owner_uuid;
    _Bool is_tamed;
};

void tameable_destroy(struct Tameable *tameable);

#endif /* tameable_h */
