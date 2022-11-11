//
//  quark_plugin.c
//  quark
//
//  Created by Evan Anderson on 11/9/22.
//

#include <stdlib.h>
#include "quark_plugin.h"

void plugin_destroy(struct QuarkPlugin *plugin) {
    free((char *) plugin->name);
    free((char *) plugin->authors);
    free(plugin);
}

void plugin_enable(struct QuarkPlugin *plugin) {
}
void plugin_disable(struct QuarkPlugin *plugin) {
}
