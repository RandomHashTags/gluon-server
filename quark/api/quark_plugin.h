//
//  quark_plugin.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef quark_plugin_h
#define quark_plugin_h

#include "quark_plugin_version.h"

struct QuarkPlugin {
    const char *name;
    const char *authors;
    const struct QuarkPluginVersion version;
};

void plugin_enable(struct QuarkPlugin *plugin);
void plugin_disable(struct QuarkPlugin *plugin);

#endif /* quark_plugin_h */
