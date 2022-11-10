//
//  player.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "player.h"
#include "../../../events/events.h"
#include "../../../managers/event_manager.h"

void player_destroy(struct Player *player) {
    living_entity_destroy(player->living_entity);
    free((char *) player->name);
    free(player->list_name);
    free(player);
}

void player_tick(struct Player *player) {
    printf("player \"%s\" at address %p has been ticked; has %f health\n", player->name, player, player->living_entity->damageable->health);
    living_entity_tick(player->living_entity);
}

void player_set_gamemode(struct Player *player, enum Gamemode gamemode) {
    const struct PlayerGamemodeChangeEvent event = {
        .event = {
            .player = player
        },
        .gamemode = gamemode
    };
    event_manager_call_event((Event *) &event);
    if (!event.event.event.is_cancelled) {
        player->gamemode = gamemode;
    }
}

void player_set_blocking(struct Player *player, _Bool value) {
    const struct PlayerToggleBlockingEvent event = {
        .event = {
            .player = player
        },
        .value = value
    };
    event_manager_call_event((Event *) &event);
    if (!event.event.event.is_cancelled) {
        player->is_blocking = value;
    }
}

void player_set_sneaking(struct Player *player, _Bool value) {
    const struct PlayerToggleSneakEvent event = {
        .event = {
            .player = player
        },
        .value = value
    };
    event_manager_call_event((Event *) &event);
    if (!event.event.event.is_cancelled) {
        player->is_sneaking = value;
    }
}

void player_set_sprinting(struct Player *player, _Bool value) {
    const struct PlayerToggleSprintingEvent event = {
        .event = {
            .player = player
        },
        .value = value
    };
    event_manager_call_event((Event *) & event);
    if (!event.event.event.is_cancelled) {
        player->is_sprinting = value;
    }
}
