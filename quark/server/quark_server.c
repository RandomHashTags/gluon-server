//
//  quark_server.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "quark_server.h"

void startServer(struct QuarkServer server) {
    const int sockID = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(server.port),
        .sin_addr.s_addr = INADDR_ANY
    };
    
    const char msg[256] = "yeah, guess who! (RandomHashTags baby)";
    const int msgSize = sizeof(msg);
    
    bind(sockID, (struct sockaddr*) &servAddr, sizeof(servAddr));
    
    listen(sockID, 1);
    
    struct PlayerConnection *player = server.players[0];
    _Bool alive = 1;
    
    while (alive) {
        int client = accept(sockID, NULL, NULL);
        send(client, msg, msgSize, 0);
        
        char response[4];
        recv(client, response, sizeof(response), 0);
        
        printf("Received response %s\n", response);
        const float amount = atof(response);
        printf("Received amount %f\n", amount);
        const enum EntityDamageResult result = damageDamageable(player->player, amount);
        if (result == ENTITY_DAMAGE_RESULT_KILLED_VICTIM) {
            alive = 0;
        }
        printf("Remaining player health: %f\n", player->player->living_entity.damageable.health);
    }
    printf("Player died! exiting...\n");
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
