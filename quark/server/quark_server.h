//
//  quark_server.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef quark_server_h
#define quark_server_h

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "../network/player_connection.h"

struct QuarkServer {
    const char hostname[10];
    const int port;
    
    char motd[32];
    int max_build_height;
    
    float tps;
    struct PlayerConnection *players[2];
    
    const _Bool is_online_mode;
    const _Bool is_hardcore;
};

void startServer(struct QuarkServer server);
void stopServer(void);
void broadcastMessage(char message[50]);

void playerJoined(struct PlayerConnection *player);
void playerQuit(struct PlayerConnection *player);

void getResponse(int port);

#endif /* quark_server_h */
