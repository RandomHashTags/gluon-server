//
//  quark_server.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef quark_server_h
#define quark_server_h

#include <sys/time.h>
#include "../util/difficulty.h"
#include "../network/player_connection.h"

struct QuarkServer {
    const char *hostname;
    const unsigned int port;
    const int64_t started;
    struct Difficulty difficulty;
    _Bool is_sleeping;
    
    unsigned short plugin_count;
    struct QuarkPlugin *plugins;
    
    struct Material *materials;
    
    char motd[32];
    unsigned short max_build_height;
    
    float tps;
    
    const char *default_world;
    unsigned short world_count;
    unsigned short world_count_maximum;
    struct World *worlds;
    
    unsigned int player_count;
    const unsigned int player_count_maximum;
    struct PlayerConnection *players;
    char *players_whitelisted;
    
    unsigned short banned_ips_count;
    char *banned_ips;
    unsigned short banned_player_count;
    char *banned_players;
    
    int entity_count;
    struct Entity *entities;
    
    int living_entity_count;
    struct LivingEntity *living_entities;
    
    _Bool is_online_mode;
    _Bool is_pvp_enabled;
    _Bool is_whitelist_enabled;
};

struct QuarkServer *server_create(void);
_Bool server_allocate(void);
void server_deallocate(void);
void server_destroy(void);

void server_start(void);
void server_stop(void);
void server_set_sleeping(_Bool value);

void server_tick(void);
void server_change_tickrate(unsigned short ticks_per_second);

void server_world_create(struct World *world);
void server_world_destroy(struct World *world);

void server_broadcast_message(char *message);

struct Entity *server_parse_entity(struct EntityType entity_type, unsigned int uuid);
struct Damageable *server_parse_damageable(struct EntityType entity_type, unsigned int uuid, double health, double health_maximum);
struct LivingEntity *server_parse_living_entity(struct EntityType entity_type, unsigned int uuid, double heath, double health_maximum);
struct Player *server_parse_player(unsigned int uuid);

void server_try_connecting_player(unsigned int uuid);
struct PlayerConnection *server_parse_player_connection(unsigned int uuid);
void server_update_player_ping_rates(void);

void server_player_joined(struct PlayerConnection *player);
void server_player_quit(struct PlayerConnection *player);

#endif /* quark_server_h */
