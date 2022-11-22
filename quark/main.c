//
//  main.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "utilities.h"
#include "server/quark_server.h"
#include "managers/file_manager.h"
#include "json/json_object.h"

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
        const char *suffix = "/quark/resources/data/biomes/minecraft";
        strcat(cwd, suffix);
        file_manager_iterate_files(cwd);
    }*/
}
void testJSON(void) {
    const long long now = current_time_nano();
    const unsigned short keys_count = 1000;
    struct JSONObjectValue *values = alloca(keys_count * sizeof(struct JSONObjectValue));
    for (unsigned short i = 0; i < keys_count; i++) {
        char *key = alloca(6 * sizeof(char));
        key = "test2\0";
        const _Bool is_float = i != 0 && i % 6 == 0;
        enum JSONValueType type = is_float ? JSON_VALUE_TYPE_FLOAT : JSON_VALUE_TYPE_INTEGER;
        struct JSONObjectValue value = {
            .key = key,
            .type = type
        };
        if (is_float) {
            value.value_float = 12345.7890;
        } else {
            value.value_long = 987654321123456789;
        }
        values[i] = value;
    }
    struct JSONObject json = {
        .keys_count = keys_count,
        .keys_character_count = 6 * keys_count,
        .values = values
    };
    char *json_string = alloca(sizeof(char *));
    json_to_string(json, json_string);
    const long long took = current_time_nano() - now;
    printf("json_to_string=%s - took %lldns\n", json_string, took);
}

int main(int argc, const char * argv[]) {
    //test();
    testJSON();
    //init();
    //server_get_response(25565);
    return 0;
}
