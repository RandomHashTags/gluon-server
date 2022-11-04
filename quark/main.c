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
    struct QuarkServer server = {
        .hostname = "localhost",
        .port = 25565
    };
    
    struct Player player = {
        .living_entity = {
            .damageable = {
                .entity = {
                    .type = ENTITY_TYPE_PLAYER,
                    .uuid = 1
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
    server.players[0] = &connection;
    
    const int playersByteSize = sizeof(server.players);
    const int playersIntSize = sizeof(player);
    const int count = playersByteSize / playersIntSize;
    
    //server.playerJoined(&player);
    
    struct PlayerEvent event = {
        .event = { .type = EVENT_PLAYER_JOIN },
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
