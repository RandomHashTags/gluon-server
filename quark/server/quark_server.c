//
//  quark_server.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "quark_server.h"
#include "../managers/event_manager.h"

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
        
        struct Player player = {
            .name = "test"
        };
        struct PlayerConnection connection = {
            .player = &player
        };
        playerJoined(connection);
    }
    printf("Stopping server...\n");
    pthread_exit(threadID);
}
void *beginTickingServer(void *threadID) {
    printf("starting to tick server once every second...\n");
    _Bool alive = 1;
    while (alive) {
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
    printf("exited\n");
    pthread_join(threads[1], NULL);
}
void stopServer(void) {
    free(SERVER);
}

void tickServer(void) {
    printf("server will begin ticking...\n");
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
    
    printf("server will begin ticking players...\n");
    struct PlayerConnection *players = (struct PlayerConnection *) SERVER->players;
    const int playerCount = SERVER->player_count;
    for (int i = 0; i < SERVER->player_count; i++) {
        struct PlayerConnection *connection = &players[i];
        if (connection != NULL) {
            struct Player *player = connection->player;
            tickPlayer(player);
        }
    }
    printf("server has been ticked, playerCount=%d...\n", SERVER->player_count);
    
    const char *name = playerCount == 1 ? "test" : "bro";
    struct Player otherPlayer = {
        .living_entity = {
            .damageable = {
                .entity = {
                    .uuid = playerCount
                }
            }
        },
        .name = *name
    };
    struct PlayerConnection otherConnection = {
        .player = &otherPlayer
    };
    playerJoined(otherConnection);
}


void playerJoined(struct PlayerConnection connection) {
    const struct PlayerJoinEvent event = {
        .event = {
            .event = {
                .type = EVENT_PLAYER_JOIN
            },
            .player = connection.player
        },
    };
    callEvent((Event *) &event);
    
    SERVER->players[SERVER->player_count] = connection;
    SERVER->player_count += 1;
}
void playerQuit(struct PlayerConnection connection) {
    int targetPlayerIndex = 0;
    int playerUUID = connection.player->living_entity.damageable.entity.uuid;
    const int playerCount = SERVER->player_count;
    struct PlayerConnection *players = SERVER->players;
    for (int i = 0; i < playerCount; i++) {
        if (players[i].player->living_entity.damageable.entity.uuid == playerUUID) {
            targetPlayerIndex = i;
            break;
        }
    }
    for (int i = targetPlayerIndex; i < playerCount-1; i++) {
        SERVER->players[i] = players[i+1];
    }
    SERVER->player_count -= 1;
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
