//
//  block_location.c
//  quark
//
//  Created by Evan Anderson on 11/10/22.
//

#include <stdlib.h>
#include "block_location.h"

void block_location_destroy(struct BlockLocation *location) {
    free((struct World *) location->world);
    free(location);
}
