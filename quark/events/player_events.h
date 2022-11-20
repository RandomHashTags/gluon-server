//
//  player_events.h
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#ifndef player_events_h
#define player_events_h

#include "event.h"
#include "../util/entity/player/player.h"

struct PlayerEvent {
    const struct Event event;
    struct Player *player;
};
struct PlayerEventCancellable {
    const struct EventCancellable event;
    struct Player *player;
};

struct PlayerDeathEvent {
    const struct PlayerEvent event;
};

struct PlayerJoinEvent {
    const struct PlayerEvent event;
};
struct PlayerQuitEvent {
    const struct PlayerEvent event;
};

struct PlayerGamemodeChangeEvent {
    const struct PlayerEventCancellable event;
    const struct Gamemode *gamemode;
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

#endif /* player_events_h */
