//
//  material_names.c
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#include <stdlib.h>
#include "material_names.h"

void material_names_destroy(struct MaterialNames *names) {
    free((char *) names->english);
    free(names);
}
