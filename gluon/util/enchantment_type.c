//
//  enchantment.c
//  gluon
//
//  Created by Evan Anderson on 11/4/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enchantment_type.h"
#include "../utilities.h"

struct EnchantmentType *enchantment_type_create(const char *identifier, const unsigned char weight, const unsigned short max_level, const unsigned short incompatible_with_count, const struct EnchantmentType *incompatible_with) {
    const size_t sizeof_enchantment_type = sizeof(struct EnchantmentType);
    struct EnchantmentType *type = malloc(sizeof_enchantment_type);
    if (!type) {
        printf("failed to allocate memory for a EnchantmentType\n");
        return NULL;
    }
    const char *target_identifier = malloc_string(identifier);
    if (!target_identifier) {
        free(type);
        printf("failed to allocate memory for a EnchantmentType target_identifier\n");
        return NULL;
    }
    type->identifier = identifier;
    memcpy((unsigned char *) &type->weight, &weight, sizeof(unsigned char));
    const size_t sizeof_unsigned_short = sizeof(unsigned short);
    memcpy((unsigned short *) &type->max_level, &max_level, sizeof_unsigned_short);
    memcpy((unsigned short *) &type->incompatible_with_count, &incompatible_with_count, sizeof_unsigned_short);
    memcpy((struct EnchantmentType *) type->incompatible_with, incompatible_with, incompatible_with_count * sizeof_enchantment_type);
    type->incompatible_with = incompatible_with;
    return type;
}
void enchantment_type_destroy(struct EnchantmentType *type) {
    free((char *) type->identifier);
    free((struct EnchantmentType *) type->incompatible_with);
    free(type);
}

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
