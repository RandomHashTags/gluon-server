//
//  itemmeta.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef itemmeta_h
#define itemmeta_h

#include <stdio.h>
#include "../enchantment.h"

struct ItemMeta {
    char display_name[50];
    char lore[30][30];
    
    struct Enchant enchants[25];
};

#endif /* itemmeta_h */
