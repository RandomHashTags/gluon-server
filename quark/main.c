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
#include "utilities.h"

// TODO: switch tick rate to be managed per world instead of only the server

void init(void) {
    server_create();
    if (SERVER) {
        server_start();
        server_destroy();
    }
    printf("server thread has shutdown, all processing has finished.\n");
}

void test(void) {
    const unsigned int size = sizeof(struct Material) + sizeof(struct MaterialConfiguration) + sizeof(struct MaterialItemConfiguration) + sizeof(struct MaterialBlockConfiguration) + sizeof(struct MaterialSmeltingConfiguration);
    printf("main.test; size=%d\n", size);
    
    const long test_long = 999999999999999999;
    printf("main.test; long=%ld\n", test_long);
    printf("main.test; float=%f\n", (float) test_long);
    printf("main.test; double=%f\n", (double) test_long);
}

int main(int argc, const char * argv[]) {
    //test();
    init();
    //server_get_response(25565);
}
