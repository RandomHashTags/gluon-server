//
//  dye_color.c
//  quark
//
//  Created by Evan Anderson on 11/12/22.
//

#include <stdlib.h>
#include "dye_color.h"

void dye_color_destroy(struct DyeColor *color) {
    free((char *) color->identifier);
    free(color);
}
