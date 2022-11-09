//
//  potion_effect.c
//  quark
//
//  Created by Evan Anderson on 11/5/22.
//

#include "potion_effect.h"

void freePotionEffect(struct PotionEffect *effect) {
    free((enum PotionEffectType *) effect->type);
    free((int *) effect->amplifier);
    free((int *) effect->duration);
    free(effect);
}
