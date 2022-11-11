//
//  projectile_arrow.h
//  quark
//
//  Created by Evan Anderson on 11/9/22.
//

#ifndef projectile_arrow_h
#define projectile_arrow_h

#include "../projectile.h"

struct ProjectileArrow {
    Projectile projectile;
    
    double damage;
    int pierce_level;
};

void projectile_arrow_destroy(struct ProjectileArrow arrow);

#endif /* projectile_arrow_h */
