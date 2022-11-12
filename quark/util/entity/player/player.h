//
//  player.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef player_h
#define player_h

#include "permission.h"
#include "advancement.h"
#include "../living_entity.h"
#include "../../gamemode.h"
#include "../../inventory/inventory.h"
#include "../../item/item_stack.h"

struct Player {
    LivingEntity *living_entity;
    const char *name;
    char *list_name;
    
    struct Permission *permissions;
    struct Advancement *advancements;
    
    const int first_played;
    
    Gamemode gamemode;
    _Bool is_blocking;
    _Bool is_flying;
    _Bool is_sneaking;
    _Bool is_sprinting;
    
    float experience;
    int experience_level;
    float saturation;
    int food_level;
    
    struct Location bed_spawn_location;
    
    struct Inventory inventory;
    struct Inventory inventory_ender_chest;
};

void player_destroy(struct Player *player);

void player_tick(struct Player *player);

void player_set_gamemode(struct Player *player, Gamemode gamemode);
void player_set_blocking(struct Player *player, _Bool value);
void player_set_sneaking(struct Player *player, _Bool value);
void player_set_sprinting(struct Player *player, _Bool value);

#endif /* player_h */
