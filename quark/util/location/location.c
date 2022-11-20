//
//  location.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "location.h"

struct Location *location_create(struct World *world, struct Chunk *chunk, const float x, const float y, const float z, const float yaw, const float pitch) {
    struct Location *location = malloc(sizeof(struct Location));
    if (!location) {
        printf("failed to allocate memory for a Location\n");
        return NULL;
    }
    location->world = world;
    location->chunk = chunk;
    location->x = x;
    location->y = y;
    location->z = z;
    location->yaw = yaw;
    location->pitch = pitch;
    printf("location_create; created with world at address %p\n", world);
    return location;
}
void location_destroy(struct Location *location) {
    free((struct World *) location->world);
    free(location->chunk);
    free(location);
}
