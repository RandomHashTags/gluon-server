//
//  entity.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "entity.h"

void freeEntity(Entity *entity) {
    free((enum EntityType *) entity->type);
    free((int *) entity->uuid);
    free((char *) entity->display_name);
    free(entity);
}

void tickEntity(Entity *entity) {
    printf("ticking Entity with uuid %d and type %d\n", *entity->uuid, *entity->type);
    const int fireTicks = entity->fire_ticks-1;
    if (fireTicks >= 0) {
        entity->fire_ticks = fireTicks;
    }
}

void teleport(Entity *entity, struct Location location) {
    entity->location = location;
}
