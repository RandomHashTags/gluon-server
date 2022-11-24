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
    const unsigned long long keys_count = 120000;
    struct LegacyJSONObjectValue values[keys_count];
    unsigned long json_string_length = 2 + (keys_count * 9) - 1;
    for (unsigned long i = 0; i < keys_count; i++) {
        const _Bool is_float = 0;//i != 0 && i % 6 == 0;
        const _Bool is_string = 1;//i != 0 && i % 4 == 0;
        const _Bool is_json = 0;//i != 0 && i % 7 == 0;
        char *key = is_float ? "float" : is_string ? "strng" : is_json ? "json1" : "intgr";
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
            const unsigned long long target_json_keys_count = 1;
            struct LegacyJSONObjectValue target_json_values[target_json_keys_count];
            struct LegacyJSONObjectValue test = {
                .key = "name",
                .key_length = 4,
                .type = JSON_VALUE_TYPE_STRING,
                .value_string = "RandomHashTags"
            };
            target_json_values[0] = test;
            const unsigned long long target_json_string_length = 25;
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
    unsigned long long to_string_length = json_string_length + 1;
    struct LegacyJSONObject json = {
        .keys_count = keys_count,
        .values = values,
        .to_string_length = to_string_length
    };
    //legacy_json_append_string_fixed(&json, "appended_string", 15, "yessir", 6);
    
    struct LegacyJSONObjectValue legacy_values[1];
    legacy_values[0] = values[0];
    struct LegacyJSONObject target_json = {
        .keys_count = 1,
        .values = legacy_values,
        .to_string_length = 11
    };
    //legacy_json_append_json_fixed(&json, "appended_json", 13, &target_json);
    
    to_string_length = json.to_string_length;
    printf("allocating %llu bytes on stack for json_string\n", to_string_length);
    char json_string[to_string_length];
    const unsigned long now = current_time_nano();
    const unsigned long bytes = legacy_json_to_string(json, json_string);
    const unsigned long took_ns = current_time_nano() - now;
    const long double took_ms = (long double) took_ns / (long double) 1000000;
    const long double bytes_per_nano = (long double) bytes / (long double) took_ns;
    printf("bytes=%lu, took %luns (%Lfms, gigabytes per second=%Lf)\n", bytes, took_ns, took_ms, bytes_per_nano);
    //printf("json_string != NULL\n");
    //printf("%s\n", json_string);
    //free(json_string);
    //free(values);
}

void testJSONNew1(void) {
    const unsigned char keys_strings_count = 255;
    //const unsigned char keys_floats_count = 10;
    //const unsigned char keys_jsons_count = 10;
    
    char *keys_string[keys_strings_count];
    unsigned char keys_string_lengths[keys_strings_count];
    
    char *values_strings[keys_strings_count];
    unsigned char values_strings_length[keys_strings_count];
    
    for (unsigned char i = 0; i < keys_strings_count; i++) {
        keys_string[i] = "test_string";
        keys_string_lengths[i] = 11;
        values_strings[i] = "string_value";
        values_strings_length[i] = 12;
    }
    
    struct JSONObject json = {
        .keys_string_count = keys_strings_count,
        .keys_string = keys_string,
        .keys_string_lengths = keys_string_lengths,
        .values_strings = values_strings,
        .values_strings_length = values_strings_length
    };
    json_calculate_string_length(&json);
    
    const unsigned long to_string_length = json.to_string_length;
    printf("allocating %lu bytes on stack for json_string\n", to_string_length);
    char json_string[to_string_length];
    
    const unsigned long now = current_time_nano();
    const unsigned long bytes = json_to_string(&json, json_string);
    const unsigned long took_ns = current_time_nano() - now;
    const long double took_ms = (long double) took_ns / (long double) 1000000;
    const long double bytes_per_nano = (long double) bytes / (long double) took_ns;
    printf("bytes=%lu, took %luns (%Lfms, gigabytes per second=%Lf)\n", bytes, took_ns, took_ms, bytes_per_nano);
    printf("%s\n", json_string);
    //free(json_string);
    //free(values);
}
void testJSON(void) {
    testJSONNew1();
    //testJSONLegacy();
}

int main(int argc, const char * argv[]) {
    //test();
    testJSON();
    //init();
    //server_get_response(25565);
    return 1;
}
