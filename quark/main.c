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
    server_create();
    server_start();
    server_destroy();
    printf("server thread has shutdown, all processing has finished.\n");
}

int main(int argc, const char * argv[]) {
    init();
    //server_get_response(25565);
}
