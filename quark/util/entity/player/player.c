//
//  player.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "player.h"
#include "../../../events/events.h"
#include "../../../managers/event_manager.h"

void tickPlayer(struct Player *player) {
    printf("player \"%s\" has been ticked with %f health\n", player->name, player->living_entity.damageable.health);
    tickLivingEntity(&player->living_entity);
}

void setGamemode(struct Player *player, enum Gamemode gamemode) {
    const struct PlayerGamemodeChangeEvent event = {
        .event = {
            .player = player
        },
        .gamemode = gamemode
    };
    callEvent((Event *) &event);
    if (!event.event.event.is_cancelled) {
        player->gamemode = gamemode;
    }
}

void setBlocking(struct Player *player, _Bool value) {
    const struct PlayerToggleBlockingEvent event = {
        .event = {
            .player = player
        },
        .value = value
    };
    callEvent((Event *) &event);
    if (!event.event.event.is_cancelled) {
        player->is_blocking = value;
    }
}

void setSneaking(struct Player *player, _Bool value) {
    const struct PlayerToggleSneakEvent event = {
        .event = {
            .player = player
        },
        .value = value
    };
    callEvent((Event *) &event);
    if (!event.event.event.is_cancelled) {
        player->is_sneaking = value;
    }
}

void setSprinting(struct Player *player, _Bool value) {
    const struct PlayerToggleSprintingEvent event = {
        .event = {
            .player = player
        },
        .value = value
    };
    callEvent((Event *) & event);
    if (!event.event.event.is_cancelled) {
        player->is_sprinting = value;
    }
}
