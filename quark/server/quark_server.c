//
//  quark_server.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "quark_server.h"
#include "utilities.h"
#include "../managers/event_manager.h"
#include <string.h>

struct QuarkServer *initServer() {
    struct QuarkServer *serverPointer = malloc(sizeof(struct QuarkServer));
    if (serverPointer == NULL) {
        printf("failed to allocate memory for a QuarkServer\n");
        return NULL;
    }
    serverPointer->port = 25565;
        
    int *playerCount = malloc(sizeof(int));
    if (!playerCount) {
        printf("failed to allocate memory for a QuarkServer playerCount\n");
        return NULL;
    }
    *playerCount = 0;
    serverPointer->player_count = playerCount;
    
    const int maximumPlayers = 2;
    
    int *maximumPlayerCount = malloc(sizeof(int));
    if (!maximumPlayerCount) {
        printf("failed to allocate memory for a QuarkServer player_count_maximum\n");
        return NULL;
    }
    *maximumPlayerCount = maximumPlayers;
    serverPointer->player_count_maximum = *maximumPlayerCount;
    
    struct PlayerConnection *players = malloc(maximumPlayers * sizeof(struct PlayerConnection)); // TODO: FIX -> SEMGENTATION FAULT IF NOT MULTIPLIED BY A NUMBER > 1 | only allows 1 player
    if (!players) {
        printf("failed to allocate memory for a QuarkServer players\n");
        return NULL;
    }
    serverPointer->players = players;
    
    SERVER = serverPointer;
    printf("created server with address %p\n", serverPointer);
    return serverPointer;
}
void freeServer(void) {
    free(SERVER);
}

void *connectPlayers(void *threadID) {
    const int sockID = socket(AF_INET, SOCK_STREAM, 0);
    const struct sockaddr_in servAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(25565),
        .sin_addr.s_addr = INADDR_ANY
    };
    
    const char msg[256] = "yeah, guess who! (RandomHashTags baby)";
    const int msgSize = sizeof(msg);
    
    bind(sockID, (struct sockaddr*) &servAddr, sizeof(servAddr));
    
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
        
        const int playerCount = *SERVER->player_count;
        if (playerCount + 1 == maximum) {
            printf("player cannot join due to the server being full! (%d maximum players)\n", maximum);
        } else {
            struct PlayerConnection *test = parsePlayerConnection(5);
            playerJoined(test);
        }
    }
    printf("Stopping server...\n");
    pthread_exit(threadID);
}
void *beginTickingServer(void *threadID) {
    printf("starting to tick server once every second...\n");
    while (SERVER != NULL) {
        tickServer();
        sleep(1);
    }
    printf("shut down server ticking...\n");
    pthread_exit(threadID);
}
void startServer() {
    pthread_t threads[2];
    pthread_create(&threads[0], NULL, connectPlayers, (void *) 0);
    pthread_create(&threads[1], NULL, beginTickingServer, (void *) 1);
    pthread_join(threads[1], NULL);
}
void stopServer(void) {
    freeServer();
}

void tickServer(void) {
    printf("\nserver at address %p will be ticked...\n", SERVER);
    /*Entity *entities = SERVER->entities;
    for (int i = 0; i < 100; i++) {
        Entity *entity = &entities[i];
        if (entity != NULL) {
            tickEntity(entity);
        }
    }
    
    printf("server will begin ticking living entities...\n");
    LivingEntity *livingEntities = (LivingEntity *) SERVER->living_entities;
    for (int i = 0; i < 100; i++) {
        LivingEntity *entity = &livingEntities[i];
        if (entity != NULL) {
            tickLivingEntity(entity);
        }
    }*/
    
    const int playerCount = *SERVER->player_count;
    printf("server will tick %d player(s)...\n", playerCount);
    struct PlayerConnection *players = (struct PlayerConnection *) SERVER->players;
    for (int i = 0; i < playerCount; i++) {
        printf("i=%d, ", i);
        struct PlayerConnection *connection = &players[i];
        printf("ping %d and chat_cooldown %d; ", *connection->ping, *connection->chat_cooldown);
        struct Player *player = connection->player;
        tickPlayer(player);
        damageDamageable(player->living_entity->damageable, 1);
        player->living_entity->no_damage_ticks_maximum -= 1;
        printf("test2\n");
    }
    printf("server has been ticked, playerCount=%d...\n", playerCount);
    tryConnectingPlayer(playerCount);
    printf("test3\n");
}

Entity *parseEntity(enum EntityType type, int uuid) {
    const int memorySize = sizeof(Entity);
    Entity *entity = malloc(memorySize);
    if (!entity) {
        printf("failed to allocate memory for a Entity\n");
        return NULL;
    }
    
    enum EntityType *typePointer = malloc(sizeof(enum EntityType));
    if (!typePointer) {
        printf("failed to allocate memory for a Entity typePointer\n");
        return NULL;
    }
    *typePointer = type;
    
    int *uuidPointer = malloc(sizeof(int));
    if (!uuidPointer) {
        printf("failed to allocate memory for a Entity uuidPointer\n");
        return NULL;
    }
    *uuidPointer = uuid;
    
    entity->type = typePointer;
    entity->uuid = uuidPointer;
    return entity;
}
Damageable *parseDamageable(int uuid, double health, double health_maximum) {
    const int memorySize = sizeof(Damageable);
    Damageable *damageable = malloc(memorySize);
    if (!damageable) {
        printf("failed to allocate memory for a Damageable\n");
        return NULL;
    }
    const size_t doubleSize = sizeof(double);
    double *healthPointer = malloc(doubleSize);
    if (!healthPointer) {
        printf("failed to allocate memory for a Damageable healthPointer\n");
        return NULL;
    }
    *healthPointer = health;
    
    double *healthMaximumPointer = malloc(doubleSize);
    if (!healthMaximumPointer) {
        printf("failed to allocate memory for a Damageable healthMaximumPointer\n");
        return NULL;
    }
    *healthMaximumPointer = health_maximum;
    
    damageable->entity = parseEntity(ENTITY_TYPE_PLAYER, uuid);
    damageable->health = health;
    damageable->health_maximum = health_maximum;
    return damageable;
}
LivingEntity *parseLivingEntity(int uuid, double health, double health_maximum) {
    const int memorySize = sizeof(LivingEntity);
    LivingEntity *entity = malloc(memorySize);
    if (!entity) {
        printf("failed to allocate memory for a LivingEntity\n");
        return NULL;
    }
    entity->no_damage_ticks_maximum = 20;
    entity->damageable = parseDamageable(uuid, health, health_maximum);
    return entity;
}
struct Player *parsePlayer(int uuid) {
    struct Player *player = malloc(sizeof(struct Player));
    if (!player) {
        printf("failed to allocate memory for a Player\n");
        return NULL;
    }
    const int nameSize = 16;
    char *name = malloc(nameSize * sizeof(char));
    if (!name) {
        printf("failed to allocate memory for a Player name\n");
        return NULL;
    }
    name = uuid == 0 ? "RandomHashTags" : uuid == 1 ? "test2" : uuid == 2 ? "test3" : "test4";
    
    player->living_entity = parseLivingEntity(uuid, 20, 20);
    player->name = name;
    //player->first_played = 0;
    const int firstPlayed = 50;
    memcpy((void *) &player->first_played, &firstPlayed, sizeof(int));
    printf("parsed player \"%s\" with address=%p\n", player->name, player);
    return player;
}

void tryConnectingPlayer(int uuid) {
    const int playerCount = *SERVER->player_count;
    const int maximum = SERVER->player_count_maximum;
    if (playerCount + 1 > maximum) {
        printf("player cannot join due to the server being full! (%d maximum players)\n", maximum);
    } else {
        struct PlayerConnection *test = parsePlayerConnection(uuid);
        playerJoined(test);
    }
}
struct PlayerConnection *parsePlayerConnection(int uuid) {
    struct PlayerConnection *connection = malloc(sizeof(struct PlayerConnection));
    if (!connection) {
        printf("failed to allocate memory for a PlayerConnection\n");
        return NULL;
    }
    
    const size_t intSize = sizeof(int);
    int *ping = malloc(intSize);
    if (!ping) {
        printf("failed to allocate memory for a PlayerConnection ping\n");
        return NULL;
    }
    *ping = 4;
    
    int *chat_cooldown = malloc(intSize);
    if (!chat_cooldown) {
        printf("failed to allocate memory for a PlayerConnection chat_cooldown\n");
        return NULL;
    }
    *chat_cooldown = 20;
    
    connection->ping = ping;
    connection->player = parsePlayer(uuid);
    connection->chat_cooldown = chat_cooldown;
    return connection;
}

void playerJoined(struct PlayerConnection *connection) {
    struct Player *player = connection->player;
    const struct PlayerJoinEvent event = {
        .event = {
            .event = {
                .type = EVENT_PLAYER_JOIN
            },
            .player = player
        },
    };
    printf("\"%s\" joined server at address %p with %d ping and chat_cooldown %d\n", player->name, SERVER, *connection->ping, *connection->chat_cooldown);
    callEvent((Event *) &event);
    
    const int playerCount = *SERVER->player_count;
    SERVER->players[playerCount] = *connection;
    *SERVER->player_count += 1;
}
void playerQuit(struct PlayerConnection *connection) {
    int targetPlayerIndex = 0;
    const int playerUUID = *connection->player->living_entity->damageable->entity->uuid;
    const int playerCount = *SERVER->player_count;
    struct PlayerConnection *players = (struct PlayerConnection *) SERVER->players;
    for (int i = 0; i < playerCount; i++) {
        if (*players[i].player->living_entity->damageable->entity->uuid == playerUUID) {
            targetPlayerIndex = i;
            break;
        }
    }
    for (int i = targetPlayerIndex; i < playerCount-1; i++) {
        SERVER->players[i] = players[i+1];
    }
    *SERVER->player_count -= 1;
    freePlayer(connection->player);
    free(connection);
}

void getResponse(int port) {
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
