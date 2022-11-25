//
//  json_object.c
//  quark
//
//  Created by Evan Anderson on 11/25/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_object.h"

void json_object_destroy(struct JSONObject *json) {
    const unsigned long keys_count = json->keys_count;
    char **keys = json->keys;
    for (unsigned long i = 0; i < keys_count; i++) {
        free(keys[i]);
    }
    free(keys);
    const unsigned long strings_count = json->strings_count;
    struct JSONObjectValueString *strings = json->strings;
    for (unsigned long i = 0; i < strings_count; i++) {
        struct JSONObjectValueString string = strings[i];
        free(string.key);
        free(string.value);
    }
    free(strings);
}
void json_object_calculate_string_length(struct JSONObject *json) {
    const unsigned long strings_count = json->strings_count;
        
    unsigned long bytes = 1;
    
    struct JSONObjectValueString *strings = json->strings;
    for (unsigned long i = 0; i < strings_count; i++) {
        struct JSONObjectValueString string = strings[i];
        bytes += string.to_string_length + 1;
    }
    
    json->to_string_length = bytes;
}

void json_object_to_string(struct JSONObject *json, char *to_string) {
    const unsigned long strings_count = json->strings_count;
    to_string[0] = '{';
    
    unsigned long byte = 1;
    
    struct JSONObjectValueString *strings = json->strings;
    for (unsigned long i = 0; i < strings_count; i++) {
        struct JSONObjectValueString string = strings[i];
        const unsigned long string_length = string.to_string_length;
        char string_to_string[string_length];
        json_object_value_string_to_string(&string, string_to_string);
        
        for (unsigned long j = 0; j < string_length; j++) {
            const unsigned long target_byte = byte + j;
            to_string[target_byte] = string_to_string[j];
        }
        byte += string_length + 1;
        to_string[byte-1] = ',';
    }
    to_string[byte-1] = '}';
    to_string[byte] = '\0';
}

void json_object_value_string_calculate_string_length(struct JSONObjectValueString *value_string) {
    const unsigned char key_length = value_string->key_length, value_length = value_string->value_length, bytes = key_length + value_length + 5;
    value_string->to_string_length = bytes;
}
void json_object_value_string_to_string(struct JSONObjectValueString *value_string, char *to_string) {
    const unsigned char key_length = value_string->key_length, value_length = value_string->value_length;
    
    to_string[0] = '"';
    unsigned short byte = 1;
    const char *key = value_string->key;
    for (unsigned char i = 0; i < key_length; i++) {
        to_string[byte + i] = key[i];
    }
    byte += key_length + 3;
    to_string[byte-3] = '"';
    to_string[byte-2] = ':';
    to_string[byte-1] = '"';
    
    const char *value = value_string->value;
    for (unsigned char i = 0; i < value_length; i++) {
        to_string[byte + i] = value[i];
    }
    byte += value_length+1;
    to_string[byte-1] = '"';
    to_string[byte] = '\0';
}

void json_object_parse_fixed_size(const char *string, const unsigned long string_length, const unsigned long key_count, const unsigned long string_count, struct JSONObject *parsed_json) {
    unsigned long keys_count = 0;
    char **keys = malloc(key_count * sizeof(char *));
    
    unsigned long strings_count = 0;
    struct JSONObjectValueString *strings = malloc(string_count * sizeof(struct JSONObjectValueString));
    
    const size_t key_value_size = 32 * sizeof(char);
    
    for (unsigned long byte = 1; byte < string_length; byte++) {
        char target_character = string[byte];
        switch (target_character) {
            case '{': {
                break;
            } case '[': {
                break;
            } case '"': {
                byte += 1;
                char *parsed_string = malloc(key_value_size);
                json_parse_string(string, string_length, byte, parsed_string);
                const unsigned char key_length = strlen(parsed_string);
                keys[keys_count] = parsed_string;
                byte += key_length;
                break;
            } case ':': {
                byte += 1;
                target_character = string[byte];
                switch (target_character) {
                    case '1': {
                        break;
                    } case 'n': {
                        break;
                    } case 't': {
                        break;
                    } case 'f': {
                        break;
                    } case '"': {
                        byte += 1;
                        char *parsed_value = malloc(key_value_size);
                        json_parse_string(string, string_length, byte, parsed_value);
                        const unsigned char parsed_string_length = strlen(parsed_value);
                        
                        char *key = keys[keys_count];
                        const unsigned char key_length = strlen(key);
                        
                        struct JSONObjectValueString value_string = {
                            .key = key,
                            .key_length = key_length,
                            .value = parsed_value,
                            .value_length = parsed_string_length,
                        };
                        json_object_value_string_calculate_string_length(&value_string);
                        
                        strings[strings_count] = value_string;
                        strings_count += 1;
                        keys_count += 1;
                        byte += parsed_string_length;
                        break;
                    } default: {
                        break;
                    }
                }
                break;
            } default: {
                break;
            }
        }
    }
    parsed_json->keys = keys;
    parsed_json->strings_count = strings_count;
    parsed_json->strings = strings;
    parsed_json->to_string_length = string_length;
}

void json_parse_string(const char *string, const unsigned long string_length, unsigned long byte, char *parsed_string) {
    unsigned long index = 0;
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
