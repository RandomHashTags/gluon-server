//
//  world.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdlib.h>
#include "world.h"

void world_destroy(struct World *world) {
    free((char *) world->name);
    free(world);
}
