//
//  entity_equipment.c
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdlib.h>
#include "entity_equipment.h"

void entity_equipment_destroy(struct EntityEquipment *equipment) {
    item_stack_destroy(equipment->item_in_main_hand);
    item_stack_destroy(equipment->item_in_off_hand);
    item_stack_destroy(equipment->helmet);
    item_stack_destroy(equipment->chestplate);
    item_stack_destroy(equipment->leggings);
    item_stack_destroy(equipment->boots);
    free(equipment);
}
