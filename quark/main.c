//
//  main.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "managers/event_manager.h"
#include "server/quark_server.h"

void init(void) {
    initServer();
    tryConnectingPlayer(0);
    startServer();
    freeServer();
    printf("server thread has shutdown, all processing has finished.\n");
}

int main(int argc, const char * argv[]) {
    init();
    //getResponse(25565);
}
