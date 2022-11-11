//
//  projectile.h
//  quark
//
//  Created by Evan Anderson on 11/9/22.
//

#ifndef projectile_h
#define projectile_h

#include "entity.h"
#include "projectile_source.h"

typedef struct Projectile {
    Entity entity;
    struct ProjectileSource *shooter;
} Projectile;

void projectile_destroy(Projectile projectile);

void projectile_launch(struct ProjectileSource *source, Projectile projectile);

#endif /* projectile_h */
