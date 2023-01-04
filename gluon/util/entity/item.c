//
//  item.c
//  gluon
//
//  Created by Evan Anderson on 11/12/22.
//

#include <stdlib.h>
#include "item.h"

void item_destroy(struct Item *item, _Bool destroy_item_stack) {
    entity_destroy(item->entity);
    if (destroy_item_stack) {
        item_stack_destroy(item->item_stack);
    } else {
        free(item->item_stack);
    }
    free(item);
}
