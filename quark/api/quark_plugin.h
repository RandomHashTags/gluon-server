//
//  quark_plugin.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef quark_plugin_h
#define quark_plugin_h

#include "../semantic_version.h"
//#include "../util/item/struct struct Material.h"

struct QuarkPlugin {
    const char *name;
    const char *bundle_id;
    const char *authors;
    const struct SemanticVersion version;
    //const enum struct struct Material *struct Materials;
};

struct QuarkPlugin *plugin_create(const char *name, const char *bundle_id, const char *authors, const struct SemanticVersion version);
void plugin_destroy(struct QuarkPlugin *plugin);

void plugin_enable(struct QuarkPlugin *plugin);
void plugin_disable(struct QuarkPlugin *plugin);

//_Bool plugin_struct Material_is_armor(struct QuarkPlugin *plugin, enum struct struct Material struct struct Material);

#endif /* quark_plugin_h */
