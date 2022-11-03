//
//  main.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

// this project is intended to further my knowledge in C programming. This is a minecraft server alternative to any written in Java.

#include <stdio.h>
#include "quark_managers.h"
#include "quark_server.h"

int main(int argc, const char * argv[]) {
    const enum Material material = BEDROCK;
    
    struct QuarkServer server = {
        .hostname = "localhost",
        .port = 25565
    };
    
    struct Player player = {
        .living_entity = {
            .entity = {
                .type = ET_PLAYER,
                .uuid = "33d83372-cf9e-432a-ad40-3b444782f465"
            },
            .health_maximum = 20,
            .health = 20
        },
        .name = "RandomHashTags"
    };
    server.players[0] = &player;
    
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
    return 0;
}
