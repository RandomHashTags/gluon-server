//
//  item_meta.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "item_meta.h"

struct ItemMeta *item_meta_create(char *display_name, char *lore, struct Enchant *enchants) {
    struct ItemMeta *meta = malloc(sizeof(struct ItemMeta));
    if (!meta) {
        printf("failed to allocate memory for a ItemMeta\n");
        return NULL;
    }
    meta->display_name = display_name;
    meta->lore = lore;
    meta->enchants = enchants;
    return meta;
}
void item_meta_destroy(struct ItemMeta *meta) {
    enchants_destroy(meta->enchants);
    free(meta->display_name);
    free(meta->lore);
    free(meta);
}

struct Enchant *item_meta_get_enchants(struct ItemMeta *meta) {
    return meta->enchants;
}
_Bool item_meta_has_enchant(struct ItemMeta *meta, struct EnchantmentType enchantment) {
    const char *identifier = enchantment.identifier;
    struct Enchant *enchants = meta->enchants;
    const int enchantsCount = sizeof(*enchants) / sizeof(&enchants[0]);
    for (int i = 0; i < enchantsCount; i++) {
        if (enchants[i].type.identifier == identifier) {
            return 1;
        }
    }
    return 0;
}
