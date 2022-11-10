//
//  projectile_source.c
//  quark
//
//  Created by Evan Anderson on 11/9/22.
//

#include "projectile_source.h"

void projectile_source_destroy(struct ProjectileSource *source) {
    free(source->living_entity);
    free(source);
}
