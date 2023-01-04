//
//  main.c
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utilities.h"
#include "server/gluon_server.h"
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
    const unsigned int test_size = sizeof(struct Gamemode);
    printf("main.test; test_size=%d\n", test_size);
    /*
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("current directory=\"%s\"\n", cwd);
        const char *suffix = "/gluon/resources/data/biomes/minecraft";
        strcat(cwd, suffix);
        file_manager_iterate_files(cwd);
    }*/
}

void *test_file_manager(char *characters, unsigned long length) {
    /*printf("characters address=%p, length=%lu\n", characters, length);
    struct JSONObject target_json;
    json_object_parse_fixed_size(characters, length, 1, &target_json);
    json_object_calculate_string_length(&target_json);
    char to_string[length];
    
    unsigned long took_ns = current_time_nano();
    json_object_to_string(&target_json, to_string);
    took_ns = current_time_nano() - took_ns;
    const long double took_ms = (long double) took_ns / (long double) 1000000;
    const long double bytes_per_nano = (long double) length / (long double) took_ns;
    printf("bytes=%lu, length=%lu, took %luns (%Lfms, gigabytes per second=%Lf)\n", length, strlen(to_string), took_ns, took_ms, bytes_per_nano);
    
    printf("%s\n", to_string);*/
    return NULL;
}

int main(int argc, const char * argv[]) {
    //test();
    init();
    //server_get_response(25565);
    
    //file_manager_read_file("/Users/randomhashtags/Downloads/test_json.json", test_file_manager);
    
    return 1;
}
