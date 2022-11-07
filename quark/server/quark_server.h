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
#include <unistd.h>
#include <pthread.h>
#include "../network/player_connection.h"

extern struct QuarkServer *SERVER;

struct QuarkServer {
    const char hostname[10];
    const int port;
    struct QuarkPlugin *plugins[50];
    
    char motd[32];
    int max_build_height;
    
    float tps;
    
    Entity *entities[100];
    LivingEntity *living_entities[100];
    
    const _Bool is_online_mode;
    const _Bool is_hardcore;
    
    int player_count;
    struct PlayerConnection *players[];
};

void startServer(void);
void stopServer(void);

void tickServer(void);

void broadcastMessage(char message[50]);

struct PlayerConnection *parsePlayerConnection(int uuid);
struct Player parsePlayer(int uuid);
void playerJoined(struct PlayerConnection *player);
void playerQuit(struct PlayerConnection *player);

void getResponse(int port);

#endif /* quark_server_h */
