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

void testJSON(void) {
    const unsigned short keys_strings_count = 20;
    //const unsigned char keys_floats_count = 10;
    const unsigned short keys_jsons_count = 20;
    
    char *keys_string[keys_strings_count];
    unsigned char keys_string_lengths[keys_strings_count];
    char *values_strings[keys_strings_count];
    unsigned char values_strings_length[keys_strings_count];
    
    char *keys_json[keys_jsons_count];
    unsigned char keys_json_lengths[keys_jsons_count];
    struct JSONObject values_jsons[keys_jsons_count];
    
    for (unsigned short i = 0; i < keys_strings_count; i++) {
        keys_string[i] = "test_string";
        keys_string_lengths[i] = 11;
        values_strings[i] = "string_value";
        values_strings_length[i] = 12;
    }
    
    for (unsigned short i = 0; i < keys_jsons_count; i++) {
        keys_json[i] = "test_json";
        keys_json_lengths[i] = 9;
        
        struct JSONObject target_json = {
            .keys_string_count = 1,
            .keys_string = keys_string,
            .keys_string_lengths = keys_string_lengths,
            .values_strings = values_strings,
            .values_strings_length = values_strings_length
        };
        json_calculate_string_length(&target_json);
        values_jsons[i] = target_json;
    }
    
    struct JSONObject json = {
        .keys_string_count = keys_strings_count,
        .keys_string = keys_string,
        .keys_string_lengths = keys_string_lengths,
        .values_strings = values_strings,
        .values_strings_length = values_strings_length,
        
        .keys_json_count = keys_jsons_count,
        .keys_json = keys_json,
        .keys_json_lengths = keys_json_lengths,
        .values_jsons = values_jsons
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
}

int main(int argc, const char * argv[]) {
    //test();
    testJSON();
    //init();
    //server_get_response(25565);
    return 1;
}
