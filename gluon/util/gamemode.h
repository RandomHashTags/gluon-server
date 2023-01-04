//
//  gamemode.h
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef gamemode_h
#define gamemode_h

struct Gamemode {
    const char *identifier;
    
    const _Bool allows_flight;
    
    const _Bool can_break_blocks;
    const _Bool can_breathe_underwater;
    const _Bool can_pickup_items;
    const _Bool can_place_blocks;
    
    const _Bool is_affected_by_gravity;
    
    const _Bool is_damageable;
    const _Bool is_invisible;
    
    const _Bool losses_hunger;
};

void gamemode_destroy(struct Gamemode *gamemode);

extern struct Gamemode GAMEMODE_MINECRAFT_ADVENTURE;
extern struct Gamemode GAMEMODE_MINECRAFT_CREATIVE;
extern struct Gamemode GAMEMODE_MINECRAFT_SPECTATOR;
extern struct Gamemode GAMEMODE_MINECRAFT_SURVIVAL;

#endif /* gamemode_h */
