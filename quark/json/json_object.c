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
    
    const unsigned short keys_boolean_count = json->keys_boolean_count;
    if (keys_boolean_count > 0) {
        const unsigned short *keys_boolean_lengths = json->keys_boolean_lengths;
        const _Bool *values_booleans = json->values_booleans;
        for (unsigned short i = 0; i < keys_boolean_count; i++) {
            bytes += keys_boolean_lengths[i] + (values_booleans[i] ? 4 : 5);
        }
        bytes += keys_boolean_count-1 + (keys_boolean_count * 3);
        should_add_comma = 1;
    }
    
    const unsigned short keys_string_count = json->keys_string_count;
    if (keys_string_count > 0) {
        const unsigned short *keys_string_lengths = json->keys_string_lengths;
        const unsigned char *values_string_lengths = json->values_strings_length;
        for (unsigned short i = 0; i < keys_string_count; i++) {
            bytes += keys_string_lengths[i] + values_string_lengths[i];
        }
        bytes += should_add_comma + keys_string_count-1 + (keys_string_count * 5);
        should_add_comma = 1;
    }
    
    const unsigned short keys_json_count = json->keys_json_count;
    if (keys_json_count > 0) {
        const unsigned char *keys_json_lengths = json->keys_json_lengths;
        struct JSONObject **values_jsons = json->values_jsons;
        for (unsigned short i = 0; i < keys_json_count; i++) {
            bytes += keys_json_lengths[i] + values_jsons[i]->to_string_length;
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
    
    unsigned short keys_boolean_count = json->keys_boolean_count;
    if (keys_boolean_count > 0) {
        char **keys = json->keys_boolean;
        unsigned short *keys_boolean_lengths = json->keys_boolean_lengths;
        _Bool *values_booleans = json->values_booleans;
        for (unsigned short i = 0; i < keys_boolean_count; i++) {
            string[byte] = '"';
            byte += 1;
            
            char *target_key = keys[i];
            const unsigned short target_key_length = keys_boolean_lengths[i];
            for (unsigned short key_iteration = 0; key_iteration < target_key_length; key_iteration++) {
                string[byte + key_iteration] = target_key[key_iteration];
            }
            byte += target_key_length + 2;
            string[byte-2] = '"';
            string[byte-1] = ':';
            
            const _Bool value = values_booleans[i];
            if (value) {
                string[byte] = 't';
                string[byte+1] = 'r';
                string[byte+2] = 'u';
                string[byte+3] = 'e';
            } else {
                string[byte] = 'f';
                string[byte+1] = 'a';
                string[byte+2] = 'l';
                string[byte+3] = 's';
                string[byte+4] = 'e';
            }
            byte += value ? 5 : 6;
            string[byte-1] = ',';
        }
    }
    
    unsigned short keys_string_count = json->keys_string_count;
    if (keys_string_count > 0) {
        char **keys = json->keys_string;
        unsigned short *keys_string_lengths = json->keys_string_lengths;
        char **values_strings = json->values_strings;
        unsigned char *values_string_lengths = json->values_strings_length;
        for (unsigned short i = 0; i < keys_string_count; i++) {
            string[byte] = '"';
            byte += 1;
            
            char *target_key = keys[i];
            const unsigned short target_key_length = keys_string_lengths[i];
            for (unsigned short key_iteration = 0; key_iteration < target_key_length; key_iteration++) {
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
        struct JSONObject **values_jsons = json->values_jsons;
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
            struct JSONObject *target_json = values_jsons[i];
            char target_json_string[target_json->to_string_length];
            unsigned long target_json_bytes = json_to_string(target_json, target_json_string);
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

void json_parse_from_fixed_string(char *string, const unsigned long string_length, void *json_function_pointer(struct JSONObject)) {
    char key[256];
    unsigned char key_length = 0;
    
    unsigned short keys_boolean_count = 0;
    unsigned short keys_boolean_lengths[10];
    char *keys_boolean[256];
    _Bool values_booleans[10];
    
    unsigned short keys_string_count = 0;
    unsigned short keys_string_lengths[10];
    char *keys_string[256];
    char *values_strings[256];
    unsigned char values_strings_lengths[10];
    
    for (unsigned long byte = 1; byte < string_length-1; byte++) {
        char target_character = string[byte];
        switch (target_character) {
            case '"': {
                byte += 1;
                json_parse_string(string, string_length, byte, key);
                key_length = strlen(key);
                byte += key_length;
                break;
            } case ':': {
                byte += 1;
                target_character = string[byte];
                switch (target_character) {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9': {
                        break;
                    } case 't': {
                        /*byte += 4;
                        keys_boolean[keys_boolean_count] = key;
                        keys_boolean_lengths[keys_boolean_count] = key_length;
                        values_booleans[keys_boolean_count] = 1;
                        keys_boolean_count += 1;*/
                        break;
                    } case 'f': {
                        /*byte += 5;
                        keys_boolean[keys_boolean_count] = key;
                        keys_boolean_lengths[keys_boolean_count] = key_length;
                        values_booleans[keys_boolean_count] = 0;
                        keys_boolean_count += 1;*/
                        break;
                    } case 'n': {
                        printf("json_parse_from_fixed_string; found null value\n");
                        break;
                    } case '{': {
                        struct JSONObject *parsed_json = NULL;
                        json_parse_json(string, string_length, byte, parsed_json);
                        byte += parsed_json->to_string_length+1;
                        break;
                    }case '[': {
                        break;
                    } case '"': {
                        char parsed_string[256];
                        byte += 1;
                        json_parse_string(string, string_length, byte, parsed_string);
                        const unsigned char value_string_length = strlen(parsed_string);
                        byte += value_string_length+1;
                        
                        printf("key=%s\n", key);
                        keys_string[keys_string_count] = key;
                        keys_string_lengths[keys_string_count] = key_length;
                        values_strings[keys_string_count] = parsed_string;
                        values_strings_lengths[keys_string_count] = value_string_length;
                        keys_string_count += 1;
                        break;
                    } default: {
                        break;
                    }
                }
                break;
            } case ',': {
                break;
            } default: {
                printf("default, character=%c\n", target_character);
                break;
            }
        }
    }
    printf("json_parse_from_fixed_string; string_length=%lu, keys_boolean_count=%d, keys_string_count=%d\n", string_length, keys_boolean_count, keys_string_count);
    struct JSONObject target_json = {
        .keys_boolean_count = keys_boolean_count,
        .keys_boolean = keys_boolean,
        .keys_boolean_lengths = keys_boolean_lengths,
        .values_booleans = values_booleans,
        
        .keys_string_count = keys_string_count,
        .keys_string = keys_string,
        .keys_string_lengths = keys_string_lengths,
        .values_strings = values_strings,
        .values_strings_length = values_strings_lengths,
        
        .to_string_length = string_length
    };
    json_function_pointer(target_json);
}

char *json_get_string(struct JSONObject *json, char *key) {
    char **keys = json->keys_string;
    const unsigned short keys_count = json->keys_string_count;
    char **values = json->values_strings;
    for (unsigned short i = 0; i < keys_count; i++) {
        if (strcmp(key, keys[i]) == 0) {
            return values[i];
        }
    }
    return NULL;
}
struct JSONObject *json_get_json(struct JSONObject *json, char *key) {
    char **keys = json->keys_json;
    const unsigned short keys_count = json->keys_json_count;
    struct JSONObject **values = json->values_jsons;
    for (unsigned short i = 0; i < keys_count; i++) {
        if (strcmp(key, keys[i]) == 0) {
            return values[i];
        }
    }
    return NULL;
}

void *json_parse_json_pointer(struct JSONObject json) {
    char string[json.to_string_length];
    json_to_string(&json, string);
    printf("json_parse_json_pointer string=%s\n", string);
    return NULL;
}
void json_parse_json(char *string, unsigned long string_length, unsigned long byte, struct JSONObject *parsed_json) {
    printf("json_parse_json; string_length=%lu, byte=%lu, string=%s\n", string_length, byte, string);
    byte += 1;
    char target_json_string[256];
    unsigned short index = 0;
    for (unsigned long i = byte; i < string_length; i++) {
        char target_character = string[i];
        printf("json_parse_json; target_character=%c\n", target_character);
        switch (target_character) {
            case '{':
                break;
            case '}': {
                target_json_string[index] = target_character;
                json_parse_from_fixed_string(target_json_string, i-byte, json_parse_json_pointer);
                goto parsed;
                break;
            } default: {
                target_json_string[index] = target_character;
                index += 1;
                break;
            }
        }
    }
parsed:
    return;
}
void json_parse_string(char *string, unsigned long string_length, unsigned long byte, char *parsed_string) {
    unsigned short index = 0;
    for (unsigned long i = byte; i < string_length; i++) {
        char target_character = string[i];
        switch (target_character) {
            case '"': {
                parsed_string[index] = '\0';
                goto parsed;
                break;
            } default: {
                parsed_string[index] = target_character;
                index += 1;
                break;
            }
        }
    }
parsed:
    return;
}
