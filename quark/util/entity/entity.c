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
    entity_eject_passengers(entity);
    free((struct Entity *) entity->passengers);
    free(entity->vehicle);
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
    
    struct Location *location = entity->location;
    const float location_y = location->y;
    const struct World *world = location->world;
    
    struct Chunk *chunk = location->chunk;
    _Bool calculated_block_at_location = 0;
    struct Block *block_beneath_entity = NULL;
    struct Vector velocity = entity->velocity;
    if (entity->is_in_block_passthroughable) {
        calculated_block_at_location = 1;
        const long block_x = (long) location->x, block_y = (long) location_y , block_z = (long) location->z;
        block_beneath_entity = chunk_get_loaded_block_at_xyz(chunk, block_x, block_y-1, block_z);
    }
    
    if (entity->is_affected_by_gravity && !entity->is_on_ground) {
        const float fall_distance = entity->fall_distance;
        printf("entity_tick; entity with uuid %d isn't on ground. fall_distance=%f\n", entity->uuid, fall_distance);
        if (!calculated_block_at_location) {
            calculated_block_at_location = 1;
            const long block_x = (long) location->x, block_y = (long) location_y, block_z = (long) location->z;
            block_beneath_entity = chunk_get_loaded_block_at_xyz(chunk, block_x, block_y-1, block_z);
        }
        const struct MaterialBlockConfiguration *block_configuration = block_beneath_entity ? block_beneath_entity->material->configuration->block : NULL;
        if (!block_configuration || block_configuration->can_passthrough) {
            entity->fall_distance += GRAVITY_PER_TICK;
            velocity.y -= GRAVITY_PER_TICK;
        } else {
            struct BlockLocation *block_location = block_beneath_entity->location;
            const long block_location_y = block_location->y;
            const float block_height = block_get_height(block_beneath_entity);
            if (location_y - GRAVITY_PER_TICK <= block_location_y + block_height) {
                entity->is_on_ground = 1;
                velocity.y = 0;
            }
        }
        if (entity->is_on_ground) {
            _Bool calculate_fall_damage = entity->type->receives_fall_damage;
            if (calculate_fall_damage) {
                printf("entity_tick; calculating fall damage for entity with uuid %d\n", entity->uuid);
                if (!calculated_block_at_location) {
                    calculated_block_at_location = 1;
                    const long block_x = (long) location->x, block_y = (long) location_y, block_z = (long) location->z;
                    block_beneath_entity = chunk_get_loaded_block_at_xyz(chunk, block_x, block_y-1, block_z);
                }
                if (block_beneath_entity) {
                    const struct MaterialBlockConfiguration *configuration = block_beneath_entity->material->configuration->block;
                    calculate_fall_damage = 1;//!configuration->breaks_fall; // TODO: uncomment this | for testing only
                }
                if (calculate_fall_damage) {
                    const unsigned int uuid = entity->uuid;
                    struct LivingEntity *living_entity = world_get_living_entity_from_uuid(world, uuid);
                    printf("entity_tick; found living_entity for uuid %d=%d\n", uuid, living_entity != NULL);
                    if (living_entity) {
                        float fall_damage_multiplier = 1.0;
                        // TODO: manipulate fall_damage_multiplier based on the living entity's equipment, enchants, modifiers, etc
                        struct EntityEquipment *equipment = living_entity->equipment;
                        if (equipment) {
                        }
                        float fall_damage = fall_distance - 3;
                        if (fall_damage > 0.00) {
                            // TODO: apply fall damage to Living Entity
                            printf("applying %f fall damage to LivingEntity with UUID %d. (fell %f blocks)\n", fall_damage, uuid, fall_distance);
                        }
                    }
                }
            }
            entity->fall_distance = 0;
        }
        if (!entity->is_on_ground) {
            const float new_location_y = location_y - GRAVITY_PER_TICK;
            location->y = new_location_y;
            printf("entity's new Y location=%f\n", new_location_y);
        }
    }
}

void entity_teleport(struct Entity *entity, struct Location *location) {
    memcpy(entity->location, location, sizeof(struct Location));
}

void entity_eject_passengers(struct Entity *entity) {
    const unsigned char passengers_count = entity->passengers_count;
    struct Entity **passengers = entity->passengers;
    for (unsigned char i = 0; i < passengers_count; i++) {
        struct Entity *passenger = passengers[i];
        entity_eject_passengers(passenger);
        passenger->vehicle = NULL;
        passengers[i] = NULL;
    }
    entity->passengers_count = 0;
}
