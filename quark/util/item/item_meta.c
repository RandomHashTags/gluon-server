//
//  item_meta.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "item_meta.h"
#include "../../utilities.h"

struct ItemMeta *item_meta_create(char *display_name, char *lore, unsigned short enchants_count, struct Enchant *enchants) {
    struct ItemMeta *meta = malloc(sizeof(struct ItemMeta));
    if (!meta) {
        printf("failed to allocate memory for a ItemMeta\n");
        return NULL;
    }
    
    char *target_display_name = malloc_string(display_name);
    if (!target_display_name) {
        free(meta);
        printf("failed to allocate memory for a ItemMeta display_name\n");
        return NULL;
    }
    
    char *target_lore = malloc_string(lore);
    if (!target_lore) {
        free(meta);
        free(target_display_name);
        printf("failed to allocate memory for a ItemMeta lore\n");
        return NULL;
    }
    
    meta->display_name = target_display_name;
    meta->lore = target_lore;
    meta->enchants_count = enchants_count;
    meta->enchants = enchants;
    return meta;
}
struct ItemMeta *item_meta_clone(struct ItemMeta *meta) {
    return item_meta_create(meta->display_name, meta->lore, meta->enchants_count, meta->enchants);
}
void item_meta_destroy(struct ItemMeta *meta) {
    enchants_destroy(meta->enchants_count, meta->enchants);
    free(meta->display_name);
    free(meta->lore);
    free(meta);
}

_Bool item_meta_is_similar(struct ItemMeta *item_meta1, struct ItemMeta *item_meta2) {
    if (item_meta1 == item_meta2) {
        return 1;
    } else if ((item_meta1 == NULL && item_meta2 != NULL) || (item_meta1 != NULL && item_meta2 == NULL)) {
        return 0;
    } else {
        return item_meta1->display_name == item_meta2->display_name && item_meta1->lore == item_meta2->lore;
    }
}

struct Enchant *item_meta_get_enchants(struct ItemMeta *meta) {
    return meta->enchants;
}
struct Enchant *item_meta_get_enchant(struct ItemMeta *meta, struct EnchantmentType enchantment) {
    const char *identifier = enchantment.identifier;
    struct Enchant *enchants = meta->enchants;
    const int enchantsCount = sizeof(*enchants) / sizeof(&enchants[0]);
    for (int i = 0; i < enchantsCount; i++) {
        struct Enchant *enchant = &enchants[i];
        if (enchant->type->identifier == identifier) {
            return enchant;
        }
    }
    return NULL;
}
