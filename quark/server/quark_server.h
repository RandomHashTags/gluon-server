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
#include "../util/location/world.h"
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
    
    char *motd;
    unsigned short max_build_height;
    
    float tps;
    
    const char *default_world;
    unsigned short world_count;
    unsigned short world_count_maximum;
    struct World *worlds;
    
    unsigned int player_count;
    const unsigned int player_count_maximum;
    char *players_whitelisted;
    
    unsigned short banned_ips_count;
    char *banned_ips;
    unsigned short banned_player_count;
    char *banned_players;
    
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
void server_change_tick_rate(const unsigned short ticks_per_second);

void server_world_create(struct World *world);
void server_world_destroy(struct World *world);

void server_broadcast_message(char *message);

struct Entity *server_parse_entity(const struct EntityType *entity_type, const unsigned int uuid);
struct Damageable *server_parse_damageable(const struct EntityType *entity_type, const unsigned int uuid, const double health, const double health_maximum);
struct LivingEntity *server_parse_living_entity(const struct EntityType *entity_type, const unsigned int uuid, const double heath, const double health_maximum);
struct Player *server_parse_player(const unsigned int uuid);

void server_try_connecting_player(const unsigned int uuid);
struct PlayerConnection *server_parse_player_connection(const unsigned int uuid);
void server_update_player_ping_rates(void);

void server_player_joined(struct PlayerConnection *player);
void server_player_quit(struct PlayerConnection *player);

#endif /* quark_server_h */
