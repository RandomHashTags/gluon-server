//
//  quark_managers.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "events.h"

#ifndef quark_managers_h
#define quark_managers_h

struct EventListener {
    
};

struct EventManager {
};

void callEvent(const struct Event *event) {
    printf("quark_managers.callEvent, %s\n", event->name);
};

extern struct EventManager EVENT_MANAGER;

#endif /* quark_managers_h */
