//
//  quark_server.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include "quark_server.h"
#include "../utilities.h"
#include "../managers/event_manager.h"

unsigned char TICKS_PER_SECOND;
float TICKS_PER_SECOND_MULTIPLIER;
unsigned char BLOCK_BREAK_DELAY_TICKS;
const float GRAVITY = 9.8;
float GRAVITY_PER_TICK;
struct QuarkServer *SERVER;

#define QUARK_SERVER_THREAD_COUNT 3
#define QUARK_SERVER_THREAD_ID_HANDLE_PLAYER_CONNECTIONS 0
#define QUARK_SERVER_THREAD_ID_SERVER_LOOP 1
#define QUARK_SERVER_THREAD_ID_UPDATE_PLAYER_PINGS 2
pthread_t *THREADS;

int64_t current_time_milliseconds(void) {
    struct timeval now;
    gettimeofday(&now, NULL);
    int64_t seconds = (int64_t) now.tv_sec * 1000;
    int64_t milliseconds = now.tv_usec / 1000;
    return seconds + milliseconds;
}
void server_create(void) {
    struct QuarkServer *server = malloc(sizeof(struct QuarkServer));
    if (!server) {
        printf("failed to allocate memory for a QuarkServer\n");
        return;
    }
    server->is_sleeping = 1;
    
    unsigned short plugins_count = 0;
    struct QuarkPlugin *plugins = malloc(plugins_count * sizeof(struct QuarkPlugin));
    if (!plugins) {
        free(server);
        printf("failed to allocate memory for a QuarkServer plugins\n");
        return;
    }
    printf("server registered %d QuarkPlugins\n", plugins_count);
    
    struct World *worlds = malloc(4 * sizeof(struct World));
    if (!worlds) {
        free(server);
        free(plugins);
        printf("failed to allocate memory for a QuarkServer worlds\n");
        return;
    }
    
    unsigned short entity_types_count = 40;
    struct EntityType *entity_types = malloc(entity_types_count * sizeof(struct EntityType));
    if (!entity_types) {
        free(server);
        free(plugins);
        free(worlds);
        printf("failed to allocate memory for a QuarkServer entity_tyes\n");
        return;
    }
    printf("server registered %d EntityTypes\n", entity_types_count);
    
    unsigned short inventory_types_count = 30;
    struct InventoryType *inventory_types = malloc(inventory_types_count * sizeof(struct InventoryType));
    if (!inventory_types) {
        free(server);
        free(plugins);
        free(worlds);
        free(entity_types);
        printf("failed to allocate memory for %d QuarkServer InventoryTypes\n", inventory_types_count);
        return;
    }
    printf("server registered %d InventoryTypes\n", inventory_types_count);
    
    unsigned short materials_count = 1700;
    struct Material *materials = malloc(materials_count * sizeof(struct Material));
    if (!materials) {
        free(server);
        free(plugins);
        free(worlds);
        free(entity_types);
        free(inventory_types);
        printf("failed to allocate memory for %d QuarkServer Materials\n", materials_count);
        return;
    }
    printf("server registered %d Materials\n", materials_count);
    
    unsigned short enchantment_types_count = 30;
    struct EnchantmentType *enchantment_types = malloc(enchantment_types_count * sizeof(struct EnchantmentType));
    if (!enchantment_types) {
        free(server);
        free(plugins);
        free(worlds);
        free(entity_types);
        free(inventory_types);
        free(materials);
        printf("failed to allocate memory for %d QuarkServer enchantment_types\n", enchantment_types_count);
        return;
    }
    
    unsigned short biomes_count = 63;
    struct Biome *biomes = malloc(biomes_count * sizeof(struct Biome));
    if (!biomes) {
        free(server);
        free(plugins);
        free(worlds);
        free(entity_types);
        free(inventory_types);
        free(materials);
        free(enchantment_types);
        printf("failed to allocate memory for %d QuarkServer biomes\n", biomes_count);
        return;
    }
    
    const char *default_world_name = malloc_string("world");
    if (!default_world_name) {
        free(server);
        free(plugins);
        free(worlds);
        free(entity_types);
        free(inventory_types);
        free(materials);
        free(enchantment_types);
        free(biomes);
        printf("failed to allocate memory for a QuarkServer default_world_name\n");
        return;
    }
    
    server->entity_types_count = entity_types_count;
    struct EntityType *entity_type_player = entity_type_create("minecraft.player", 20, 20);
    const _Bool is_affected_by_gravity = 1;
    memcpy((_Bool *) &entity_type_player->is_affected_by_gravity, &is_affected_by_gravity, sizeof(_Bool));
    memcpy((_Bool *) &entity_type_player->receives_fall_damage, &is_affected_by_gravity, sizeof(_Bool));
    memcpy(&entity_types[0], entity_type_player, sizeof(struct EntityType));
    server->entity_types = entity_types;
    
    server->inventory_types_count = inventory_types_count;
    server->inventory_types = inventory_types;
    
    server->materials_count = materials_count;
    server->materials = materials;
    
    server->enchantment_types_count = enchantment_types_count;
    server->enchantment_types = enchantment_types;
    
    server->biomes_count = biomes_count;
    server->biomes = biomes;
    
    server->worlds = worlds;
    server->default_world = default_world_name;
    server->world_count = 0;
    
    const unsigned int port = 25565;
    memcpy((unsigned int *) &server->port, &port, sizeof(port));
    
    const int64_t started = current_time_milliseconds();
    memcpy((int64_t *) &server->started, &started, sizeof(started));
    
    const unsigned int players_maximum = 2;
    memcpy((unsigned int *) &server->player_count_maximum, &players_maximum, sizeof(unsigned int));
    SERVER = server;
    
    struct World *world = server_world_create(0, default_world_name, (struct Difficulty *) &DIFFICULTY_MINECRAFT_NORMAL);
    if (!world) {
        free(server);
        free(plugins);
        free(worlds);
        free(entity_types);
        free(inventory_types);
        free(materials);
        free(enchantment_types);
        free(biomes);
        free((char *) default_world_name);
        free(SERVER);
        return;
    }
    printf("created server with address %p, created at %lld\n", server, started);
    server_change_tick_rate(20);
}
void server_deallocate(void) {
    const unsigned short world_count = SERVER->world_count;
    struct World *worlds = SERVER->worlds;
    for (unsigned short i = 0; i < world_count; i++) {
        struct World *world = &worlds[i];
        world_destroy(world);
    }
    free(worlds);
    
    const unsigned short plugin_count = SERVER->plugins_count;
    struct QuarkPlugin *plugins = SERVER->plugins;
    for (unsigned short i = 0; i < plugin_count; i++) {
        struct QuarkPlugin *plugin = &plugins[i];
        plugin_disable(plugin);
        plugin_destroy(plugin);
    }
    free(plugins);
    
    const unsigned short inventory_types_count = SERVER->inventory_types_count;
    struct InventoryType *inventory_types = SERVER->inventory_types;
    for (unsigned short i = 0; i < inventory_types_count; i++) {
        struct InventoryType *type = &inventory_types[i];
        inventory_type_destroy(type);
    }
    free(inventory_types);
    
    const unsigned short materials_count = SERVER->materials_count;
    struct Material *materials = SERVER->materials;
    for (unsigned short i = 0; i < materials_count; i++) {
        struct Material *material = &materials[i];
        material_destroy(material);
    }
    free(materials);
    
    const unsigned short enchantment_types_count = SERVER->enchantment_types_count;
    struct EnchantmentType *enchantment_types = SERVER->enchantment_types;
    for (unsigned short i = 0; i < enchantment_types_count; i++) {
        struct EnchantmentType *type = &enchantment_types[i];
        enchantment_type_destroy(type);
    }
    free(enchantment_types);
    
    const unsigned short biomes_count = SERVER->biomes_count;
    struct Biome *biomes = SERVER->biomes;
    for (unsigned short i = 0; i < biomes_count; i++) {
        struct Biome *biome = &biomes[i];
        biome_destroy(biome);
    }
    free(biomes);
    
    const unsigned short entity_types_count = SERVER->entity_types_count;
    struct EntityType *entity_types = SERVER->entity_types;
    for (unsigned short i = 0; i < entity_types_count; i++) {
        struct EntityType *entity_type = &entity_types[i];
        entity_type_destroy(entity_type);
    }
    free(entity_types);
    
    free((char *) SERVER->hostname);
    free(SERVER->motd);
    free((char *) SERVER->default_world);
    free(SERVER->players_whitelisted);
    free(SERVER->banned_ips);
    free(SERVER->banned_players);
}

void acceptClient(const int sockID, const struct sockaddr_in servAddr, const char *msg, const short msgSize, const short maximum) {
    const int client = accept(sockID, NULL, NULL);
    //send(client, msg, msgSize, 0);
    printf("Received connection\n");
    
    const unsigned int player_count = SERVER->player_count;
    server_try_connecting_player(player_count);
    //close(client);
}
void server_destroy(void) {
    server_deallocate();
    free(SERVER);
}

void server_load_biomes(void) {
    const _Bool reallocate = !SERVER;
}

void *begin_connecting_players(void *threadID) {
    const int sockID = socket(AF_INET, SOCK_STREAM, 0);
    const struct sockaddr_in servAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER->port),
        .sin_addr.s_addr = INADDR_ANY
    };
    
    const char *msg = "yeah, guess who! (RandomHashTags baby)";
    const int msgSize = sizeof(msg);
    
    bind(sockID, (struct sockaddr *) &servAddr, sizeof(servAddr));
    listen(sockID, 1);
    
    const short maximum = SERVER->player_count_maximum;
    printf("Waiting for players to connect on port %d...\n", SERVER->port);
    _Bool alive = 1;
    while (alive) {
        acceptClient(sockID, servAddr, msg, msgSize, maximum);
    }
    close(sockID);
    printf("server will stop accepting clients...\n");
    pthread_exit(threadID);
}
void *begin_ticking_server(void *threadID) {
    double interval = 1000 / (double) TICKS_PER_SECOND;
    printf("starting to tick server %d times every second (once every %f ms)...\n", TICKS_PER_SECOND, interval);
    interval = (double) TICKS_PER_SECOND / 1000;
    while (SERVER != NULL) {
        server_tick();
        sleep(1);
        //sleep(interval);
    }
    printf("shut down server ticking...\n");
    pthread_exit(threadID);
}
void *begin_updating_player_pings(void *threadID) {
    const unsigned short interval = 10;
    printf("starting to update player pings every %d seconds...\n", interval);
    while (SERVER) {
        server_update_player_ping_rates();
        sleep(interval);
    }
    printf("shut down updating player ping updates...\n");
    pthread_exit(threadID);
}
void server_start() {
    pthread_t *threads = malloc(QUARK_SERVER_THREAD_COUNT * sizeof(pthread_t));
    if (!threads) {
        printf("failed to allocate memory for the %d threads\n", QUARK_SERVER_THREAD_COUNT);
        return;
    }
    THREADS = threads;
    pthread_create(&THREADS[QUARK_SERVER_THREAD_ID_HANDLE_PLAYER_CONNECTIONS], NULL, begin_connecting_players, (void *) QUARK_SERVER_THREAD_ID_HANDLE_PLAYER_CONNECTIONS);
    pthread_join(THREADS[QUARK_SERVER_THREAD_ID_HANDLE_PLAYER_CONNECTIONS], NULL);
}
void server_stop(void) {
    printf("stopping server...\n");
    server_deallocate();
    pthread_kill(THREADS[QUARK_SERVER_THREAD_ID_HANDLE_PLAYER_CONNECTIONS], QUARK_SERVER_THREAD_ID_HANDLE_PLAYER_CONNECTIONS);
    pthread_kill(THREADS[QUARK_SERVER_THREAD_ID_SERVER_LOOP], QUARK_SERVER_THREAD_ID_SERVER_LOOP);
    pthread_kill(THREADS[QUARK_SERVER_THREAD_ID_UPDATE_PLAYER_PINGS], QUARK_SERVER_THREAD_ID_UPDATE_PLAYER_PINGS);
    server_destroy();
}
void server_set_sleeping(_Bool value) {
    const _Bool previous_value = SERVER->is_sleeping;
    SERVER->is_sleeping = value;
    printf("server_set_sleeping, value=%d\n", value);
    if (value != previous_value) {
        if (!value) {
            pthread_create(&THREADS[QUARK_SERVER_THREAD_ID_SERVER_LOOP], NULL, begin_ticking_server, (void *) QUARK_SERVER_THREAD_ID_SERVER_LOOP);
            pthread_create(&THREADS[QUARK_SERVER_THREAD_ID_UPDATE_PLAYER_PINGS], NULL, begin_updating_player_pings, (void *) QUARK_SERVER_THREAD_ID_UPDATE_PLAYER_PINGS);
        } else {
            server_stop();
        }
    }
}

void server_tick(void) {
    printf("\nserver at address %p will be ticked...\n", SERVER);
    
    const unsigned short world_count = SERVER->world_count;
    struct World *worlds = SERVER->worlds;
    for (unsigned short i = 0; i < world_count; i++) {
        struct World *world = &worlds[i];
        world_tick(world);
    }
    
    printf("server has been ticked\n");
}


void server_change_tick_rate(const unsigned char ticks_per_second) {
    const float previous_ticks_per_second_multiplier = TICKS_PER_SECOND_MULTIPLIER == 0 ? 1 : TICKS_PER_SECOND_MULTIPLIER;
    TICKS_PER_SECOND = ticks_per_second;
    TICKS_PER_SECOND_MULTIPLIER = (float) ticks_per_second / 20;
    BLOCK_BREAK_DELAY_TICKS = ticks_per_second / 3;
    GRAVITY_PER_TICK = GRAVITY / (float) ticks_per_second;
    
    const double interval = 1000 / (float) ticks_per_second;
    printf("changing server tickrate to %d ticks per second (1 every %f ms, %f multiplier)...\n", TICKS_PER_SECOND, interval, TICKS_PER_SECOND_MULTIPLIER);
    
    const unsigned short entity_types_count = SERVER->entity_types_count;
    struct EntityType *entity_types = SERVER->entity_types;
    for (unsigned short i = 0; i < entity_types_count; i++) {
        struct EntityType *type = &entity_types[i];
        type->no_damage_ticks_maximum /= previous_ticks_per_second_multiplier;
        type->no_damage_ticks_maximum *= TICKS_PER_SECOND_MULTIPLIER;
        
        type->fire_ticks_maximum /= previous_ticks_per_second_multiplier;
        type->fire_ticks_maximum *= TICKS_PER_SECOND_MULTIPLIER;
        
        type->freeze_ticks_maximum /= previous_ticks_per_second_multiplier;
        type->freeze_ticks_maximum *= TICKS_PER_SECOND_MULTIPLIER;
    }
    
    const unsigned short world_count = SERVER->world_count;
    struct World *worlds = SERVER->worlds;
    for (unsigned short i = 0; i < world_count; i++) {
        struct World *world = &worlds[i];
        world_change_tick_rate(world, ticks_per_second);
    }
    printf("server successfully updated tick rate values\n");
}


struct QuarkPlugin *server_get_plugin(const char *name, const char *bundle_id) {
    const unsigned short plugins_count = SERVER->plugins_count;
    struct QuarkPlugin *plugins = SERVER->plugins;
    for (unsigned short i = 0; i < plugins_count; i++) {
        struct QuarkPlugin *plugin = &plugins[i];
        if (strcmp(name, plugin->name) == 0 && strcmp(bundle_id, plugin->bundle_id) == 0) {
            return plugin;
        }
    }
    return NULL;
}
struct EntityType *server_get_entity_type(const char *identifier) {
    const unsigned short entity_types_count = SERVER->entity_types_count;
    struct EntityType *entity_types = SERVER->entity_types;
    for (unsigned short i = 0; i < entity_types_count; i++) {
        struct EntityType *entity_type = &entity_types[i];
        if (strcmp(identifier, entity_type->identifier) == 0) {
            return entity_type;
        }
    }
    return NULL;
}
struct Material *server_get_material(const char *identifier) {
    const unsigned short materials_count = SERVER->materials_count;
    struct Material *materials = SERVER->materials;
    for (unsigned short i = 0; i < materials_count; i++) {
        struct Material *material = &materials[i];
        if (strcmp(identifier, material->identifier) == 0) {
            return material;
        }
    }
    return NULL;
}

struct World *server_get_world(const char *world_name) {
    const unsigned short world_count = SERVER->world_count;
    struct World *worlds = SERVER->worlds;
    for (unsigned short i = 0; i < world_count; i++) {
        struct World *world = &worlds[i];
        if (strcmp(world_name, world->name) == 0) {
            printf("server_get_world; returning world at address %p\n", world);
            return world;
        }
    }
    printf("server failed to get world with name \"%s\"\n", world_name);
    return NULL;
}
struct World *server_world_create(const long seed, const char *world_name, struct Difficulty *difficulty) {
    const short world_count = SERVER->world_count;
    const short world_count_maximum = SERVER->world_count_maximum;
    struct World *worlds = SERVER->worlds;
    if (world_count + 1 > world_count_maximum) {
        const short new_world_count_maximum = world_count_maximum + 4;
        worlds = realloc(worlds, new_world_count_maximum * sizeof(struct World));
        if (!worlds) {
            printf("failed to reallocate memory to expand QuarkServer worlds!\n");
            return NULL;
        }
        SERVER->world_count_maximum = new_world_count_maximum;
    }
    struct World *world = world_create(MINECRAFT_VERSION_1_19_2, seed, world_name, difficulty);
    if (!world) {
        printf("failed to allocate memory for a World\n");
        return NULL;
    }
    printf("server_world_create; created world \"%s\" at address %p\n", world->name, world);
    memcpy(&worlds[world_count], world, sizeof(struct World));
    SERVER->world_count += 1;
    return world;
}
void server_world_destroy(struct World *world) {
    const unsigned short world_count = SERVER->world_count;
    struct World *worlds = SERVER->worlds;
    for (unsigned short i = 0; i < world_count; i++) {
        struct World *targetWorld = &worlds[i];
        if (targetWorld == world) {
            world_destroy(world);
            SERVER->world_count -= 1;
            break;
        }
    }
}

struct Entity *server_parse_entity(const struct EntityType *entity_type, const unsigned int uuid) {
    struct Entity *entity = malloc(sizeof(struct Entity));
    if (!entity) {
        printf("failed to allocate memory for a Entity\n");
        return NULL;
    }
    
    const char *world_name = SERVER->default_world;
    struct World *world = server_get_world(world_name);
    if (!world) {
        const char *default_world_name = SERVER->default_world;
        struct World *default_world = server_get_world(default_world_name);
        if (!default_world) {
            free(entity);
            printf("failed to parse World for Entity's location, and the default server's world\n");
            return NULL;
        }
        world = default_world;
    }
    
    const float location_x = 0, location_y = 10, location_z = 0;
    struct Chunk *chunk = world_get_or_load_chunk(world, (long) location_x / 16, (long) location_z / 16);
    if (!chunk) {
        free(entity);
        return NULL;
    }
    struct Location *location = location_create(world, chunk, location_x, location_y, location_z, 90, 0);
    if (!location) {
        free(entity);
        return NULL;
    }
    entity->type = entity_type;
    memcpy((unsigned int *) &entity->uuid, &uuid, sizeof(uuid));
    entity->display_name = NULL;
    entity->location = location;
    entity->is_affected_by_gravity = entity_type->is_affected_by_gravity;
    
    struct Vector vector = {
        .x = 0,
        .y = 0,
        .z = 0
    };
    entity->velocity = vector;
    entity->fire_ticks = 0;
    entity->fire_ticks_maximum = entity_type->fire_ticks_maximum;
    return entity;
}
struct Damageable *server_parse_damageable(const struct EntityType *entity_type, const unsigned int uuid, const double health, const double health_maximum) {
    struct Entity *entity = server_parse_entity(entity_type, uuid);
    if (!entity) {
        return NULL;
    }
    struct Damageable *damageable = malloc(sizeof(struct Damageable));
    if (!damageable) {
        entity_destroy(entity);
        printf("failed to allocate memory for a Damageable\n");
        return NULL;
    }
    damageable->entity = entity;
    damageable->health = health;
    damageable->health_maximum = health_maximum;
    return damageable;
}
struct LivingEntity *server_parse_living_entity(const struct EntityType *entity_type, const unsigned int uuid, const double health, const double health_maximum) {
    struct Damageable *damageable = server_parse_damageable(entity_type, uuid, health, health_maximum);
    if (!damageable) {
        return NULL;
    }
    struct LivingEntity *entity = malloc(sizeof(struct LivingEntity));
    if (!entity) {
        damageable_destroy(damageable);
        printf("failed to allocate memory for a LivingEntity\n");
        return NULL;
    }
    
    struct PotionEffect *potionEffects = malloc(27 * sizeof(struct PotionEffect));
    if (!potionEffects) {
        damageable_destroy(damageable);
        free(entity);
        printf("failed to allocate memory for a LivingEntity potionEffectsPointer\n");
        return NULL;
    }
    
    entity->damageable = damageable;
    entity->potion_effect_count = 0;
    entity->potion_effects = potionEffects;
    entity->no_damage_ticks = 0;
    entity->no_damage_ticks_maximum = entity_type->no_damage_ticks_maximum;
    return entity;
}
struct Player *server_parse_player(unsigned int uuid) {
    const double health = 20;
    const double health_maximum = 20;
    struct EntityType *entity_type_player = server_get_entity_type("minecraft.player");
    struct LivingEntity *entity = server_parse_living_entity(entity_type_player, uuid, health, health_maximum);
    if (!entity) {
        return NULL;
    }
    struct Player *player = malloc(sizeof(struct Player));
    if (!player) {
        living_entity_destroy(entity);
        printf("failed to allocate memory for a Player\n");
        return NULL;
    }
    
    char *player_name = uuid == 0 ? "RandomHashTags" : uuid == 1 ? "test2" : uuid == 2 ? "test3" : "test4";
    char *namePointer = malloc_string(player_name);
    if (!namePointer) {
        living_entity_destroy(entity);
        free(player);
        printf("failed to allocate memory for a Player namePointer\n");
        return NULL;
    }
    const unsigned int firstPlayed = 50;
    
    player->living_entity = entity;
    player->name = namePointer;
    player->list_name = NULL;
    memcpy((unsigned int *) &player->first_played, &firstPlayed, sizeof(firstPlayed));
    
    player->block_break_delay = 0;
    player->experience = 0;
    player->experience_level = 0;
    player->food_level = 0;
    
    player->gamemode = &GAMEMODE_MINECRAFT_SURVIVAL;
    player->bed_spawn_location = NULL;
    player->advancements = NULL;
    player->inventory = NULL;
    player->inventory_ender_chest = NULL;
    player->permissions = NULL;
    player->spectator_target = NULL;
    return player;
}

void server_try_connecting_player(const unsigned int uuid) {
    const unsigned int player_count = SERVER->player_count;
    const unsigned int maximum = SERVER->player_count_maximum;
    if (player_count + 1 > maximum) {
        printf("player cannot join due to the server being full! (%d maximum players)\n", maximum);
    } else {
        struct PlayerConnection *test = server_parse_player_connection(uuid);
        if (test) {
            server_player_joined(test);
        }
    }
}
struct PlayerConnection *server_parse_player_connection(const unsigned int uuid) {
    struct Player *player = server_parse_player(uuid);
    if (!player) {
        return NULL;
    }
    
    struct PlayerConnection *connection = malloc(sizeof(struct PlayerConnection));
    if (!connection) {
        player_destroy(player);
        printf("failed to allocate memory for a PlayerConnection\n");
        return NULL;
    }
    connection->player = player;
    connection->ping = (unsigned short) rand();
    connection->chat_cooldown = 20;
    printf("parsed player connection \"%s\" with address=%p\n", player->name, player);
    return connection;
}
void server_update_player_ping_rates(void) {
    const int player_count = SERVER->player_count;
    printf("\nupdating %d player pings...\n", player_count);
    
    const unsigned short world_count = SERVER->world_count;
    struct World *worlds = SERVER->worlds;
    for (unsigned short i = 0; i < world_count; i++) {
        struct World *world = &worlds[i];
        const unsigned int player_count = world->player_count;
        struct PlayerConnection *connections = world->players;
        for (int i = 0; i < player_count; i++) {
            struct PlayerConnection *connection = &connections[i];
            connection->ping = (unsigned short) rand();
        }
    }
    printf("finished updating player pings\n");
}

void server_player_joined(struct PlayerConnection *connection) {
    if (SERVER->is_sleeping) {
        server_set_sleeping(0);
    }
    struct Player *player = connection->player;
    const struct World *world = player->living_entity->damageable->entity->location->world;
    world_player_joined(world, connection);
    SERVER->player_count += 1;
    struct PlayerJoinEvent event = {
        .event = {
            .event = {
                .type = EVENT_PLAYER_JOIN
            },
            .player = player
        },
    };
    printf("\"%s\" joined with address %p, on server at address %p, in world at address %p\n", player->name, connection, SERVER, world);
    event_manager_call_event((struct Event *) &event);
}
void server_player_quit(struct PlayerConnection *connection) {
    player_connection_destroy(connection);
    SERVER->player_count -= 1;
    if (SERVER->player_count == 0) {
        server_set_sleeping(1);
    }
}
