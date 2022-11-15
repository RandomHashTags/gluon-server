//
//  block_location.c
//  quark
//
//  Created by Evan Anderson on 11/10/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "block_location.h"

struct BlockLocation *block_location_create(struct World *world, const long x, const long y, const long z) {
    struct BlockLocation *location = malloc(sizeof(struct BlockLocation));
    if (!location) {
        printf("failed to allocate memory for a BlockLocation\n");
        return NULL;
    }
    location->world = world;
    memcpy((long *) &location->x, &x, sizeof(long));
    memcpy((long *) &location->y, &y, sizeof(long));
    memcpy((long *) &location->z, &z, sizeof(long));
    return location;
}
void block_location_destroy(struct BlockLocation *location) {
    free((struct World *) location->world);
    free(location);
}
