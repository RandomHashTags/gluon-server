//
//  enchantment.c
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#include <stdlib.h>
#include "enchantment_type.h"

void enchant_destroy(struct Enchant *enchant) {
    free((struct EnchantmentType *) enchant->type);
    free(enchant);
}
void enchants_destroy(unsigned short enchants_count, struct Enchant *enchants) {
    for (unsigned short i = 0; i < enchants_count; i++) {
        struct Enchant *enchant = &enchants[i];
        enchant_destroy(enchant);
    }
    free(enchants);
}

struct EnchantmentTarget enchantment_type_get_enchantment_target(struct EnchantmentType *enchantment) {
    return ENCHANTMENT_TARGET_MINECRAFT_ALL;
}
