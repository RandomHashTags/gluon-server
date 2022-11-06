//
//  event_listener.h
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#ifndef event_listener_h
#define event_listener_h

#include <stdio.h>
#include "quark_plugin.h"
#include "../events/event_type.h"

typedef struct EventListener {
    const struct QuarkPlugin *plugin;
    const enum EventType types[];
} EventListener;

#endif /* event_listener_h */
