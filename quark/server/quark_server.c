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
#include "utilities.h"
#include "../managers/event_manager.h"

unsigned short TICKS_PER_SECOND;
float TICKS_PER_SECOND_MULTIPLIER;
unsigned short BLOCK_BREAK_DELAY_TICKS;
struct QuarkServer *SERVER;

#define QUARK_SERVER_THREAD_COUNT 3
#define QUARK_SERVER_THREAD_ID_HANDLE_PLAYER_CONNECTIONS 0
#define QUARK_SERVER_THREAD_ID_SERVER_LOOP 1
#define QUARK_SERVER_THREAD_ID_UPDATE_PLAYER_PINGS 2
pthread_t *THREADS;

void server_destroy(void) {
    server_deallocate();
    free(SERVER);
}
int64_t current_time_milliseconds(void) {
    struct timeval now;
    gettimeofday(&now, NULL);
    int64_t seconds = (int64_t) now.tv_sec * 1000;
    int64_t microseconds = now.tv_usec / 1000;
    return seconds;
}
struct QuarkServer *server_create() {
    struct QuarkServer *serverPointer = malloc(sizeof(struct QuarkServer));
    if (serverPointer == NULL) {
        printf("failed to allocate memory for a QuarkServer\n");
        return NULL;
    }
    serverPointer->is_sleeping = 1;
    
    const unsigned int port = 25565;
    memcpy((unsigned int *) &serverPointer->port, &port, sizeof(port));
    
    const int64_t started = current_time_milliseconds();
    memcpy((int64_t *) &serverPointer->started, &started, sizeof(started));
    
    const unsigned int players_maximum = 2;
    memcpy((unsigned int *) &serverPointer->player_count_maximum, &players_maximum, sizeof(unsigned int));
    struct PlayerConnection *players = malloc(players_maximum * sizeof(struct PlayerConnection));
    if (!players) {
        printf("failed to allocate memory for a QuarkServer playersPointer\n");
        return 0;
    }
    serverPointer->players = players;
    SERVER = serverPointer;
    server_change_tickrate(20);
    printf("created server with address %p, created at %lld\n", serverPointer, started);
    return serverPointer;
}
_Bool server_allocate(void) {
    struct World *worldsPointer = malloc(4 * sizeof(struct World));
    if (!worldsPointer) {
        printf("failed to allocate memory for a QuarkServer worldsPointer\n");
        return 0;
    }
    SERVER->worlds = worldsPointer;
    return 1;
}
void server_deallocate(void) {
    free((char *) SERVER->hostname);
    
    const int plugin_count = SERVER->plugin_count;
    struct QuarkPlugin *plugins = SERVER->plugins;
    for (int i = 0; i < plugin_count; i++) {
        struct QuarkPlugin *plugin = &plugins[i];
        plugin_disable(plugin);
        plugin_destroy(plugin);
    }
    free(SERVER->plugins);
    
    const int player_count = SERVER->player_count;
    struct PlayerConnection *connections = SERVER->players;
    for (int i = 0; i < player_count; i++) {
        struct PlayerConnection *connection = &connections[i];
        // TODO: kick player
        player_connection_destroy(connection);
    }
    free(SERVER->players_whitelisted);
    free(SERVER->banned_ips);
    free(SERVER->banned_players);
    
    const int living_entity_count = SERVER->living_entity_count;
    struct LivingEntity *living_entities = SERVER->living_entities;
    for (int i = 0; i < living_entity_count; i++) {
        struct LivingEntity *living_entity = &living_entities[i];
        living_entity_destroy(living_entity);
    }
    free(SERVER->living_entities);
    
    const int entity_count = SERVER->entity_count;
    struct Entity *entities = SERVER->entities;
    for (int i = 0; i < entity_count; i++) {
        struct Entity *entity = &entities[i];
        entity_destroy(entity);
    }
    free(SERVER->entities);
    
    const int world_count = SERVER->world_count;
    struct World *worlds = SERVER->worlds;
    for (int i = 0; i < world_count; i++) {
        struct World *world = &worlds[i];
        world_destroy(world);
    }
    free(SERVER->worlds);
    free((char *) SERVER->default_world);
}

void acceptClient(const int sockID, const struct sockaddr_in servAddr, const char *msg, const short msgSize, const short maximum) {
    const int client = accept(sockID, NULL, NULL);
    //send(client, msg, msgSize, 0);
    printf("Received connection\n");
    
    const unsigned int player_count = SERVER->player_count;
    if (player_count + 1 == maximum) {
        printf("player cannot join due to the server being full! (%d maximum players allowed, %d connected)\n", maximum, player_count);
    } else {
        struct PlayerConnection *test = server_parse_player_connection(player_count);
        if (test) {
            server_player_joined(test);
        }
    }
    //close(client);
}
void *connectPlayers(void *threadID) {
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
    printf("Waiting for players to connect...\n");
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
    while (SERVER != NULL) {
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
    pthread_create(&THREADS[QUARK_SERVER_THREAD_ID_HANDLE_PLAYER_CONNECTIONS], NULL, connectPlayers, (void *) QUARK_SERVER_THREAD_ID_HANDLE_PLAYER_CONNECTIONS);
    pthread_join(THREADS[QUARK_SERVER_THREAD_ID_HANDLE_PLAYER_CONNECTIONS], NULL);
}
void server_stop(void) {
    server_destroy();
}
void server_set_sleeping(_Bool value) {
    const _Bool previous_value = SERVER->is_sleeping;
    SERVER->is_sleeping = value;
    printf("server_set_sleeping, value=%d\n", value);
    if (value != previous_value) {
        if (!value) {
            const _Bool allocated = server_allocate();
            if (allocated) {
                pthread_create(&THREADS[QUARK_SERVER_THREAD_ID_SERVER_LOOP], NULL, begin_ticking_server, (void *) QUARK_SERVER_THREAD_ID_SERVER_LOOP);
                pthread_create(&THREADS[QUARK_SERVER_THREAD_ID_UPDATE_PLAYER_PINGS], NULL, begin_updating_player_pings, (void *) QUARK_SERVER_THREAD_ID_UPDATE_PLAYER_PINGS);
            } else {
                printf("failed to allocate memory to run server\n");
            }
        } else {
            server_deallocate();
            pthread_kill(THREADS[QUARK_SERVER_THREAD_ID_SERVER_LOOP], QUARK_SERVER_THREAD_ID_SERVER_LOOP);
            pthread_kill(THREADS[QUARK_SERVER_THREAD_ID_UPDATE_PLAYER_PINGS], QUARK_SERVER_THREAD_ID_UPDATE_PLAYER_PINGS);
        }
    }
}

void server_tick(void) {
    printf("\nserver at address %p will be ticked...\n", SERVER);
    
    const int entityCount = SERVER->entity_count;
    printf("server will tick %d entities...\n", entityCount);
    struct Entity *entities = SERVER->entities;
    for (int i = 0; i < entityCount; i++) {
        struct Entity *entity = &entities[i];
        entity_tick(entity);
    }
    
    const int livingEntityCount = SERVER->living_entity_count;
    printf("server will tick %d living entities...\n", livingEntityCount);
    struct LivingEntity *livingEntities = SERVER->living_entities;
    for (int i = 0; i < livingEntityCount; i++) {
        struct LivingEntity *entity = &livingEntities[i];
        living_entity_tick(entity);
    }
    
    const int player_count = SERVER->player_count;
    printf("server will tick %d player(s)...\n", player_count);
    struct PlayerConnection *players = SERVER->players;
    for (int i = 0; i < player_count; i++) {
        printf("ticking player #%d, ", i);
        struct PlayerConnection *connection = &players[i];
        printf("with ping %d\n", connection->ping);
        struct Player *player = connection->player;
        player_tick(player);
        damageable_damage(player->living_entity->damageable, 1);
        printf("test2\n");
    }
    printf("server has been ticked\n");
}

void server_sync_tickrate_for_entity(struct Entity *entity, struct EntityType entity_type) {
    entity->fire_ticks *= TICKS_PER_SECOND_MULTIPLIER;
    entity->fire_ticks_maximum = entity_type_get_fire_ticks_maximum(entity_type);
}
void server_sync_tickrate_for_living_entity(struct LivingEntity *living_entity, struct EntityType entity_type, int no_damage_ticks_maximum) {
    struct Entity *entity = living_entity->damageable->entity;
    
    living_entity->no_damage_ticks *= TICKS_PER_SECOND_MULTIPLIER;
    living_entity->no_damage_ticks_maximum = no_damage_ticks_maximum;
    
    struct PotionEffect *potionEffects = living_entity->potion_effects;
    const unsigned short potion_effect_count = living_entity->potion_effect_count;
    for (int i = 0; i < potion_effect_count; i++) {
        potionEffects[i].duration *= TICKS_PER_SECOND_MULTIPLIER;
    }
    
    server_sync_tickrate_for_entity(entity, entity_type);
}
void server_sync_tickrate_for_player(struct Player *player, unsigned int no_damage_ticks_maximum) {
    server_sync_tickrate_for_living_entity(player->living_entity, ENTITY_TYPE_MINECRAFT_PLAYER, no_damage_ticks_maximum);
}
void server_change_tickrate(unsigned short ticks_per_second) {
    TICKS_PER_SECOND = ticks_per_second;
    TICKS_PER_SECOND_MULTIPLIER = (float) ticks_per_second / 20;
    BLOCK_BREAK_DELAY_TICKS = TICKS_PER_SECOND / 3;
    
    const double interval = 1000 / (float) ticks_per_second;
    printf("changing server tickrate to %d ticks per second (1 every %f ms, %f multiplier)...\n", TICKS_PER_SECOND, interval, TICKS_PER_SECOND_MULTIPLIER);
    
    const unsigned int player_count = SERVER->player_count;
    struct PlayerConnection *players = SERVER->players;
    printf("updating tickrate values for %d player(s)...\n", player_count);
    const int maximumPlayerNoDamageTicksMaximum = entity_type_get_no_damage_ticks_maximum(ENTITY_TYPE_MINECRAFT_PLAYER);
    for (int i = 0; i < player_count; i++) {
        struct PlayerConnection *connection = &players[i];
        server_sync_tickrate_for_player(connection->player, maximumPlayerNoDamageTicksMaximum);
    }
    
    const int living_entity_count = SERVER->living_entity_count;
    printf("updating tickrate values for %d living entities...\n", living_entity_count);
    struct LivingEntity *livingEntities = SERVER->living_entities;
    for (int i = 0; i < living_entity_count; i++) {
        struct LivingEntity *living_entity = &livingEntities[i];
        const struct EntityType entity_type = living_entity->damageable->entity->type;
        server_sync_tickrate_for_living_entity(living_entity, entity_type, entity_type_get_no_damage_ticks_maximum(entity_type));
    }
    
    printf("server successfully updated tickrate values\n");
}

void server_world_create(struct World *world) {
    const short world_count = SERVER->world_count;
    const short world_count_maximum = SERVER->world_count_maximum;
    struct World *worlds = SERVER->worlds;
    if (world_count + 1 > world_count_maximum) {
        const short new_world_count_maximum = world_count_maximum + 4;
        SERVER->world_count_maximum = new_world_count_maximum;
        worlds = realloc(worlds, new_world_count_maximum * sizeof(struct World));
        if (!worlds) {
            printf("failed to reallocate memory to expand QuarkServer worldPointer!\n");
            return;
        }
    }
    memmove((struct World *) &worlds[world_count], world, sizeof(struct World));
    SERVER->world_count += 1;
}
void server_world_destroy(struct World *world) {
    const int world_count = SERVER->world_count;
    struct World *worlds = SERVER->worlds;
    for (int i = 0; i < world_count; i++) {
        struct World *targetWorld = &worlds[i];
        if (targetWorld == world) {
            world_destroy(world);
            SERVER->world_count -= 1;
            break;
        }
    }
}

struct Entity *server_parse_entity(struct EntityType entity_type, unsigned int uuid) {
    struct Entity *entity = malloc(sizeof(struct Entity));
    if (!entity) {
        printf("failed to allocate memory for a Entity\n");
        return NULL;
    }
    memcpy((struct EntityType *) &entity->type, &entity_type, sizeof(struct EntityType));
    memcpy((unsigned int *) &entity->uuid, &uuid, sizeof(uuid));
    return entity;
}
struct Damageable *server_parse_damageable(struct EntityType entity_type, unsigned int uuid, double health, double health_maximum) {
    struct Entity *entity = server_parse_entity(entity_type, uuid);
    if (!entity) {
        return NULL;
    }
    struct Damageable *damageable = malloc(sizeof(struct Damageable));
    if (!damageable) {
        printf("failed to allocate memory for a Damageable\n");
        return NULL;
    }
    damageable->entity = entity;
    damageable->health = health;
    damageable->health_maximum = health_maximum;
    return damageable;
}
struct LivingEntity *server_parse_living_entity(struct EntityType entity_type, unsigned int uuid, double health, double health_maximum) {
    struct Damageable *damageable = server_parse_damageable(entity_type, uuid, health, health_maximum);
    if (!damageable) {
        return NULL;
    }
    struct LivingEntity *entity = malloc(sizeof(struct LivingEntity));
    if (!entity) {
        printf("failed to allocate memory for a LivingEntity\n");
        return NULL;
    }
    
    struct PotionEffect *potionEffects = malloc(27 * sizeof(struct PotionEffect));
    if (!potionEffects) {
        printf("failed to allocate memory for a LivingEntity potionEffectsPointer\n");
        return NULL;
    }
    
    entity->damageable = damageable;
    entity->potion_effect_count = 0;
    entity->potion_effects = potionEffects;
    entity->no_damage_ticks = 0;
    entity->no_damage_ticks_maximum = entity_type_get_no_damage_ticks_maximum(entity_type);
    return entity;
}
struct Player *server_parse_player(unsigned int uuid) {
    struct LivingEntity *entity = server_parse_living_entity(ENTITY_TYPE_MINECRAFT_PLAYER, uuid, 20, 20);
    if (!entity) {
        return NULL;
    }
    struct Player *player = malloc(sizeof(struct Player));
    if (!player) {
        printf("failed to allocate memory for a Player\n");
        return NULL;
    }
    
    char *namePointer = malloc(16 * sizeof(char));
    if (!namePointer) {
        printf("failed to allocate memory for a Player namePointer\n");
        return NULL;
    }
    namePointer = uuid == 0 ? "RandomHashTags" : uuid == 1 ? "test2" : uuid == 2 ? "test3" : "test4";
    const unsigned int firstPlayed = 50;
    
    player->living_entity = entity;
    player->name = namePointer;
    memcpy((unsigned int *) &player->first_played, &firstPlayed, sizeof(firstPlayed));
    player->block_break_delay = 0;
    return player;
}

void server_try_connecting_player(unsigned int uuid) {
    const unsigned int player_count = SERVER->player_count;
    const unsigned int maximum = SERVER->player_count_maximum;
    if (player_count + 1 > maximum) {
        printf("player cannot join due to the server being full! (%d maximum players)\n", maximum);
    } else {
        struct PlayerConnection *test = server_parse_player_connection(uuid);
        server_player_joined(test);
    }
}
struct PlayerConnection *server_parse_player_connection(unsigned int uuid) {
    struct Player *player = server_parse_player(uuid);
    if (!player) {
        return NULL;
    }
    
    struct PlayerConnection *connection = malloc(sizeof(struct PlayerConnection));
    if (!connection) {
        printf("failed to allocate memory for a PlayerConnection\n");
        return NULL;
    }
    connection->player = player;
    connection->ping = 4;
    connection->chat_cooldown = 20;
    printf("parsed player \"%s\" with address=%p\n", player->name, player);
    return connection;
}
void server_update_player_ping_rates(void) {
    const int player_count = SERVER->player_count;
    struct PlayerConnection *connections = SERVER->players;
    for (int i = 0; i < player_count; i++) {
        struct PlayerConnection *connection = &connections[i];
        connection->ping = (unsigned short) rand();
    }
}

void server_player_joined(struct PlayerConnection *connection) {
    if (SERVER->is_sleeping) {
        server_set_sleeping(0);
    }
    struct Player *player = connection->player;
    const struct PlayerJoinEvent event = {
        .event = {
            .event = {
                .type = EVENT_PLAYER_JOIN
            },
            .player = player
        },
    };
    printf("\"%s\" joined with address %p server at address %p with %d ping, %d chat_cooldown, and %d no_damage_ticks_maximum\n", player->name, player, SERVER, connection->ping, connection->chat_cooldown, connection->player->living_entity->no_damage_ticks_maximum);
    event_manager_call_event((struct Event *) &event);
    
    const unsigned int playerCount = SERVER->player_count;
    SERVER->players[playerCount] = *connection;
    SERVER->player_count += 1;
}
void server_player_quit(struct PlayerConnection *connection) {
    const unsigned int player_uuid = connection->player->living_entity->damageable->entity->uuid;
    const unsigned int player_count = SERVER->player_count;
    struct PlayerConnection *players = SERVER->players;
    for (int i = 0; i < player_count; i++) {
        if (players[i].player->living_entity->damageable->entity->uuid == player_uuid) {
            for (int j = i; j < player_count-1; j++) {
                SERVER->players[j] = players[j+1];
            }
            break;
        }
    }
    
    player_connection_destroy(connection);
    SERVER->player_count -= 1;
    if (player_count == 1) {
        server_set_sleeping(1);
    }
}
