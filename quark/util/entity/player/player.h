//
//  player.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef player_h
#define player_h

#include <stdio.h>
#include "living_entity.h"
#include "itemstack.h"
#include "gamemode.h"

struct Player {
    LivingEntity living_entity;
    const char name[32];
    char list_name[32];
    
    int played_first;
    int played_last;
    
    enum Gamemode gamemode;
    _Bool is_flying;
    _Bool is_sneaking;
    _Bool is_sprinting;
    
    float experience;
    float experience_total;
    int experience_level;
    float saturation;
    int food_level;
    
    struct Location bed_spawn_location;
    
    void (*saveData)(void);
    void (*sendMessage)(char message[50]);
};

#endif /* player_h */
