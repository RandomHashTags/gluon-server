//
//  player.h
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef player_h
#define player_h

#include "permission.h"
#include "advancement.h"
#include "../living_entity.h"
#include "../../gamemode.h"
#include "../../block/block.h"
#include "../../inventory/inventory.h"
#include "../../item/item_stack.h"
#include "../../statistics/statistic_active.h"

struct Player {
    struct LivingEntity *living_entity;
    const char *name;
    char *list_name;
    
    unsigned short permissions_count;
    struct Permission **permissions;
    
    unsigned long advancements_count;
    struct Advancement **advancements;
    
    struct StatisticActive *statistics;
    
    const unsigned int first_played;
    
    struct Gamemode *gamemode;
    _Bool is_blocking;
    _Bool is_flying;
    _Bool is_op;
    _Bool is_sneaking;
    _Bool is_sprinting;
    
    unsigned int experience;
    unsigned int experience_level;
    unsigned int food_level;
    
    unsigned short block_break_delay;
    
    struct Location *bed_spawn_location;
    
    struct Inventory *inventory;
    struct Inventory *inventory_ender_chest;
    
    unsigned short open_inventories_count;
    struct Inventory **open_inventories;
    
    struct LivingEntity *spectator_target;
};

void player_destroy(struct Player *player);

void player_tick(struct Player *player);

void player_set_gamemode(struct Player *player, struct Gamemode *gamemode);
void player_set_blocking(struct Player *player, _Bool value);
void player_set_sneaking(struct Player *player, _Bool value);
void player_set_sprinting(struct Player *player, _Bool value);

void player_broke_block(struct Player *player, struct Block *block, _Bool instantly);

void player_close_open_inventories(struct Player *player, _Bool remove_from_viewers);

_Bool player_has_permission(struct Player *player, const char *identifier);
_Bool player_has_advancement(struct Player *player, const char *identifier);

#endif /* player_h */
