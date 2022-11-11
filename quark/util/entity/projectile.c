//
//  projectile.c
//  quark
//
//  Created by Evan Anderson on 11/9/22.
//

#include <stdlib.h>
#include "projectile.h"
#include "entity.h"

void projectile_destroy(Projectile *projectile) {
    entity_destroy(projectile->entity);
    free(projectile->shooter);
    free(projectile);
}
