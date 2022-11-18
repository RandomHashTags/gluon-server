//
//  permission.c
//  quark
//
//  Created by Evan Anderson on 11/16/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "permission.h"
#include "../../../utilities.h"

struct Permission *permission_create(const struct QuarkPlugin *plugin, const char *identifier) {
    struct Permission *permission = malloc(sizeof(struct Permission));
    if (!permission) {
        printf("failed to allocate memory for a Permission\n");
        return NULL;
    }
    const char *target_identifier = malloc_string(identifier);
    if (!target_identifier) {
        printf("failed to allocate memory for a Permission target_identifier\n");
        free(permission);
        return NULL;
    }
    permission->plugin = plugin;
    permission->identifier = target_identifier;
    return permission;
}
void permission_destroy(struct Permission *permission) {
    free((struct QuarkPlugin *) permission->plugin);
    free((char *) permission->identifier);
    free(permission);
}
