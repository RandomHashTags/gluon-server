//
//  permission.c
//  quark
//
//  Created by Evan Anderson on 11/16/22.
//

#include <stdlib.h>
#include "permission.h"

void permission_destroy(struct Permission *permission) {
    free((struct QuarkPlugin *) permission->plugin);
    free((char *) permission->identifier);
    free(permission);
}
