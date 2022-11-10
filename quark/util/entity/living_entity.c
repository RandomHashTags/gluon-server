//
//  living_entity.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "living_entity.h"

void living_entity_destroy(LivingEntity *entity) {
    damageable_destroy(entity->damageable);
    free(entity->killer);
    free(entity->potion_effects);
    free(entity);
}

void living_entity_tick(LivingEntity *entity) {
    printf("ticking LivingEntity with uuid %d with no_damage_ticks_maximum %d\n", entity->damageable->entity->uuid, entity->no_damage_ticks_maximum);
    const int noDamageTicks = entity->no_damage_ticks-1;
    if (noDamageTicks >= 0) {
        entity->no_damage_ticks = noDamageTicks;
    }
    
    struct PotionEffect *potionEffects = entity->potion_effects;
    if (potionEffects != NULL) {
        const int potionEffectsCount = sizeof(*potionEffects) / sizeof(&potionEffects[0]);
        for (int i = 0; i < potionEffectsCount; i++) {
            struct PotionEffect *potionEffect = &potionEffects[i];
            const int newPotionEffectDuration = *potionEffect->duration - 1;
            if (newPotionEffectDuration == 0) {
                potion_effect_destroy(potionEffect);
                for (int j = i; j < potionEffectsCount; j++) {
                    potionEffects[j] = potionEffects[i+1];
                }
                i -= 1;
            } else {
                *potionEffect->duration = newPotionEffectDuration;
            }
        }
    }
    
    entity_tick(entity->damageable->entity);
}

enum EntityDamageResult living_entity_damage(LivingEntity *entity, double amount) {
    const enum EntityDamageResult result = damageable_damage((Damageable *) entity, amount);
    if (result == ENTITY_DAMAGE_RESULT_SUCCESS) {
        entity->no_damage_ticks = entity->no_damage_ticks_maximum;
    }
    return result;
}

_Bool living_entity_has_potion_effect(LivingEntity *entity, enum PotionEffectType type) {
    struct PotionEffect *potionEffects = entity->potion_effects;
    for (int i = 0; i < 10; i++) {
        const struct PotionEffect *effect = &potionEffects[i];
        if (effect != NULL && *effect->type == type) {
            return 1;
        }
    }
    return 0;
}
void living_entity_add_potion_effect(LivingEntity *entity, enum PotionEffectType type, int amplifier, int duration) {
    if (living_entity_has_potion_effect(entity, type)) {
        
    } else {
        struct PotionEffect *potionEffects = entity->potion_effects;
        const int potionEffectsCount = sizeof(*potionEffects) / sizeof(&potionEffects[0]);
        enum PotionEffectType *typePointer = malloc(sizeof(enum PotionEffectType));
        if (!typePointer) {
            printf("failed to allocate memory for a PotionEffect PotionEffectType\n");
            return;
        }
        *typePointer = type;
        
        struct PotionEffect *effect = malloc(sizeof(struct PotionEffect));
        if (!effect) {
            printf("failed to allocate memory for a PotionEffect\n");
            return;
        }
        effect->type = typePointer;
        
        const size_t intSize = sizeof(int);
        int *amplifierPointer = malloc(intSize);
        if (!amplifierPointer) {
            printf("failed to allocate memory for a PotionEffect amplifierPointer\n");
            return;
        }
        *amplifierPointer = amplifier;
        
        int *durationPointer = malloc(intSize);
        if (!durationPointer) {
            printf("failed to allocate memory for a PotionEffect durationPointer\n");
            return;
        }
        *durationPointer = duration;
        
        effect->amplifier = amplifierPointer;
        effect->duration = durationPointer;
        
        entity->potion_effects[potionEffectsCount] = *effect;
    }
}
void living_entity_remove_potion_effect(LivingEntity *entity, enum PotionEffectType type) {
    struct PotionEffect *potionEffects = entity->potion_effects;
    const int potionEffectsCount = sizeof(*potionEffects) / sizeof(&potionEffects[0]);
    for (int i = 0; i < potionEffectsCount; i++) {
        struct PotionEffect *potionEffect = &potionEffects[i];
        if (*potionEffect->type == type) {
            potion_effect_destroy(potionEffect);
            for (int j = i; j < potionEffectsCount-1; j++) {
                potionEffects[j] = potionEffects[j+1];
            }
            i -= 1;
            break;
        }
    }
}
