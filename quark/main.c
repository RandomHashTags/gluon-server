//
//  main.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
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

void *testJSON(void) {
    const unsigned long strings_count = 50000;
    struct JSONObjectValueString strings[strings_count];
    for (unsigned long i = 0; i < strings_count; i++) {
        const _Bool is_bro = i % 3 == 0;
        char *key = is_bro ? "okay, but who actually cares" : "really? do your Japanese learning on Duolingo!!";
        const unsigned short key_length = strlen(key);
        char *value = is_bro ? "brooooooooooooooo" : "RandomHashTags12345678";
        unsigned short value_length = strlen(value);
        struct JSONObjectValueString value_string = {
            .key = key,
            .key_length = key_length,
            .value = value,
            .value_length = value_length
        };
        json_object_value_string_calculate_string_length(&value_string);
        strings[i] = value_string;
    }
    
    struct JSONObject json = {
        .strings_count = strings_count,
        .strings = strings
    };
    json_object_calculate_string_length(&json);
    
    const unsigned long to_string_length = json.to_string_length;
    char to_string[to_string_length];
    
    json_object_to_string(&json, to_string);
    //printf("%s\n", to_string);
    
    struct JSONObject parsed_json;
    struct JSONObject *parsed_json_pointer = &parsed_json;
    json_object_parse_fixed_size(to_string, to_string_length, strings_count, parsed_json_pointer);
    char parsed_json_to_string[to_string_length];
    
    double most_bytes_per_nano = 0;
    for (int i = 0; i < 10; i++) {
        /*clock_t now = clock();
        json_object_to_string(parsed_json_pointer, parsed_json_to_string);
        now = clock() - now;
        double took_s = ((double) now) / CLOCKS_PER_SEC;
        double took_ms = took_s * 1000;
        double took_ns = took_ms * 1000000;
        double bytes_per_nano = (double) to_string_length / took_ns;
        printf("bytes=%lu, length=%lu, took %fns (%fms, gigabytes per second=%f)\n", to_string_length, strlen(parsed_json_to_string), took_ns, took_ms, bytes_per_nano);*/
        
        unsigned long took_ns = current_time_nano();
        json_object_to_string(parsed_json_pointer, parsed_json_to_string);
        took_ns = current_time_nano() - took_ns;
        const long double took_ms = (long double) took_ns / (long double) 1000000;
        const long double bytes_per_nano = (long double) to_string_length / (long double) took_ns;
        printf("bytes=%lu, length=%lu, took %luns (%Lfms, gigabytes per second=%Lf)\n", to_string_length, strlen(parsed_json_to_string), took_ns, took_ms, bytes_per_nano);
        
        if (bytes_per_nano > most_bytes_per_nano) {
            most_bytes_per_nano = bytes_per_nano;
        }
    }
    printf("bytes=%lu, length=%lu, most gigabytes per second=%f\n", to_string_length, strlen(parsed_json_to_string), most_bytes_per_nano);
    
    json_object_destroy(parsed_json_pointer);
    return NULL;
}

void *test_file_manager(char *characters, unsigned long length) {
    printf("characters address=%p, length=%lu\n", characters, length);
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
    
    printf("%s\n", to_string);
    return NULL;
}

int main(int argc, const char * argv[]) {
    //test();
    //testJSON();
    //init();
    //server_get_response(25565);
    
    file_manager_read_file("/Users/randomhashtags/Downloads/test_json.json", test_file_manager);
    
    return 1;
}
