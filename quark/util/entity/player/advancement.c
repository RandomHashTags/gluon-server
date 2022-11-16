//
//  advancement.c
//  quark
//
//  Created by Evan Anderson on 11/16/22.
//

#include <stdlib.h>
#include "advancement.h"

void advancement_destroy(struct Advancement *advancement) {
    free((struct Advancement *) advancement->plugin);
    free((char *) advancement->identifier);
    free((char *) advancement->name);
    free((char *) advancement->description);
    free(advancement);
}
