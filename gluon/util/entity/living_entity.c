//
//  living_entity.c
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "living_entity.h"
#include "../../utilities.h"

void living_entity_destroy(struct LivingEntity *entity) {
    damageable_destroy(entity->damageable);
    entity_equipment_destroy(entity->equipment);
    const unsigned int potion_effect_count = entity->potion_effect_count;
    struct PotionEffect **potion_effects = entity->potion_effects;
    for (unsigned int i = 0; i < potion_effect_count; i++) {
        struct PotionEffect *potion_effect = potion_effects[i];
        potion_effect_destroy(potion_effect);
    }
    free(entity->killer);
    free(entity->leash_holder);
    free(entity);
}

void living_entity_tick(struct LivingEntity *entity) {
    const unsigned short new_no_damage_ticks = entity->no_damage_ticks - 1;
    if (new_no_damage_ticks >= 0) {
        entity->no_damage_ticks = new_no_damage_ticks;
    }
    
    struct PotionEffect **potion_effects = entity->potion_effects;
    const unsigned short potion_effect_count = entity->potion_effect_count;
    for (int i = 0; i < potion_effect_count; i++) {
        struct PotionEffect *potion_effect = potion_effects[i];
        const unsigned short new_potion_effect_duration = potion_effect->duration - 1;
        if (new_potion_effect_duration == 0) {
            potion_effect_destroy(potion_effect);
            for (int j = i; j < potion_effect_count-1; j++) {
                potion_effects[j] = potion_effects[j+1];
            }
            i -= 1;
            entity->potion_effect_count -= 1;
        } else {
            potion_effect->duration = new_potion_effect_duration;
        }
    }
    entity_tick(entity->damageable->entity);
}

enum EntityDamageResult living_entity_damage(struct LivingEntity *entity, double amount) {
    const enum EntityDamageResult result = damageable_damage(entity->damageable, amount);
    if (result == ENTITY_DAMAGE_RESULT_SUCCESS) {
        entity->no_damage_ticks = entity->no_damage_ticks_maximum;
    }
    return result;
}

struct PotionEffect *living_entity_get_potion_effect(struct LivingEntity *entity, struct PotionEffectType *type) {
    const char *type_identifier = type->identifier;
    struct PotionEffect **potion_effects = entity->potion_effects;
    const unsigned short potion_effect_count = entity->potion_effect_count;
    for (int i = 0; i < potion_effect_count; i++) {
        struct PotionEffect *effect = potion_effects[i];
        if (strcmp(type_identifier, effect->type->identifier)) {
            return effect;
        }
    }
    return NULL;
}
_Bool living_entity_add_potion_effect(struct LivingEntity *entity, struct PotionEffectType *type, unsigned short amplifier, unsigned short duration, _Bool has_icon, _Bool has_particles, _Bool is_ambient) {
    struct PotionEffect *existing_potion_effect = living_entity_get_potion_effect(entity, type);
    const unsigned short new_duration = duration * TICKS_PER_SECOND_MULTIPLIER;
    if (!existing_potion_effect) {
        existing_potion_effect->amplifier = amplifier;
        existing_potion_effect->duration = new_duration;
        existing_potion_effect->has_icon = has_icon;
        existing_potion_effect->has_particles = has_particles;
        existing_potion_effect->is_ambient = is_ambient;
    } else {
        struct PotionEffect *potion_effect = potion_effect_create(type, amplifier, duration, has_icon, has_particles, is_ambient);
        if (!potion_effect) {
            return 0;
        }
        const unsigned short potion_effect_count = entity->potion_effect_count;
        entity->potion_effects[potion_effect_count] = potion_effect;
    }
    return 1;
}
void living_entity_remove_potion_effect(struct LivingEntity *entity, struct PotionEffectType type) {
    const char *typeIdentifier = type.identifier;
    struct PotionEffect **potion_effects = entity->potion_effects;
    const unsigned short potion_effect_count = entity->potion_effect_count;
    for (int i = 0; i < potion_effect_count; i++) {
        struct PotionEffect *potionEffect = potion_effects[i];
        if (strcmp(typeIdentifier, potionEffect->type->identifier)) {
            potion_effect_destroy(potionEffect);
            for (int j = i; j < potion_effect_count-1; j++) {
                potion_effects[j] = potion_effects[j+1];
            }
            i -= 1;
            entity->potion_effect_count -= 1;
            break;
        }
    }
}

void living_entity_damage_item_in_main_hand(struct LivingEntity *entity, unsigned short amount) {
    struct EntityEquipment *equipment = entity->equipment;
    struct ItemStack *item_stack = equipment->item_in_main_hand;
    if (item_stack != NULL) {
        const struct MaterialItemConfiguration *configuration = item_stack->material->configuration->item;
        if (configuration != NULL && configuration->has_durability) {
            const unsigned short new_durability = item_stack->durability - 1;
            if (new_durability == 0) {
                item_stack = NULL;
                item_stack_destroy(item_stack);
            } else {
                item_stack->durability = new_durability;
            }
        }
    }
}
