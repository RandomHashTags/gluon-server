//
//  potion_effect.c
//  quark
//
//  Created by Evan Anderson on 11/5/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "potion_effect.h"


struct PotionEffect *potion_effect_create(struct PotionEffectType *type, unsigned short amplifier, unsigned short duration, _Bool has_icon, _Bool has_particles, _Bool is_ambient) {
    struct PotionEffect *potion_effect = malloc(sizeof(struct PotionEffect));
    if (!potion_effect) {
        printf("failed to allocate memory for a PotionEffect\n");
        return NULL;
    }
    potion_effect->type = type;
    potion_effect->amplifier = amplifier;
    potion_effect->duration = duration;
    potion_effect->has_icon = has_icon;
    potion_effect->has_particles = has_particles;
    potion_effect->is_ambient = is_ambient;
    return potion_effect;
}
void potion_effect_destroy(struct PotionEffect *effect) {
    free((struct PotionEffectType *) effect->type);
    free(effect);
}
