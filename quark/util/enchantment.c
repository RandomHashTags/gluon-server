//
//  enchantment.c
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#include <stdlib.h>
#include "enchantment.h"

enum EnchantmentTarget enchantment_get_enchantment_target(enum Enchantment enchantment) {
    switch (enchantment) {
        case ENCHANTMENT_ARROW_DAMAGE:
            return ENCHANTMENT_TARGET_BOW;
        default:
            return ENCHANTMENT_TARGET_ALL;
    }
}


void enchants_destroy(struct Enchant *enchants) {
    free(enchants);
}
