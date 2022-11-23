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

unsigned long legacy_json_to_string(struct LegacyJSONObject json, char *string) {
    const unsigned long keys_count = json.keys_count;
    struct LegacyJSONObjectValue *values = json.values;
    
    const unsigned long float_size = 3;
    
    string[0] = '{';
    unsigned long key_index = 1;
    for (unsigned long i = 0; i < keys_count; i++) {
        struct LegacyJSONObjectValue value = values[i];
        string[key_index] = '"';
        key_index += 1;
        
        const char *key = value.key;
        const unsigned long key_count = 5;
        for (unsigned long j = 0; j < key_count; j++) {
            string[key_index + j] = key[j];
        }
        key_index += key_count;
        
        string[key_index] = '"';
        string[key_index + 1] = ':';
        key_index += 2;
        
        switch (value.type) {
            case JSON_VALUE_TYPE_FLOAT:
                json_to_string_append_float(value.value_float, string, key_index);
                key_index += float_size;
                break;
            case JSON_VALUE_TYPE_STRING:
                json_to_string_append_string(value.value_string, string, key_index);
                key_index += 6;
                break;
            default:
                string[key_index] = '5';
                key_index += 1;
                //break;
        }
        string[key_index] = ',';
        key_index += 1;
    }
    key_index -= 1;
    string[key_index] = '}';
    string[key_index+1] = '\0';
    return key_index;
}

void new_json_to_string(struct LegacyJSONObject json, char *string) {
    
}

void json_to_string(struct LegacyJSONObject json, char *string) {
    const unsigned long now = current_time_nano();
    const unsigned long key_index = legacy_json_to_string(json, string);
    const unsigned long took_ns = current_time_nano() - now;
    const long double took_ms = (double) took_ns / (double) 1000000;
    const long double bytes_per_nano = (double) key_index / (double) took_ns;
    printf("bytes=%lu, took %luns (%Lfms, bytes per nano (gigabytes per second)=%Lf)\n", key_index, took_ns, took_ms, bytes_per_nano);
}
void json_to_string_append_float(float value, char *string, unsigned long index) {
    const unsigned long float_precision = 3;
    //char buffer[float_precision];
    //memcpy(&buffer, &value, sizeof(float));
    //gcvt(value, 7, buffer);
    
    for (unsigned long i = 0; i < float_precision; i++) {
        string[index + i] = '1';
    }
}
void json_to_string_append_string(char *value, char *string, unsigned long index) {
    const unsigned long value_length = strlen(value);
    string[index] = '"';
    index += 1;
    for (unsigned long i = 0; i < value_length; i++) {
        string[index + i] = value[i];
    }
    string[index + value_length] = '"';
}
