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
#include "util/block/block.h"

void init(void) {
    server_create();
    server_start();
    server_destroy();
    printf("server thread has shutdown, all processing has finished.\n");
}

void test(void) {
    const unsigned int size = sizeof(struct Player);
    printf("main.test; size=%d\n", size);
}

int main(int argc, const char * argv[]) {
    test();
    //init();
    //server_get_response(25565);
}
