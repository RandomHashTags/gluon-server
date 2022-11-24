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

void json_parse_from_fixed_string(char *string, unsigned long string_length, struct JSONObject *json) {
    enum JSONObjectParsingIdentity parsing_identity = JSON_PARSING_IDENTITY_NULL;
    
    char key[256];
    unsigned long key_length = 0;
    
    unsigned short keys_string_count = 0;
    
    for (unsigned long byte = 1; byte < string_length-1; byte++) {
        char target_character = string[byte];
        switch (target_character) {
            case '{': {
                printf("parsing json...\n");
                for (unsigned long index = byte+1; index < string_length; index++) {
                    target_character = string[index];
                    switch (target_character) {
                        case '}': {
                            char *target_json_string = NULL;
                            struct JSONObject *inner_json = NULL;
                            json_parse_from_fixed_string(target_json_string, index-byte, inner_json);
                            goto parsed_json;
                            break;
                        } default: {
                            break;
                        }
                    }
                }
                parsed_json:
                printf("parsed json\n");
                break;
            } case '"': {
                switch (parsing_identity) {
                    case JSON_PARSING_IDENTITY_NULL: {
                        char parsed_string[256];
                        byte += 1;
                        json_parse_string(string, string_length, byte, parsed_string);
                        keys_string_count += 1;
                        byte += strlen(parsed_string)+1;
                        break;
                    } default: {
                        break;
                    }
                }
                break;
            } case ':': {
                parsing_identity = JSON_PARSING_IDENTITY_VALUE;
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
                    } case '"': {
                        char parsed_string[256];
                        byte += 1;
                        json_parse_string(string, string_length, byte, parsed_string);
                        byte += strlen(parsed_string)+1;
                        parsing_identity = JSON_PARSING_IDENTITY_NULL;
                        break;
                    } default: {
                        break;
                    }
                }
                break;
            } case ',': {
                parsing_identity = JSON_PARSING_IDENTITY_NULL;
                break;
            } default: {
                key[key_length] = target_character;
                key_length += 1;
                printf("default, character=%c, parsing_identity=%d\n", target_character, parsing_identity);
                break;
            }
        }
    }
    printf("json_parse_from_fixed_string; keys_string_count=%d\n", keys_string_count);
    struct JSONObject target_json = {
        .keys_string_count = keys_string_count,
        
        .to_string_length = string_length
    };
    json = &target_json;
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
    printf("parsed string \"%s\" with index %d\n", parsed_string, index);
}
