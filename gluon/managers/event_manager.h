//
//  event_manager.h
//  gluon
//
//  Created by Evan Anderson on 11/5/22.
//

#ifndef event_manager_h
#define event_manager_h

#include "../events/player_events.h"

struct EventManager {
};

_Bool event_manager_call_event(struct Event *event);

#endif /* event_manager_h */
