//
//  location.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "location.h"

void location_destroy(struct Location *location) {
    free((struct World *) location->world);
    free(location);
}
