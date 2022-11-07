//
//  player_connection.h
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#ifndef player_connection_h
#define player_connection_h

#include <stdio.h>
#include "../util/entity/player/player.h"

struct PlayerConnection {
    struct Player player;
    int ping;
    int chat_cooldown;
};

void chat(struct PlayerConnection connection, char message[32]);
void disconnect(struct PlayerConnection *connection, char reason[32]);

#endif /* player_connection_h */
