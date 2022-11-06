//
//  living_entity.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "living_entity.h"

void tickLivingEntity(LivingEntity *entity) {
    const int noDamageTicks = entity->no_damage_ticks-1;
    if (noDamageTicks >= 0) {
        entity->no_damage_ticks = noDamageTicks;
    }
    tickEntity(&entity->damageable.entity);
}

enum EntityDamageResult damageLivingEntity(LivingEntity *entity, double amount) {
    const enum EntityDamageResult result = damageDamageable((Damageable *) entity, amount);
    if (result == ENTITY_DAMAGE_RESULT_SUCCESS) {
        entity->no_damage_ticks = entity->no_damage_ticks_maximum;
    }
    return result;
}

void getPotionEffects(LivingEntity *entity, struct PotionEffect potion_effects[MAXIMUM_POTION_EFFECT_TYPE_COUNT]) {
    potion_effects = entity->potion_effects;
}
_Bool hasPotionEffect(LivingEntity *entity, enum PotionEffectType type) {
    struct PotionEffect potionEffects[MAXIMUM_POTION_EFFECT_TYPE_COUNT];
    getPotionEffects(entity, potionEffects);
    for (int i = 0; i < MAXIMUM_POTION_EFFECT_TYPE_COUNT; i++) {
        const struct PotionEffect *effect = &potionEffects[i];
        if (effect != NULL && effect->type == type) {
            return 1;
        }
    }
    return 0;
}
void addPotionEffect(LivingEntity *entity, struct PotionEffect effect) {
    const enum PotionEffectType type = effect.type;
    if (hasPotionEffect(entity, type)) {
        
    } else {
        struct PotionEffect potionEffects[MAXIMUM_POTION_EFFECT_TYPE_COUNT];
        getPotionEffects(entity, potionEffects);
        for (int i = 0; i < MAXIMUM_POTION_EFFECT_TYPE_COUNT; i++) {
            const struct PotionEffect *effectPointer = &potionEffects[i];
            if (effectPointer == NULL) {
                entity->potion_effects[i] = &effect;
                break;
            }
        }
    }
}
