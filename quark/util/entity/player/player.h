//
//  player.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef player_h
#define player_h

#include <stdio.h>
#include "../living_entity.h"
#include "../../item/itemstack.h"
#include "gamemode.h"
#include "../../inventory/inventory.h"
#include "permission.h"
#include "advancement.h"

struct Player {
    LivingEntity living_entity;
    const char *name;
    char *list_name;
    
    struct Permission permissions[8];
    struct Advancement advancements[8];
    
    const int *first_played;
    
    enum Gamemode gamemode;
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

void tickPlayer(struct Player player);

void setGamemode(struct Player player, enum Gamemode);
void setBlocking(struct Player player, _Bool value);
void setSneaking(struct Player player, _Bool value);
void setSprinting(struct Player player, _Bool value);

#endif /* player_h */
