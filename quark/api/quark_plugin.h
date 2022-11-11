//
//  quark_plugin.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef quark_plugin_h
#define quark_plugin_h

#include "quark_plugin_version.h"
//#include "../util/item/material.h"

struct QuarkPlugin {
    const char *name;
    const char *authors;
    const struct QuarkPluginVersion version;
    //const enum Material *materials;
};

void plugin_destroy(struct QuarkPlugin *plugin);

void plugin_enable(struct QuarkPlugin *plugin);
void plugin_disable(struct QuarkPlugin *plugin);

//_Bool plugin_material_is_armor(struct QuarkPlugin *plugin, enum Material material);

#endif /* quark_plugin_h */
