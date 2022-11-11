//
//  entity_equipment.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef entity_equipment_h
#define entity_equipment_h

#include "../item/item_stack.h"

struct EntityEquipment {
    struct ItemStack item_in_main_hand;
    struct ItemStack item_in_off_hand;
    
    struct ItemStack helmet;
    struct ItemStack chestplate;
    struct ItemStack leggings;
    struct ItemStack boots;
};

#endif /* entity_equipment_h */
