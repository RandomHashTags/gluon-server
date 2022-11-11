//
//  event_manager.c
//  quark
//
//  Created by Evan Anderson on 11/5/22.
//

#include <stdio.h>
#include "event_manager.h"

void event_manager_call_event(Event *event) {
    printf("called event %d\n", event->type);
}
