//
//  entity_type.c
//  quark
//
//  Created by Evan Anderson on 11/10/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "entity_type.h"
#include "../../utilities.h"

struct EntityType *entity_type_create(const char *identifier, unsigned short no_damage_ticks_maximum, unsigned short fire_ticks_maximum) {
    struct EntityType *type = malloc(sizeof(struct EntityType));
    if (!type) {
        printf("failed to allocate memory for a EntityType\n");
        return NULL;
    }
    const char *target_identifier = malloc_string(identifier);
    if (!target_identifier) {
        free(type);
        printf("failed to allocate memory for a EntityType target_identifier\n");
        return NULL;
    }
    type->identifier = target_identifier;
    type->no_damage_ticks_maximum = no_damage_ticks_maximum;
    type->fire_ticks_maximum = fire_ticks_maximum;
    return type;
}
void entity_type_destroy(struct EntityType *type) {
    free((char *) type->identifier);
    free(type);
}
