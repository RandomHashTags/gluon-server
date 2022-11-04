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
#include "player_damage_result.h"

struct Player {
    LivingEntity living_entity;
    const char name[16];
    char list_name[16];
    
    struct Permission permissions[8];
    struct Advancement advancements[8];
    
    int played_first;
    int played_last;
    
    enum Gamemode gamemode;
    _Bool is_blocking;
    _Bool is_flying;
    _Bool is_sneaking;
    _Bool is_sprinting;
    
    float experience;
    float experience_total;
    int experience_level;
    float saturation;
    int food_level;
    
    struct Location bed_spawn_location;
    
    struct Inventory inventory;
    struct Inventory inventory_ender_chest;
    
    void (*openInventory)(struct Inventory *inventory);
};

void deallocate(struct Player *player);

enum PlayerDamageResult damage(struct Player *player, double amount);
_Bool isDead(struct Player *player);
void saveData(void);
void sendMessage(char message[64]);

#endif /* player_h */
