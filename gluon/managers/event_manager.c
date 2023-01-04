//
//  event_manager.c
//  gluon
//
//  Created by Evan Anderson on 11/5/22.
//

#include <stdio.h>
#include "event_manager.h"
#include "../utilities.h"

_Bool event_manager_call_event(struct Event *event) {
    printf("called event \"%s\" with key \"%s\"\n", event->identifier, event->key);
    return 1;
}
