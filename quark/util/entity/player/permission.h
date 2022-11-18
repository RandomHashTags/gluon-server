//
//  permission.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef permission_h
#define permission_h

#include "../../../api/quark_plugin.h"

struct Permission {
    const struct QuarkPlugin *plugin;
    const char *identifier;
};

struct Permission *permission_create(const struct QuarkPlugin *plugin, const char *identifier);
void permission_destroy(struct Permission *permission);

#endif /* permission_h */
