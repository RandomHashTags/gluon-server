//
//  enchantment.c
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#include <stdlib.h>
#include "enchantment_type.h"

void enchants_destroy(struct Enchant *enchants) {
    free(enchants);
}

struct EnchantmentTarget enchantment_type_get_enchantment_target(struct EnchantmentType *enchantment) {
    return ENCHANTMENT_TARGET_MINECRAFT_ALL;
}
