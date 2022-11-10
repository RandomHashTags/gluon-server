//
//  living_entity.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <string.h>
#include "living_entity.h"

void living_entity_destroy(LivingEntity entity) {
    damageable_destroy(&entity.damageable);
    potion_effect_destroy(entity.potion_effects);
    free(entity.killer);
    free(entity.potion_effects);
}

void living_entity_tick(LivingEntity entity) {
    printf("ticking LivingEntity at address %p with uuid %d with no_damage_ticks_maximum %d\n", &entity, entity.damageable.entity.uuid, entity.no_damage_ticks_maximum);
    const int noDamageTicks = entity.no_damage_ticks-1;
    if (noDamageTicks >= 0) {
        entity.no_damage_ticks = noDamageTicks;
    }
    
    struct PotionEffect *potionEffects = entity.potion_effects;
    if (potionEffects != NULL) {
        const int potionEffectsCount = sizeof(*potionEffects) / sizeof(&potionEffects[0]);
        for (int i = 0; i < potionEffectsCount; i++) {
            struct PotionEffect *potionEffect = &potionEffects[i];
            const int newPotionEffectDuration = potionEffect->duration - 1;
            if (newPotionEffectDuration == 0) {
                potion_effect_destroy(potionEffect);
                for (int j = i; j < potionEffectsCount; j++) {
                    memcpy(&potionEffects[j], &potionEffects[i+1], sizeof(struct PotionEffect));
                }
                i -= 1;
            } else {
                potionEffect->duration = newPotionEffectDuration;
            }
        }
    }
    
    entity_tick(&entity.damageable.entity);
}

enum EntityDamageResult living_entity_damage(LivingEntity entity, double amount) {
    const enum EntityDamageResult result = damageable_damage(&entity.damageable, amount);
    if (result == ENTITY_DAMAGE_RESULT_SUCCESS) {
        entity.no_damage_ticks = entity.no_damage_ticks_maximum;
    }
    return result;
}

_Bool living_entity_has_potion_effect(LivingEntity entity, enum PotionEffectType type) {
    struct PotionEffect *potionEffects = entity.potion_effects;
    for (int i = 0; i < 10; i++) {
        const struct PotionEffect *effect = &potionEffects[i];
        if (effect != NULL && effect->type == type) {
            return 1;
        }
    }
    return 0;
}
void living_entity_add_potion_effect(LivingEntity entity, enum PotionEffectType type, int amplifier, int duration) {
    if (living_entity_has_potion_effect(entity, type)) {
        
    } else {
        struct PotionEffect *potionEffects = entity.potion_effects;
        const int potionEffectsCount = sizeof(*potionEffects) / sizeof(&potionEffects[0]);
        
        struct PotionEffect effect = {
            .type = type,
            .amplifier = amplifier,
            .duration = duration
        };
        memcpy((struct PotionEffect *) &entity.potion_effects[potionEffectsCount], &effect, sizeof(struct PotionEffect));
    }
}
void living_entity_remove_potion_effect(LivingEntity entity, enum PotionEffectType type) {
    struct PotionEffect *potionEffects = entity.potion_effects;
    const int potionEffectsCount = sizeof(*potionEffects) / sizeof(&potionEffects[0]);
    for (int i = 0; i < potionEffectsCount; i++) {
        struct PotionEffect *potionEffect = &potionEffects[i];
        if (potionEffect->type == type) {
            potion_effect_destroy(potionEffect);
            for (int j = i; j < potionEffectsCount-1; j++) {
                memmove((struct PotionEffect *) &potionEffects[j], &potionEffects[j+1], sizeof(struct PotionEffect));
            }
            i -= 1;
            break;
        }
    }
}
