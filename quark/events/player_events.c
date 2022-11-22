//
//  player_events.c
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#include "player_events.h"

const struct Event EVENT_PLAYER_JOIN =  { .identifier = "minecraft.player.join", .key = "onPlayerJoin" };
const struct Event EVENT_PLAYER_DEATH = { .identifier = "minecraft.player.death", .key = "onPlayerDeath" };
