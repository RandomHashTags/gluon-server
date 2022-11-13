//
//  entity.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "entity.h"

void entity_destroy(struct Entity *entity) {
    free((char *) entity->display_name);
    free(entity);
}

void entity_tick(struct Entity *entity) {
    printf("ticking Entity with uuid %d and type \"%s\"\n", entity->uuid, entity->type.identifier);
    const int fireTicks = entity->fire_ticks-1;
    if (fireTicks >= 0) {
        entity->fire_ticks = fireTicks;
    }
}

void entity_teleport(struct Entity *entity, struct Location *location) {
    entity->location = *location;
}
