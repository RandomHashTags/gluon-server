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

struct Event {
    const _Bool is_async;
    const enum EventType type;
};

struct EventCancellable {
    const struct Event event;
    _Bool is_cancelled;
};

struct PlayerEvent {
    const struct Event event;
    struct Player *player;
};
struct PlayerEventCancellable {
    const struct EventCancellable event;
    struct Player *player;
};


struct PlayerJoinEvent {
    const struct PlayerEvent event;
};
struct PlayerQuitEvent {
    const struct PlayerEvent event;
};

struct PlayerGamemodeChangeEvent {
    const struct PlayerEventCancellable event;
    const struct Gamemode gamemode;
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

struct PlayerBreakBlockEvent {
    const struct PlayerEventCancellable event;
    const struct Block *block;
    const _Bool instantly;
    _Bool drop_items;
};
struct PlayerBreakBlocksEvent {
    const struct PlayerEventCancellable event;
    const struct Block *blocks;
    const _Bool instantly;
    _Bool *drop_items;
};

#endif /* events_h */
