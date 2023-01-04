//
//  item_meta.h
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef item_meta_h
#define item_meta_h

#include "../enchantment_type.h"

struct ItemMeta {
    char *display_name;
    char *lore;
    
    unsigned short enchants_count;
    struct Enchant *enchants;
};

struct ItemMeta *item_meta_create(char *display_name, char *lore, unsigned short enchants_count, struct Enchant *enchants);
struct ItemMeta *item_meta_clone(struct ItemMeta *meta);
void item_meta_destroy(struct ItemMeta *meta);

_Bool item_meta_is_similar(struct ItemMeta *item_meta1, struct ItemMeta *item_meta2);

struct Enchant *item_meta_get_enchants(struct ItemMeta *meta);
struct Enchant *item_meta_get_enchant(struct ItemMeta *meta, struct EnchantmentType enchantment);

#endif /* item_meta_h */
