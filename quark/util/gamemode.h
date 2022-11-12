//
//  gamemode.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef gamemode_h
#define gamemode_h

typedef struct Gamemode {
    const char *identifier;
} Gamemode;

extern Gamemode GAMEMODE_MINECRAFT_ADVENTURE;
extern Gamemode GAMEMODE_MINECRAFT_CREATIVE;
extern Gamemode GAMEMODE_MINECRAFT_SPECTATOR;
extern Gamemode GAMEMODE_MINECRAFT_SURVIVAL;

#endif /* gamemode_h */
