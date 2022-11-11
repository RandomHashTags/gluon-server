//
//  events.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef events_h
#define events_h

#include "event_type.h"
#include "../util/entity/entity.h"
#include "../util/entity/player/player.h"

typedef struct Event {
    const _Bool is_async;
    const enum EventType type;
} Event;

typedef struct EventCancellable {
    const struct Event event;
    _Bool is_cancelled;
} EventCancellable;

typedef struct PlayerEvent {
    const struct Event event;
    struct Player *player;
} PlayerEvent;
typedef struct PlayerEventCancellable {
    const struct EventCancellable event;
    struct Player *player;
} PlayerEventCancellable;


struct PlayerJoinEvent {
    const struct PlayerEvent event;
};
struct PlayerQuitEvent {
    const struct PlayerEvent event;
};

struct PlayerGamemodeChangeEvent {
    const struct PlayerEventCancellable event;
    const enum Gamemode gamemode;
};
struct PlayerToggleBlockingEvent {
    const struct PlayerEventCancellable event;
    const _Bool value;
};
struct PlayerToggleSneakEvent {
    const struct PlayerEventCancellable event;
    const _Bool value;
};
struct PlayerToggleSprintingEvent {
    const struct PlayerEventCancellable event;
    const _Bool value;
};

#endif /* events_h */
