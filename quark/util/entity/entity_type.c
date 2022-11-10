//
//  entity_type.c
//  quark
//
//  Created by Evan Anderson on 11/10/22.
//

#include "entity_type.h"
#include "../../utilities.h"

int entity_type_get_damage_ticks_maximum(enum EntityType type) {
    switch (type) {
        default:
            return TICKS_PER_SECOND;
    }
}

int entity_type_get_fire_ticks_maximum(enum EntityType type) {
    switch (type) {
        default:
            return TICKS_PER_SECOND;
    }
}
