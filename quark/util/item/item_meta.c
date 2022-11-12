//
//  item_meta.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdlib.h>
#include "item_meta.h"

void item_meta_destroy(struct ItemMeta *meta) {
    enchants_destroy(meta->enchants);
    free(meta->display_name);
    free(meta);
}

struct Enchant *item_meta_get_enchants(struct ItemMeta *meta) {
    return meta->enchants;
}
_Bool item_meta_has_enchant(struct ItemMeta *meta, enum Enchantment enchantment) {
    struct Enchant *enchants = meta->enchants;
    const int enchantsCount = sizeof(*enchants) / sizeof(&enchants[0]);
    for (int i = 0; i < enchantsCount; i++) {
        if (enchants[i].type == enchantment) {
            return 1;
        }
    }
    return 0;
}
