//
//  entity.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "entity.h"

void tickEntity(Entity *entity) {
    const int fireTicks = entity->fire_ticks-1;
    if (fireTicks >= 0) {
        entity->fire_ticks = fireTicks;
    }
}

void teleport(Entity *entity, struct Location location) {
    entity->location = location;
}
