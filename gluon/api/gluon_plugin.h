//
//  gluon_plugin.h
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef gluon_plugin_h
#define gluon_plugin_h

#include "../semantic_version.h"
//#include "../util/item/Material.h"

struct GluonPlugin {
    const char *name;
    const char *bundle_id;
    const char *authors;
    const struct SemanticVersion version;
    
    //const struct Material *materials;
    // TODO: added required dependencies
};

struct GluonPlugin *plugin_create(const char *name, const char *bundle_id, const char *authors, const struct SemanticVersion version);
void plugin_destroy(struct GluonPlugin *plugin);

void plugin_enable(struct GluonPlugin *plugin);
void plugin_disable(struct GluonPlugin *plugin);

//_Bool plugin_struct Material_is_armor(struct GluonPlugin *plugin, enum struct struct Material struct struct Material);

#endif /* gluon_plugin_h */
