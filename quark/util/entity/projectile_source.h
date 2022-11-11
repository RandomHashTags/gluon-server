//
//  projectile_source.h
//  quark
//
//  Created by Evan Anderson on 11/9/22.
//

#ifndef projectile_source_h
#define projectile_source_h

#include "living_entity.h"

struct ProjectileSource {
    struct LivingEntity *living_entity;
};

void projectile_source_destroy(struct ProjectileSource *source);

#endif /* projectile_source_h */
