//
//  advancement.h
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef advancement_h
#define advancement_h

#include "../../../api/gluon_plugin.h"

struct Advancement {
    const struct GluonPlugin *plugin;
    const char *identifier;
    const char *name;
    const char *description;
};

void advancement_destroy(struct Advancement *advancement);

#endif /* advancement_h */
