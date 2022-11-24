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
    const unsigned long keys_count = 90000;
    const unsigned long sizeof_json_value = sizeof(struct LegacyJSONObjectValue);
    const unsigned long json_object_size = keys_count * sizeof_json_value;
    
    printf("preparing to allocate %lu bytes on stack for json values\n", json_object_size);
    struct LegacyJSONObjectValue *values = alloca(json_object_size);
    printf("allocated %lu bytes on stack for json values\n", json_object_size);
    if (!values) {
        printf("failed to allocate memory for %lu LegacyJSONObjectValues\n", keys_count);
        return;
    }
    unsigned long json_string_length = 2 + (keys_count * 9) - 1;
    for (unsigned long i = 0; i < keys_count; i++) {
        const _Bool is_float = i != 0 && i % 6 == 0;
        const _Bool is_string = i != 0 && i % 4 == 0;
        const _Bool is_json = i != 0 && i % 7 == 0;
        char *key = is_string ? "strng" : is_json ? "json1" : is_float ? "float" : "test2";
        enum JSONValueType type = is_float ? JSON_VALUE_TYPE_FLOAT : is_string ? JSON_VALUE_TYPE_STRING : is_json ? JSON_VALUE_TYPE_JSON_OBJECT : JSON_VALUE_TYPE_INTEGER;
        struct LegacyJSONObjectValue value = {
            .key = key,
            .key_length = 5,
            .type = type
        };
        if (is_float) {
            value.value_float = 12345.7890;
            json_string_length += 3;
        } else if (is_string) {
            value.value_string = "bruh";
            json_string_length += 6;
        } else if (is_json) {
            const unsigned long target_json_keys_count = 1;
            struct LegacyJSONObjectValue *target_json_values = alloca(target_json_keys_count * sizeof(struct LegacyJSONObjectValue));
            struct LegacyJSONObjectValue test = {
                .key = "name",
                .key_length = 4,
                .type = JSON_VALUE_TYPE_STRING,
                .value_string = "RandomHashTags"
            };
            target_json_values[0] = test;
            const unsigned long target_json_string_length = 25;
            struct LegacyJSONObject target_json = {
                .keys_count = target_json_keys_count,
                .values = target_json_values,
                .to_string_length = target_json_string_length
            };
            value.value_json = target_json;
            json_string_length += target_json_string_length;
        } else {
            json_string_length += 1;
            //value.value_long = 987654321123456789;
        }
        values[i] = value;
    }
    const unsigned long to_string_length = json_string_length + 1;
    struct LegacyJSONObject json = {
        .keys_count = keys_count,
        .values = values,
        .to_string_length = to_string_length
    };
    
    printf("preparing to allocate %lu bytes on stack for json_string\n", to_string_length);
    char *json_string = alloca(to_string_length);
    printf("allocated %lu bytes on stack for json_string\n", to_string_length);
    if (!json_string) {
        printf("failed to allocate memory on stack for a string with length %lu\n", to_string_length);
        return;
    }
    json_to_string(json, json_string);
    if (!json_string) {
        printf("json_string == NULL\n");
    } else {
        printf("json_string != NULL\n");
        //printf("%s\n", json_string);
    }
    //free(json_string);
    //free(values);
}
void testJSON(void) {
    testJSONLegacy();
}

int main(int argc, const char * argv[]) {
    //test();
    testJSON();
    //init();
    //server_get_response(25565);
    return 1;
}
