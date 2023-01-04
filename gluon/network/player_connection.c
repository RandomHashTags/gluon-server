//
//  player_connection.c
//  gluon
//
//  Created by Evan Anderson on 11/4/22.
//

#include <stdlib.h>
#include "player_connection.h"
#include "../server/gluon_server.h"

void player_connection_destroy(struct PlayerConnection *connection) {
    player_destroy(connection->player);
    free(connection);
}

void player_connection_disconnect(struct PlayerConnection *connection, char reason[32]) {
    server_player_quit(connection);
}
