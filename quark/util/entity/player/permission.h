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
    struct QuarkPlugin *plugin;
    const char *identifier;
};

#endif /* permission_h */
