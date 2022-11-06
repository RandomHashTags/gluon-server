//
//  main.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include "managers/event_manager.h"
#include "server/quark_server.h"

struct QuarkServer *SERVER;

void init(void) {
    struct QuarkServer server = {
        .hostname = "localhost",
        .port = 25565,
    };
    
    
    struct Player player = {
        .living_entity = {
            .damageable = {
                .entity = {
                    .type = ENTITY_TYPE_PLAYER,
                    .uuid = 0
                },
                .health_maximum = 20,
                .health = 20
            }
        },
        .name = "RandomHashTags"
    };
    struct PlayerConnection connection = {
        .player = &player
    };
    
    
    int maximumAllowedPlayers = 1;
    const int playersByteSize = sizeof(maximumAllowedPlayers);
    const int playersIntSize = sizeof(player);
    const int count = playersByteSize / playersIntSize;
    printf("Hello, World!\n%i\n", playersIntSize);
    
    SERVER = &server;
    playerJoined(connection);
    startServer();
    printf("server thread has shutdown, all processing has finished.\n");
}

int main(int argc, const char * argv[]) {
    init();
    //getResponse(25565);
}
