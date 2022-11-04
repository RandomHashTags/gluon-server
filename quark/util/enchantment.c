//
//  enchantment.c
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#include "enchantment.h"

enum EnchantmentTarget getEnchantmentTarget(enum Enchantment enchantment) {
    switch (enchantment) {
        case ENCHANTMENT_ARROW_DAMAGE:
            return ENCHANTMENT_TARGET_BOW;
        default:
            return ENCHANTMENT_TARGET_ALL;
    }
}
