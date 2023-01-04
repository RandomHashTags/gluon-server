//
//  projectile.h
//  gluon
//
//  Created by Evan Anderson on 11/9/22.
//

#ifndef projectile_h
#define projectile_h

#include "entity.h"
#include "projectile_source.h"

struct Projectile {
    struct Entity *entity;
    struct ProjectileSource *shooter;
};

void projectile_destroy(struct Projectile *projectile);

void projectile_launch(struct ProjectileSource *source, struct Projectile projectile);

#endif /* projectile_h */
