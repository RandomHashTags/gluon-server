//
//  entity.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entity.h"

void entity_destroy(struct Entity *entity) {
    location_destroy(entity->location);
    free((struct EntityType *) entity->type);
    free((char *) entity->display_name);
    free(entity);
}

void entity_tick(struct Entity *entity) {
    const int fireTicks = entity->fire_ticks-1;
    if (fireTicks >= 0) {
        entity->fire_ticks = fireTicks;
    }
}

void entity_teleport(struct Entity *entity, struct Location *location) {
    memcpy(entity->location, location, sizeof(struct Location));
}
