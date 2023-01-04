//
//  tameable.c
//  gluon
//
//  Created by Evan Anderson on 11/12/22.
//

#include <stdlib.h>
#include "tameable.h"

void tameable_destroy(struct Tameable *tameable) {
    living_entity_destroy(tameable->entity);
    free(tameable);
}
