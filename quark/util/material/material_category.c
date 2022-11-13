//
//  material_category.c
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#include <stdlib.h>
#include "material_category.h"

void material_category_destroy(struct MaterialCategory *category) {
    free(category);
}
