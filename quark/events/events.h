//
//  events.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef events_h
#define events_h

#include <stdio.h>
#include "../util/entity/entity.h"
#include "../util/entity/player/player.h"
#include "event_type.h"

typedef struct Event {
    const _Bool is_async;
    const enum EventType type;
} Event;

typedef struct PlayerEvent {
    const struct Event event;
    struct Player *player;
} PlayerEvent;

struct PlayerJoinEvent {
    const struct PlayerEvent event;
};

struct PlayerQuitEvent {
    const struct PlayerEvent event;
};

#endif /* events_h */
