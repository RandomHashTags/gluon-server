//
//  gamemode.c
//  gluon
//
//  Created by Evan Anderson on 11/12/22.
//

#include <stdlib.h>
#include "gamemode.h"

void gamemode_destroy(struct Gamemode *gamemode) {
    free((char *) gamemode->identifier);
    free(gamemode);
}

struct Gamemode GAMEMODE_MINECRAFT_ADVENTURE = { .identifier = "minecraft.adventure" };
struct Gamemode GAMEMODE_MINECRAFT_CREATIVE =  { .identifier = "minecraft.creative" };
struct Gamemode GAMEMODE_MINECRAFT_SPECTATOR = { .identifier = "minecraft.spectator" };
struct Gamemode GAMEMODE_MINECRAFT_SURVIVAL =  { .identifier = "minecraft.survival" };
