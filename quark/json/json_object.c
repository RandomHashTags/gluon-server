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
    
    unsigned char keys_string_count = json->keys_string_count;
    unsigned char *keys_string_lengths = json->keys_string_lengths;
    unsigned char *values_string_lengths = json->values_strings_length;
    for (unsigned char i = 0; i < keys_string_count; i++) {
        bytes += keys_string_lengths[i] + values_string_lengths[i] + 6;
    }
    bytes += keys_string_count-1;
    
    json->to_string_length = bytes;
    return bytes;
}
unsigned long json_to_string(struct JSONObject *json, char *string) {
    string[0] = '{';
    unsigned long byte = 1;
    
    unsigned char keys_string_count = json->keys_string_count;
    char **keys_string = json->keys_string;
    unsigned char *keys_string_lengths = json->keys_string_lengths;
    char **values_strings = json->values_strings;
    unsigned char *values_string_lengths = json->values_strings_length;
    for (unsigned long iteration = 0; iteration < keys_string_count; iteration++) {
        string[byte] = '"';
        
        byte += 1;
        char *target_key = keys_string[iteration];
        const unsigned char target_key_length = keys_string_lengths[iteration];
        for (unsigned char string_iteration = 0; string_iteration < target_key_length; string_iteration++) {
            string[byte + string_iteration] = target_key[string_iteration];
        }
        byte += target_key_length + 3;
        string[byte-3] = '"';
        string[byte-2] = ':';
        string[byte-1] = '"';
        
        char *target_value = values_strings[iteration];
        const unsigned char target_value_length = values_string_lengths[iteration];
        for (unsigned char value_iteration = 0; value_iteration < target_value_length; value_iteration++) {
            string[byte + value_iteration] = target_value[value_iteration];
        }
        byte += target_value_length + 2;
        string[byte-2] = '"';
        string[byte-1] = ',';
    }
    string[byte-1] = '}';
    string[byte] = '\0';
    return byte;
}

unsigned long legacy_json_to_string(struct LegacyJSONObject json, char *string) {
    const unsigned long long keys_count = json.keys_count;
    struct LegacyJSONObjectValue *values = json.values;
    
    const unsigned long long float_size = 3;
    
    string[0] = '{';
    unsigned long key_index = 1;
    for (unsigned long long i = 0; i < keys_count; i++) {
        struct LegacyJSONObjectValue value = values[i];
        string[key_index] = '"';
        key_index += 1;
        
        const char *key = value.key;
        const unsigned long long key_count = value.key_length;
        for (unsigned long long j = 0; j < key_count; j++) {
            string[key_index + j] = key[j];
        }
        key_index += key_count;
        
        string[key_index] = '"';
        string[key_index+1] = ':';
        key_index += 2;
        
        switch (value.type) {
            case JSON_VALUE_TYPE_FLOAT: {
                json_to_string_append_float(value.value_float, string, key_index);
                key_index += float_size;
                break;
            } case JSON_VALUE_TYPE_STRING: {
                char *value_string = value.value_string;
                const unsigned long long value_length = strlen(value_string);
                json_to_string_append_string(value_string, value_length, string, key_index);
                key_index += value_length + 2;
                break;
            } case JSON_VALUE_TYPE_JSON_OBJECT: {
                struct LegacyJSONObject target_json = value.value_json;
                const unsigned long long target_json_string_length = target_json.to_string_length;
                char *target_json_string = alloca(target_json_string_length);
                if (target_json_string) {
                    legacy_json_to_string(target_json, target_json_string);
                    for (unsigned long long j = 0; j < target_json_string_length; j++) {
                        string[key_index + j] = target_json_string[j];
                    }
                    key_index += target_json_string_length;
                } else {
                    printf("failed to allocate %llu bytes for a target_json_string", target_json_string_length);
                    string[key_index] = '{';
                    string[key_index+1] = '}';
                    key_index += 2;
                }
                break;
            } default: {
                string[key_index] = '5';
                key_index += 1;
                break;
            }
        }
        string[key_index] = ',';
        key_index += 1;
    }
    string[key_index-1] = '}';
    string[key_index] = '\0';
    return key_index;
}

void legacy_json_append_string_fixed(struct LegacyJSONObject *json, char *key, const unsigned long long key_length, char *value, const unsigned long long value_length) {
    struct LegacyJSONObjectValue json_value = {
        .key = key,
        .key_length = key_length,
        .type = JSON_VALUE_TYPE_STRING,
        .value_string = value
    };
    json->values[json->keys_count] = json_value;
    json->keys_count += 1;
    json->to_string_length += key_length + value_length + 6;
}
void legacy_json_append_json_fixed(struct LegacyJSONObject *json, char *key, const unsigned long long key_length, struct LegacyJSONObject *target_json) {
    struct LegacyJSONObjectValue json_value = {
        .key = key,
        .key_length = key_length,
        .type = JSON_VALUE_TYPE_JSON_OBJECT,
        .value_json = *target_json
    };
    json->values[json->keys_count] = json_value;
    json->keys_count += 1;
    json->to_string_length += key_length + 4 + target_json->to_string_length + 1;
}

void json_to_string_append_float(float value, char *string, unsigned long long index) {
    const unsigned long float_precision = 3;
    //char buffer[float_precision];
    //memcpy(&buffer, &value, sizeof(float));
    //gcvt(value, 7, buffer);
    
    for (unsigned long i = 0; i < float_precision; i++) {
        string[index + i] = '1';
    }
}
void json_to_string_append_string(char *value, unsigned long long value_length, char *string, unsigned long long index) {
    string[index] = '"';
    index += 1;
    for (unsigned long i = 0; i < value_length; i++) {
        string[index + i] = value[i];
    }
    string[index + value_length] = '"';
}
