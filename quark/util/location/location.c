//
//  location.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdlib.h>
#include "location.h"

void location_destroy(struct Location *location) {
    free((struct World *) location->world);
    free(location);
}

void location_get_chunk(struct Location *location) {
    const int chunkX = location->x / 16;
    const int chunkZ = location->z / 16;
}
