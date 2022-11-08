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

struct QuarkServer {
    char hostname[10];
    int port;
    struct QuarkPlugin *plugins[50];
    
    char motd[32];
    int max_build_height;
    
    float tps;
    
    Entity *entities[100];
    LivingEntity *living_entities[100];
    
    _Bool is_online_mode;
    _Bool is_hardcore;
    
    int *player_count;
    struct PlayerConnection *players;
};

struct QuarkServer *initServer(void);
void freeServer(void);

void startServer(void);
void stopServer(void);

void tickServer(void);

void broadcastMessage(char message[50]);

struct Entity *parseEntity(enum EntityType type, int uuid);
struct Damageable *parseDamageable(int uuid, double health, double health_maximum);
struct LivingEntity *parseLivingEntity(int uuid, double heath, double health_maximum);
struct Player *parsePlayer(int uuid);

struct PlayerConnection *parsePlayerConnection(int uuid);

void playerJoined(struct PlayerConnection *player);
void playerQuit(struct PlayerConnection *player);

void getResponse(int port);

#endif /* quark_server_h */
