//
//  event_manager.c
//  quark
//
//  Created by Evan Anderson on 11/5/22.
//

#include "event_manager.h"

void callEvent(Event *event) {
    printf("called event %d\n", event->type);
}
