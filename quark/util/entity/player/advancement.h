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
    const char identifier[16];
    const char name[16];
    const char description[32];
};

#endif /* advancement_h */
