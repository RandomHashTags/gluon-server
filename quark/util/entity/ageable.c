//
//  ageable.c
//  quark
//
//  Created by Evan Anderson on 11/11/22.
//

#include <stdlib.h>
#include "ageable.h"

void ageable_destroy(Ageable *ageable) {
    creature_destroy(ageable->creature);
    free(ageable);
}
