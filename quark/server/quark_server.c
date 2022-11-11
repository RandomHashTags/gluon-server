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

void server_destroy(void) {
    free((char *) SERVER->hostname);
    
    const int plugin_count = SERVER->plugin_count;
    struct QuarkPlugin *plugins = (struct QuarkPlugin *) SERVER->plugins;
    for (int i = 0; i < plugin_count; i++) {
        struct QuarkPlugin *plugin = &plugins[i];
        plugin_disable(plugin);
        plugin_destroy(plugin);
    }
    free(SERVER->plugins);
    
    const int player_count = SERVER->player_count;
    struct PlayerConnection *connections = (struct PlayerConnection *) SERVER->players;
    for (int i = 0; i < player_count; i++) {
        struct PlayerConnection *connection = &connections[i];
        // TODO: kick player
        player_connection_destroy(connection);
    }
    free(SERVER->players);
    
    const int living_entity_count = SERVER->living_entity_count;
    LivingEntity *living_entities = (LivingEntity *) SERVER->living_entities;
    for (int i = 0; i < living_entity_count; i++) {
        LivingEntity *living_entity = &living_entities[i];
        living_entity_destroy(living_entity);
    }
    free(SERVER->living_entities);
    
    const int entity_count = SERVER->entity_count;
    Entity *entities = (Entity *) SERVER->entities;
    for (int i = 0; i < entity_count; i++) {
        Entity *entity = &entities[i];
        entity_destroy(entity);
    }
    free(SERVER->entities);
    
    const int world_count = SERVER->world_count;
    struct World *worlds = (struct World *) SERVER->worlds;
    for (int i = 0; i < world_count; i++) {
        struct World *world = &worlds[i];
        world_destroy(world);
    }
    free(SERVER->worlds);
    
    free(SERVER);
}
struct QuarkServer *server_create() {
    struct QuarkServer *serverPointer = malloc(sizeof(struct QuarkServer));
    if (serverPointer == NULL) {
        printf("failed to allocate memory for a QuarkServer\n");
        return NULL;
    }
    serverPointer->port = 25565;
    
    struct World *worldsPointer = malloc(4 * sizeof(struct World));
    if (!worldsPointer) {
        printf("failed to allocate memory for a QuarkServer worldsPointer");
        return NULL;
    }
    serverPointer->worlds = worldsPointer;
    
    const int players_maximum = 2;
    memcpy((int *) &serverPointer->player_count_maximum, &players_maximum, sizeof(int));
    serverPointer->player_count = 0;
    
    struct PlayerConnection *players = malloc(players_maximum * sizeof(struct PlayerConnection));
    if (!players) {
        printf("failed to allocate memory for a QuarkServer players\n");
        return NULL;
    }
    serverPointer->players = players;
    
    SERVER = serverPointer;
    server_change_tickrate(20);
    printf("created server with address %p\n", serverPointer);
    return serverPointer;
}

void *connectPlayers(void *threadID) {
    const int sockID = socket(AF_INET, SOCK_STREAM, 0);
    const struct sockaddr_in servAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER->port),
        .sin_addr.s_addr = INADDR_ANY
    };
    
    const char msg[256] = "yeah, guess who! (RandomHashTags baby)";
    const int msgSize = sizeof(msg);
    
    bind(sockID, (struct sockaddr *) &servAddr, sizeof(servAddr));
    
    listen(sockID, 1);
    
    const int maximum = SERVER->player_count_maximum;
    printf("Waiting for players to connect...\n");
    _Bool alive = 1;
    while (alive) {
        const int client = accept(sockID, NULL, NULL);
        send(client, msg, msgSize, 0);
        
        char response[4];
        recv(client, response, sizeof(response), 0);
        
        printf("Received response %s\n", response);
        const float amount = atof(response);
        printf("Received amount %f\n", amount);
        
        const int playerCount = SERVER->player_count;
        if (playerCount + 1 == maximum) {
            printf("player cannot join due to the server being full! (%d maximum players)\n", maximum);
        } else {
            struct PlayerConnection *test = server_parse_player_connection(playerCount);
            server_player_joined(test);
        }
    }
    printf("Stopping server...\n");
    pthread_exit(threadID);
}
void *beginTickingServer(void *threadID) {
    const double interval = 1000 / (double) TICKS_PER_SECOND;
    printf("starting to tick server %d times every second (once every %f ms)...\n", TICKS_PER_SECOND, interval);
    while (SERVER != NULL) {
        server_tick();
        sleep(1);
        //const double interval = 1000 / (double) TICKS_PER_SECOND;
        //sleep(interval);
    }
    printf("shut down server ticking...\n");
    pthread_exit(threadID);
}
void server_start() {
    pthread_t threads[2];
    pthread_create(&threads[0], NULL, connectPlayers, (void *) 0);
    pthread_create(&threads[1], NULL, beginTickingServer, (void *) 1);
    pthread_join(threads[1], NULL);
}
void server_stop(void) {
    server_destroy();
}

void server_tick(void) {
    printf("\nserver at address %p will be ticked...\n", SERVER);
    const int entityCount = SERVER->entity_count;
    Entity *entities = SERVER->entities;
    for (int i = 0; i < entityCount; i++) {
        Entity *entity = &entities[i];
        entity_tick(entity);
    }
    
    printf("server will begin ticking living entities...\n");
    const int livingEntityCount = SERVER->living_entity_count;
    LivingEntity *livingEntities = (LivingEntity *) SERVER->living_entities;
    for (int i = 0; i < livingEntityCount; i++) {
        LivingEntity *entity = &livingEntities[i];
        living_entity_tick(entity);
    }
    
    const int playerCount = SERVER->player_count;
    printf("server will tick %d player(s)...\n", playerCount);
    struct PlayerConnection *players = (struct PlayerConnection *) SERVER->players;
    for (int i = 0; i < playerCount; i++) {
        printf("i=%d, ", i);
        struct PlayerConnection *connection = &players[i];
        printf("ping %d and chat_cooldown %d; ", connection->ping, connection->chat_cooldown);
        struct Player *player = connection->player;
        player_tick(player);
        damageable_damage((Damageable *) player, 1);
        player->living_entity->no_damage_ticks_maximum -= 1;
        printf("test2\n");
    }
    printf("server has been ticked, playerCount=%d...\n", playerCount);
    server_try_connecting_player(playerCount);
    printf("test3\n");
}

void server_sync_tickrate_for_entity(Entity *entity, enum EntityType entity_type) {
    entity->fire_ticks *= TICKS_PER_SECOND_MULTIPLIER;
    entity->fire_ticks_maximum = entity_type_get_fire_ticks_maximum(entity_type);
}
void server_sync_tickrate_for_living_entity(LivingEntity *living_entity, enum EntityType entity_type, int no_damage_ticks_maximum) {
    Entity *entity = living_entity->damageable->entity;
    
    living_entity->no_damage_ticks *= TICKS_PER_SECOND_MULTIPLIER;
    living_entity->no_damage_ticks_maximum = no_damage_ticks_maximum;
    
    struct PotionEffect *potionEffects = living_entity->potion_effects;
    const int potionEffectsCount = sizeof(*potionEffects) / sizeof(&potionEffects[0]);
    for (int i = 0; i < potionEffectsCount; i++) {
        potionEffects[i].duration *= TICKS_PER_SECOND_MULTIPLIER;
    }
    
    server_sync_tickrate_for_entity(entity, entity_type);
}
void server_sync_tickrate_for_player(struct Player *player, int no_damage_ticks_maximum) {
    server_sync_tickrate_for_living_entity(player->living_entity, ENTITY_TYPE_PLAYER, no_damage_ticks_maximum);
}
void server_change_tickrate(int ticks_per_second) {
    TICKS_PER_SECOND = ticks_per_second;
    TICKS_PER_SECOND_MULTIPLIER = (double) ticks_per_second / 20;
    
    const double interval = 1000 / (double) ticks_per_second;
    printf("changing server tickrate to %d ticks per second (1 every %f ms, %f multiplier)...\n", TICKS_PER_SECOND, interval, TICKS_PER_SECOND_MULTIPLIER);
    
    const int playerCount = SERVER->player_count;
    struct PlayerConnection *players = (struct PlayerConnection *) SERVER->players;
    printf("updating tickrate values for %d player(s)...\n", playerCount);
    const int maximumPlayerNoDamageTicksMaximum = entity_type_get_damage_ticks_maximum(ENTITY_TYPE_PLAYER);
    for (int i = 0; i < playerCount; i++) {
        struct PlayerConnection *connection = &players[i];
        server_sync_tickrate_for_player(connection->player, maximumPlayerNoDamageTicksMaximum);
    }
    
    const int livingEntityCount = SERVER->living_entity_count;
    printf("updating tickrate values for %d living entities...\n", livingEntityCount);
    LivingEntity *livingEntities = (LivingEntity *) SERVER->living_entities;
    for (int i = 0; i < livingEntityCount; i++) {
        LivingEntity *living_entity = &livingEntities[i];
        const enum EntityType entity_type = living_entity->damageable->entity->type;
        server_sync_tickrate_for_living_entity(living_entity, entity_type, entity_type_get_damage_ticks_maximum(entity_type));
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

Entity *server_parse_entity(enum EntityType entity_type, int uuid) {
    Entity *entity = malloc(sizeof(Entity));
    if (!entity) {
        printf("failed to allocate memory for a Entity\n");
        return NULL;
    }
    memcpy((enum EntityType *) &entity->type, &entity_type, sizeof(enum EntityType));
    memcpy((int *) &entity->uuid, &uuid, sizeof(int));
    return entity;
}
Damageable *server_parse_damageable(enum EntityType entity_type, int uuid, double health, double health_maximum) {
    Entity *entity = server_parse_entity(entity_type, uuid);
    if (!entity) {
        return NULL;
    }
    Damageable *damageable = malloc(sizeof(Damageable));
    if (!damageable) {
        printf("failed to allocate memory for a Damageable\n");
        return NULL;
    }
    damageable->entity = entity;
    damageable->health = health;
    damageable->health_maximum = health_maximum;
    return damageable;
}
LivingEntity *server_parse_living_entity(enum EntityType entity_type, int uuid, double health, double health_maximum) {
    Damageable *damageable = server_parse_damageable(entity_type, uuid, health, health_maximum);
    if (!damageable) {
        return NULL;
    }
    LivingEntity *entity = malloc(sizeof(LivingEntity));
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
    entity->no_damage_ticks_maximum = entity_type_get_damage_ticks_maximum(entity_type);
    entity->potion_effects = potionEffects;
    return entity;
}
struct Player *server_parse_player(int uuid) {
    LivingEntity *entity = server_parse_living_entity(ENTITY_TYPE_PLAYER, uuid, 20, 20);
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
    
    player->living_entity = entity;
    const int firstPlayed = 50;
    memcpy((int *) &player->first_played, &firstPlayed, sizeof(int));
    player->name = namePointer;
    return player;
}

void server_try_connecting_player(int uuid) {
    const int playerCount = SERVER->player_count;
    const int maximum = SERVER->player_count_maximum;
    if (playerCount + 1 > maximum) {
        printf("player cannot join due to the server being full! (%d maximum players)\n", maximum);
    } else {
        struct PlayerConnection *test = server_parse_player_connection(uuid);
        server_player_joined(test);
    }
}
struct PlayerConnection *server_parse_player_connection(int uuid) {
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

void server_player_joined(struct PlayerConnection *connection) {
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
    event_manager_call_event((Event *) &event);
    
    const int playerCount = SERVER->player_count;
    SERVER->players[playerCount] = *connection;
    SERVER->player_count += 1;
}
void server_player_quit(struct PlayerConnection *connection) {
    int targetPlayerIndex = 0;
    const int playerUUID = connection->player->living_entity->damageable->entity->uuid;
    const int playerCount = SERVER->player_count;
    struct PlayerConnection *players = (struct PlayerConnection *) SERVER->players;
    for (int i = 0; i < playerCount; i++) {
        if (players[i].player->living_entity->damageable->entity->uuid == playerUUID) {
            targetPlayerIndex = i;
            break;
        }
    }
    for (int i = targetPlayerIndex; i < playerCount-1; i++) {
        SERVER->players[i] = players[i+1];
    }
    SERVER->player_count -= 1;
    player_connection_destroy(connection);
}

void server_get_response(int port) {
    const int sockID = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = INADDR_ANY
    };
    
    const int connectStatus = connect(sockID, (struct sockaddr*) &servAddr, sizeof(servAddr));
    if (connectStatus == -1) {
        printf("Error...\n");
    } else {
        char strData[256];
        recv(sockID, strData, sizeof(strData), 0);
        
        char amount[4];
        scanf("%s", amount);
        send(sockID, amount, sizeof(amount), 0);
        
        printf("Message: %s\n", strData);
    }
}
