//
//  main.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include "managers/quark_managers.h"
#include "server/quark_server.h"

void init(void) {
    const enum Material material = BEDROCK;
    
    struct QuarkServer server = {
        .hostname = "localhost",
        .port = 25565
    };
    
    struct Player player = {
        .living_entity = {
            .entity = {
                .type = ENTITY_TYPE_PLAYER,
                .uuid = "33d83372-cf9e-432a-ad40-3b444782f465"
            },
            .health_maximum = 20,
            .health = 20
        },
        .name = "RandomHashTags"
    };
    struct Player *playerPointer = &player;
    server.players[0] = playerPointer;
    
    const int playersByteSize = sizeof(server.players);
    const int playersIntSize = sizeof(player);
    const int count = playersByteSize / playersIntSize;
    
    //server.playerJoined(&player);
    
    const struct PlayerEvent event = {
        .event = { .name = "PlayerEvent" },
        .player = &player
    };
    callEvent(&event);
    printf("Hello, World!\n%i\n", playersIntSize);
    startServer(server);
}

int main(int argc, const char * argv[]) {
    init();
    //getResponse(25565);
    return 0;
}
