//
//  main.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "server/quark_server.h"
#include "managers/file_manager.h"

// TODO: switch tick rate to be managed per world instead of only the server

void init(void) {
    printf("initializing...\n");
    server_create();
    if (SERVER) {
        server_start();
        server_destroy();
    }
    printf("server thread has shutdown, all processing has finished.\n");
}

void test(void) {
    //const unsigned int size = sizeof(struct Material);
    //printf("main.test; size=%d\n", size);
    
    const long test_long = 999999999999999999;
    printf("main.test; long=%ld\n", test_long);
    printf("main.test; float=%f\n", (float) test_long);
    printf("main.test; double=%f\n", (double) test_long);
    
    char *test_char = "RandomHashTags";
    int test_char_size1 = sizeof(test_char), test_char_size2 = sizeof(*test_char);
    printf("main.test; test_char_size1=%d, test_char_size2=%d\n", test_char_size1, test_char_size2);
    
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("current directory=\"%s\"\n", cwd);
        //file_manager_iterate_files("/Users/randomhashtags/GitProjects/quark/quark/resources/data/biomes/minecraft");
    }
}

int main(int argc, const char * argv[]) {
    test();
    //init();
    //server_get_response(25565);
}
