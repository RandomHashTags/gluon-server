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
#include "../../utilities.h"

void entity_destroy(struct Entity *entity) {
    boundary_destroy(entity->boundary);
    location_destroy(entity->location);
    free((struct EntityType *) entity->type);
    free((char *) entity->display_name);
    free(entity);
}

void entity_tick(struct Entity *entity) {
    const unsigned short new_fire_ticks = entity->fire_ticks-1;
    if (new_fire_ticks >= 0) {
        entity->fire_ticks = new_fire_ticks;
    }
    
    const unsigned short new_freeze_ticks = entity->freeze_ticks-1;
    if (new_freeze_ticks >= 0) {
        entity->freeze_ticks = new_freeze_ticks;
    }
    
    struct Vector velocity = entity->velocity;
    if (entity->is_in_passthroughable) {
    }
    
    if (entity->has_gravity && !entity->is_on_ground) {
        
        struct Location *location = entity->location;
        const struct World *world = location->world;
        const float new_fall_distance = entity->fall_distance - GRAVITY_PER_TICK;
        struct Chunk *chunk;
        struct Block *target_block;
        if (new_fall_distance <= 0.00) {
            _Bool calculate_fall_damage = entity->type->receives_fall_damage;
            if (calculate_fall_damage) {
                chunk = location_get_loaded_chunk(location);
                chunk_get_loaded_block_at_xyz(chunk, location->x, location->y, location->z, target_block);
                if (target_block) {
                    const struct MaterialBlockConfiguration *configuration = target_block->material->configuration->block;
                    if (configuration->breaks_fall) {
                        calculate_fall_damage = 0;
                    }
                }
                if (calculate_fall_damage) {
                    // TODO: calculate fall damage
                    const float fall_distance_total = entity->fall_distance_total;
                    const unsigned int uuid = entity->uuid;
                    struct LivingEntity *living_entity = world_get_living_entity_from_uuid(world, uuid);
                    if (living_entity) {
                        float fall_damage_multiplier = 1.0;
                        struct EntityEquipment *equipment = living_entity->equipment;
                        if (equipment) {
                        }
                    }
                }
            }
            entity->is_on_ground = 1;
            entity->fall_distance = 0;
            entity->fall_distance_total = 0;
            velocity.y = 0;
        } else {
            entity->fall_distance = new_fall_distance;
            velocity.y -= GRAVITY_PER_TICK;
        }
        const float location_y = location->y;
        const float new_location_y = location_y - GRAVITY_PER_TICK;
        location->y -= GRAVITY_PER_TICK;
    }
}

void entity_teleport(struct Entity *entity, struct Location *location) {
    memcpy(entity->location, location, sizeof(struct Location));
}
