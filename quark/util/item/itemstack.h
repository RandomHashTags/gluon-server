//
//  itemstack.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef itemstack_h
#define itemstack_h

#include <stdio.h>
#include "material.h"
#include "itemmeta.h"

struct ItemStack {
    const enum Material type;
    struct ItemMeta item_meta;
};

#endif /* itemstack_h */
