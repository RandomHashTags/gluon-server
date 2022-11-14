//
//  gamemode.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef gamemode_h
#define gamemode_h

struct Gamemode {
    const char *identifier;
};

extern struct Gamemode GAMEMODE_MINECRAFT_ADVENTURE;
extern struct Gamemode GAMEMODE_MINECRAFT_CREATIVE;
extern struct Gamemode GAMEMODE_MINECRAFT_SPECTATOR;
extern struct Gamemode GAMEMODE_MINECRAFT_SURVIVAL;

#endif /* gamemode_h */
