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
    
    unsigned short plugins_count;
    struct QuarkPlugin **plugins;
    
    unsigned short entity_types_count;
    struct EntityType **entity_types;
    
    unsigned short inventory_types_count;
    struct InventoryType **inventory_types;
    
    unsigned short materials_count;
    struct Material **materials;
    
    unsigned short enchantment_types_count;
    struct EnchantmentType **enchantment_types;
    
    unsigned short biomes_count;
    struct Biome **biomes;
    
    char *motd;
    
    float tps;
    
    const char *default_world;
    unsigned short world_count;
    unsigned short world_count_maximum;
    struct World **worlds;
    
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

void server_create(void);
void server_deallocate(void);
void server_destroy(void);

void server_load_biomes(void);

void server_start(void);
void server_stop(void);
void server_set_sleeping(_Bool value);

void server_tick(void);
void server_change_tick_rate(const unsigned char ticks_per_second);

struct QuarkPlugin *server_get_plugin(const char *name, const char *bundle_id);
struct EntityType *server_get_entity_type(const char *identifier);
struct Material *server_get_material(const char *identifier);

struct World *server_get_world(const char *world_name);
struct World *server_world_create(const long seed, const char *world_name, struct Difficulty *difficulty);
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
