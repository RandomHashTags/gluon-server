//
//  projectile_arrow.c
//  quark
//
//  Created by Evan Anderson on 11/9/22.
//

#include "projectile_arrow.h"

void projectile_arrow_destroy(struct ProjectileArrow *arrow) {
    projectile_destroy(arrow->projectile);
    free(arrow);
}
