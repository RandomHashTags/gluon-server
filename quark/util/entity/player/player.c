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
#include "../../../events/events.h"
#include "../../../managers/event_manager.h"
#include "../../../utilities.h"

void player_destroy(struct Player *player) {
    living_entity_destroy(player->living_entity);
    inventory_destroy(player->inventory);
    inventory_destroy(player->inventory_ender_chest);
    free((char *) player->name);
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

void player_set_gamemode(struct Player *player, struct Gamemode gamemode) {
    const struct PlayerGamemodeChangeEvent event = {
        .event = {
            .player = player
        },
        .gamemode = gamemode
    };
    event_manager_call_event((struct Event *) &event);
    if (!event.event.event.is_cancelled) {
        memcpy(&player->gamemode, &gamemode, sizeof(struct Gamemode));
    }
}

void player_set_blocking(struct Player *player, _Bool value) {
    const struct PlayerToggleBlockingEvent event = {
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
    const struct PlayerToggleSneakEvent event = {
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
    const struct PlayerToggleSprintingEvent event = {
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
        block_destroy(block);
        living_entity_damage_item_in_main_hand(player->living_entity, 1);
        if (!instantly) {
            player->block_break_delay = BLOCK_BREAK_DELAY_TICKS;
        }
        if (breakEvent.drop_items) {
            const struct MaterialConfiguration *configuration = block->material->configuration;
            if (configuration != NULL) {
                const struct MaterialBlockConfiguration *blockConfiguration = configuration->block_configuration;
                if (blockConfiguration != NULL) {
                }
            }
        }
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
        if (updated_drop_items != NULL) {
            for (int i = 0; i < blocks_broken_count; i++) {
                const _Bool should_drop_items = updated_drop_items[i];
                if (should_drop_items) {
                    const struct MaterialConfiguration *configuration = blocks[i].material->configuration;
                    if (configuration != NULL) {
                        const struct MaterialBlockConfiguration *blockConfiguration = configuration->block_configuration;
                        if (blockConfiguration != NULL) {
                        }
                    }
                }
            }
        }
    }
}
