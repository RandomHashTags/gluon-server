//
//  quark_managers.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "../events/events.h"

#ifndef quark_managers_h
#define quark_managers_h

struct EventManager {
};

void callEvent(Event *event) {
    printf("quark_managers.callEvent, %d\n", event->type);
}

#endif /* quark_managers_h */
