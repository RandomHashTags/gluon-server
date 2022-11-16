//
//  player_connection.h
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#ifndef player_connection_h
#define player_connection_h

#include "../util/entity/player/player.h"

struct PlayerConnection {
    struct Player *player;
    unsigned short ping;
    unsigned short chat_cooldown;
};

void player_connection_destroy(struct PlayerConnection *connection);

void player_connection_chat(struct PlayerConnection connection, char *message);
void player_connection_disconnect(struct PlayerConnection *connection, char *reason);

#endif /* player_connection_h */
