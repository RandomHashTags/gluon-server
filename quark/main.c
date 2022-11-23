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

void testJSONLegacy(void) {
    const unsigned long keys_count = 100000;
    const unsigned long sizeof_json_value = sizeof(struct LegacyJSONObjectValue);
    struct LegacyJSONObjectValue *values = alloca(keys_count * sizeof_json_value);
    unsigned long floats_count = 0, strings_count = 0;
    for (unsigned long i = 0; i < keys_count; i++) {
        char *key = "test2";
        const _Bool is_float = i != 0 && i % 12 == 0;
        const _Bool is_string = i != 0 && i % 5 == 0;
        enum JSONValueType type = is_float ? JSON_VALUE_TYPE_FLOAT : is_string ? JSON_VALUE_TYPE_STRING : JSON_VALUE_TYPE_INTEGER;
        struct LegacyJSONObjectValue value = {
            .key = key,
            .type = type
        };
        if (is_float) {
            value.value_float = 12345.7890;
            floats_count += 1;
        } else if (is_string) {
            value.value_string = "bruh";
            strings_count += 4 + 2;
        } else {
            value.value_long = 987654321123456789;
        }
        values[i] = value;
    }
    const unsigned long keys_character_count = 5 * keys_count;
    struct LegacyJSONObject json = {
        .keys_count = keys_count,
        .values = values
    };
    
    const unsigned long float_size = 3;
    const unsigned long to_string_length = keys_character_count + (floats_count * float_size) + (strings_count * sizeof(char)) + (keys_count * 3) + (keys_count-1) + 1;
    json.to_string_length = to_string_length;
    char *json_string = alloca(to_string_length * sizeof(char));
    json_to_string(json, json_string);
    if (!json_string) {
        printf("json_string == NULL\n");
    } else {
        printf("json_string != NULL\n");
    }
}
void testJSON(void) {
    //testJSONLegacy();
    
}

int main(int argc, const char * argv[]) {
    //test();
    testJSON();
    //init();
    //server_get_response(25565);
    return 1;
}
