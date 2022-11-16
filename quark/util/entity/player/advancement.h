//
//  advancement.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef advancement_h
#define advancement_h

#include "../../../api/quark_plugin.h"

struct Advancement {
    const struct QuarkPlugin *plugin;
    const char *identifier;
    const char *name;
    const char *description;
};

void advancement_destroy(struct Advancement *advancement);

#endif /* advancement_h */
