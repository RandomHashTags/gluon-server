//
//  quark_server.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef quark_server_h
#define quark_server_h

#include <stdio.h>
#include "player.h"

struct QuarkServer {
    const char hostname;
    const int port;
    
    char motd[20];
    int max_build_height;
    
    float tps;
    struct Player *players[50];
    
    const _Bool is_online_mode;
    const _Bool is_hardcore;
    
    void (*stop);
    void (*playerJoined)(struct Player *player);
    void (*playerQuit)(struct Player *player);
    void (*broadcastMessage)(char message[50]);
};

#endif /* quark_server_h */
