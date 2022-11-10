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
    const char *hostname;
    int port;
    struct QuarkPlugin *plugins;
    
    char motd[32];
    int max_build_height;
    
    float tps;
    
    int player_count;
    const int player_count_maximum;
    struct PlayerConnection *players;
    
    Entity *entities;
    LivingEntity *living_entities;
    
    _Bool is_online_mode;
    _Bool is_hardcore;
};

struct QuarkServer *server_create(void);
void server_destroy(void);

void server_start(void);
void server_stop(void);

void server_tick(void);

void server_broadcast_message(char message[50]);

struct Entity server_parse_entity(enum EntityType type, int uuid);
struct Damageable server_parse_damageable(int uuid, double health, double health_maximum);
struct LivingEntity server_parse_living_entity(int uuid, double heath, double health_maximum);
struct Player server_parse_player(int uuid);

void server_try_connecting_player(int uuid);
struct PlayerConnection *server_parse_player_connection(int uuid);

void server_player_joined(struct PlayerConnection *player);
void server_player_quit(struct PlayerConnection *player);

void server_get_response(int port);

#endif /* quark_server_h */
