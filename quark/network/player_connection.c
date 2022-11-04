//
//  player_connection.c
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#include <stdlib.h>
#include "player_connection.h"

void disconnect(struct PlayerConnection *player, char reason[32]) {
    free(player->player);
}
