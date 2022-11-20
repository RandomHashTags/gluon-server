//
//  player.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "../../block/block.h"
#include "../../../events/player_events.h"
#include "../../../managers/event_manager.h"
#include "../../../utilities.h"

void player_destroy(struct Player *player) {
    living_entity_destroy(player->living_entity);
    location_destroy(player->bed_spawn_location);
    inventory_destroy(player->inventory);
    inventory_destroy(player->inventory_ender_chest);
    free((char *) player->name);
    free(player->gamemode);
    free(player->list_name);
    free(player->permissions);
    free(player->advancements);
    free(player->spectator_target);
    free(player);
}

void player_tick(struct Player *player) {
    printf("player \"%s\" at address %p has been ticked; has %f health\n", player->name, player, player->living_entity->damageable->health);
    living_entity_tick(player->living_entity);
    
    const unsigned short new_block_break_delay = player->block_break_delay - 1;
    if (new_block_break_delay >= 0) {
        player->block_break_delay = new_block_break_delay;
    }
}

void player_set_gamemode(struct Player *player, struct Gamemode *gamemode) {
    struct PlayerGamemodeChangeEvent event = {
        .event = {
            .player = player
        },
        .gamemode = gamemode
    };
    event_manager_call_event((struct Event *) &event);
    if (!event.event.event.is_cancelled) {
        struct Gamemode *previous_gamemode = player->gamemode;
        
        const _Bool gamemode_allows_flight = gamemode->allows_flight;
        if (previous_gamemode->allows_flight != gamemode_allows_flight) {
            player->is_flying = gamemode_allows_flight;
        }
        
        player->gamemode = gamemode;
        
        struct LivingEntity *living_entity = player->living_entity;
        living_entity->can_breathe_underwater = gamemode->can_breathe_underwater;
        living_entity->can_pickup_items = gamemode->can_pickup_items;
        
        struct Entity *entity = living_entity->damageable->entity;
        entity->is_affected_by_gravity = gamemode->is_affected_by_gravity;
        entity->is_damageable = gamemode->is_damageable;
    }
}

void player_set_blocking(struct Player *player, _Bool value) {
    struct PlayerToggleBlockingEvent event = {
        .event = {
            .player = player
        },
        .value = value
    };
    event_manager_call_event((struct Event *) &event);
    if (!event.event.event.is_cancelled) {
        player->is_blocking = value;
    }
}

void player_set_sneaking(struct Player *player, _Bool value) {
    struct PlayerToggleSneakEvent event = {
        .event = {
            .player = player
        },
        .value = value
    };
    event_manager_call_event((struct Event *) &event);
    if (!event.event.event.is_cancelled) {
        player->is_sneaking = value;
    }
}

void player_set_sprinting(struct Player *player, _Bool value) {
    struct PlayerToggleSprintingEvent event = {
        .event = {
            .player = player
        },
        .value = value
    };
    event_manager_call_event((struct Event *) &event);
    if (!event.event.event.is_cancelled) {
        player->is_sprinting = value;
    }
}

void player_broke_block(struct Player *player, struct Block *block, _Bool instantly) {
    struct PlayerBreakBlockEvent breakEvent = {
        .event = {
            .player = player
        },
        .block = block,
        .instantly = instantly,
        .drop_items = 1
    };
    event_manager_call_event((struct Event *) &breakEvent);
    if (!breakEvent.event.event.is_cancelled) {
        living_entity_damage_item_in_main_hand(player->living_entity, 1);
        if (!instantly) {
            player->block_break_delay = BLOCK_BREAK_DELAY_TICKS;
        }
        if (breakEvent.drop_items) {
            const struct MaterialConfiguration *configuration = block->material->configuration;
            if (!configuration) {
                const struct MaterialBlockConfiguration *block_configuration = configuration->block;
                if (!block_configuration) {
                }
            }
        }
        block_destroy(block);
    }
}
void player_broke_blocks(struct Player *player, struct Block *blocks, _Bool instantly, short item_damage_amount) {
    const int blocks_broken_count = sizeof(*blocks) / sizeof(&blocks[0]);
    _Bool *drop_items = malloc(blocks_broken_count * sizeof(_Bool));
    if (!drop_items) {
        printf("failed to allocate memory for a Player broke_blocks drop_items pointer\n");
        return;
    }
    struct PlayerBreakBlocksEvent breakEvent = {
        .event = {
            .player = player
        },
        .blocks = blocks,
        .instantly = instantly,
        .drop_items = drop_items
    };
    event_manager_call_event((struct Event *) &breakEvent);
    if (!breakEvent.event.event.is_cancelled) {
        living_entity_damage_item_in_main_hand(player->living_entity, item_damage_amount);
        if (!instantly) {
            player->block_break_delay = BLOCK_BREAK_DELAY_TICKS;
        }
        const _Bool *updated_drop_items = breakEvent.drop_items;
        if (!updated_drop_items) {
            for (int i = 0; i < blocks_broken_count; i++) {
                const _Bool should_drop_items = updated_drop_items[i];
                if (should_drop_items) {
                    const struct MaterialConfiguration *configuration = blocks[i].material->configuration;
                    if (!configuration) {
                        const struct MaterialBlockConfiguration *block_configuration = configuration->block;
                        if (!block_configuration) {
                        }
                    }
                }
            }
        }
        for (int i = 0; i < blocks_broken_count; i++) {
            struct Block *block = &blocks[i];
            block_destroy(block);
        }
    }
    free(drop_items);
}

_Bool player_has_permission(struct Player *player, const char *identifier) {
    const unsigned short permissions_count = player->permissions_count;
    const struct Permission *permissions = player->permissions;
    for (unsigned short i = 0; i < permissions_count; i++) {
        const struct Permission *permission = &permissions[i];
        if (identifier == permission->identifier) {
            return 1;
        }
    }
    return 0;
}
