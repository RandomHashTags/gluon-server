//
//  world_events.h
//  gluon
//
//  Created by Evan Anderson on 11/21/22.
//

#ifndef world_events_h
#define world_events_h

#include "event.h"
#include "../util/location/world.h"

struct WorldEvent {
    const struct Event event;
    struct World *world;
};
struct WorldEventCancellable {
    const struct WorldEvent event;
    _Bool is_cancelled;
};

#endif /* world_events_h */
