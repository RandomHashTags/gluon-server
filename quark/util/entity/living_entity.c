//
//  living_entity.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "living_entity.h"
#include "../../utilities.h"

void living_entity_destroy(LivingEntity *entity) {
    damageable_destroy(entity->damageable);
    potion_effect_destroy(entity->potion_effects);
    free(entity->killer);
    free(entity);
}

void living_entity_tick(LivingEntity *entity) {
    printf("ticking LivingEntity at address %p with uuid %d with no_damage_ticks_maximum %d\n", &entity, entity->damageable->entity->uuid, entity->no_damage_ticks_maximum);
    const int noDamageTicks = entity->no_damage_ticks-1;
    if (noDamageTicks >= 0) {
        entity->no_damage_ticks = noDamageTicks;
    }
    
    struct PotionEffect *potionEffects = entity->potion_effects;
    const int potionEffectMemorySize = sizeof(struct PotionEffect);
    const int potionEffectsCount = sizeof(*potionEffects) / potionEffectMemorySize;
    for (int i = 0; i < potionEffectsCount; i++) {
        struct PotionEffect *potionEffect = &potionEffects[i];
        const int newPotionEffectDuration = potionEffect->duration - 1;
        if (newPotionEffectDuration == 0) {
            potion_effect_destroy(potionEffect);
            for (int j = i; j < potionEffectsCount-1; j++) {
                memmove(&potionEffects[j], &potionEffects[j+1], potionEffectMemorySize);
            }
            i -= 1;
        } else {
            potionEffect->duration = newPotionEffectDuration;
        }
    }
    
    entity_tick(entity->damageable->entity);
}

enum EntityDamageResult living_entity_damage(LivingEntity *entity, double amount) {
    const enum EntityDamageResult result = damageable_damage(entity->damageable, amount);
    if (result == ENTITY_DAMAGE_RESULT_SUCCESS) {
        entity->no_damage_ticks = entity->no_damage_ticks_maximum;
    }
    return result;
}

_Bool living_entity_has_potion_effect(LivingEntity *entity, enum PotionEffectType type) {
    struct PotionEffect *potionEffects = entity->potion_effects;
    const int potionEffectsCount = sizeof(*potionEffects) / sizeof(&potionEffects[0]);
    for (int i = 0; i < potionEffectsCount; i++) {
        const struct PotionEffect *effect = &potionEffects[i];
        if (effect->type == type) {
            return 1;
        }
    }
    return 0;
}
void living_entity_add_potion_effect(LivingEntity *entity, enum PotionEffectType type, int amplifier, int duration) {
    if (living_entity_has_potion_effect(entity, type)) {
        
    } else {
        struct PotionEffect effect = {
            .type = type,
            .amplifier = amplifier,
            .duration = duration * TICKS_PER_SECOND_MULTIPLIER
        };
        
        struct PotionEffect *potionEffects = entity->potion_effects;
        const int potionEffectMemorySize = sizeof(struct PotionEffect);
        const int potionEffectsCount = sizeof(*potionEffects) / potionEffectMemorySize;
        memmove((struct PotionEffect *) &entity->potion_effects[potionEffectsCount], &effect, potionEffectMemorySize);
    }
}
void living_entity_remove_potion_effect(LivingEntity *entity, enum PotionEffectType type) {
    struct PotionEffect *potionEffects = entity->potion_effects;
    int potionEffectsCount = sizeof(*potionEffects) / sizeof(&potionEffects[0]);
    for (int i = 0; i < potionEffectsCount; i++) {
        struct PotionEffect *potionEffect = &potionEffects[i];
        if (potionEffect->type == type) {
            potion_effect_destroy(potionEffect);
            const int potionEffectSize = sizeof(struct PotionEffect);
            for (int j = i; j < potionEffectsCount-1; j++) {
                memmove((struct PotionEffect *) &potionEffects[j], &potionEffects[j+1], potionEffectSize);
            }
            i -= 1;
            potionEffectsCount -= 1;
            break;
        }
    }
}
