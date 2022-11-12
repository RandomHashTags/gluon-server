//
//  item_meta.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef item_meta_h
#define item_meta_h

#include "../enchantment_type.h"

struct ItemMeta {
    char *display_name;
    char lore[30][30];
    
    struct Enchant *enchants;
};

void item_meta_destroy(struct ItemMeta *meta);

struct Enchant *item_meta_get_enchants(struct ItemMeta *meta);
_Bool item_meta_has_enchant(struct ItemMeta *meta, struct EnchantmentType enchantment);

#endif /* item_meta_h */
