//
//  json_object.c
//  quark
//
//  Created by Evan Anderson on 11/22/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_object.h"
#include "../utilities.h"

unsigned long json_calculate_string_length(struct JSONObject *json) {
    unsigned long bytes = 2;
    
    _Bool should_add_comma = 0;
    const unsigned short keys_string_count = json->keys_string_count;
    if (keys_string_count > 0) {
        const unsigned char *keys_string_lengths = json->keys_string_lengths;
        const unsigned char *values_string_lengths = json->values_strings_length;
        for (unsigned short i = 0; i < keys_string_count; i++) {
            bytes += keys_string_lengths[i] + values_string_lengths[i];
        }
        bytes += keys_string_count-1 + (keys_string_count * 5);
        should_add_comma = 1;
    }
    
    const unsigned short keys_json_count = json->keys_json_count;
    if (keys_json_count > 0) {
        const unsigned char *keys_json_lengths = json->keys_json_lengths;
        const struct JSONObject *values_jsons = json->values_jsons;
        for (unsigned short i = 0; i < keys_json_count; i++) {
            bytes += keys_json_lengths[i] + values_jsons[i].to_string_length;
        }
        bytes += should_add_comma + keys_json_count-1 + (keys_json_count * 3);
        should_add_comma = 1;
    }
    
    json->to_string_length = bytes;
    return bytes;
}
unsigned long json_to_string(struct JSONObject *json, char *string) {
    string[0] = '{';
    unsigned long byte = 1;
    
    unsigned short keys_string_count = json->keys_string_count;
    if (keys_string_count > 0) {
        char **keys_string = json->keys_string;
        unsigned char *keys_string_lengths = json->keys_string_lengths;
        char **values_strings = json->values_strings;
        unsigned char *values_string_lengths = json->values_strings_length;
        for (unsigned short i = 0; i < keys_string_count; i++) {
            string[byte] = '"';
            
            byte += 1;
            char *target_key = keys_string[i];
            const unsigned char target_key_length = keys_string_lengths[i];
            for (unsigned char key_iteration = 0; key_iteration < target_key_length; key_iteration++) {
                string[byte + key_iteration] = target_key[key_iteration];
            }
            byte += target_key_length + 3;
            string[byte-3] = '"';
            string[byte-2] = ':';
            string[byte-1] = '"';
            
            char *target_value = values_strings[i];
            const unsigned char target_value_length = values_string_lengths[i];
            for (unsigned char value_iteration = 0; value_iteration < target_value_length; value_iteration++) {
                string[byte + value_iteration] = target_value[value_iteration];
            }
            byte += target_value_length + 2;
            string[byte-2] = '"';
            string[byte-1] = ',';
        }
    }
    
    unsigned short keys_json_count = json->keys_json_count;
    if (keys_json_count > 0) {
        char **keys_json = json->keys_json;
        unsigned char *keys_json_lengths = json->keys_json_lengths;
        struct JSONObject *values_jsons = json->values_jsons;
        for (unsigned short i = 0; i < keys_json_count; i++) {
            string[byte] = '"';
            
            byte += 1;
            char *target_key = keys_json[i];
            const unsigned char target_key_length = keys_json_lengths[i];
            for (unsigned char key_iteration = 0; key_iteration < target_key_length; key_iteration++) {
                string[byte + key_iteration] = target_key[key_iteration];
            }
            byte += target_key_length + 2;
            string[byte-2] = '"';
            string[byte-1] = ':';
            struct JSONObject target_json = values_jsons[i];
            char target_json_string[target_json.to_string_length];
            unsigned long target_json_bytes = json_to_string(&target_json, target_json_string);
            for (unsigned long json_iteration = 0; json_iteration < target_json_bytes; json_iteration++) {
                string[byte + json_iteration] = target_json_string[json_iteration];
            }
            byte += target_json_bytes + 1;
            string[byte-1] = ',';
        }
    }
    
    string[byte-1] = '}';
    string[byte] = '\0';
    return byte;
}
