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

void json_to_string(struct JSONObject json, char *string) {
    const unsigned short keys_count = json.keys_count, last_keys_count = keys_count-1;
    struct JSONObjectValue *values = json.values;
    
    const unsigned short float_size = 3;
    char *target_string = alloca(json.keys_character_count + ((keys_count / 6) * float_size) + (keys_count * 3) + (keys_count-1) + 1);
    
    target_string[0] = '{';
    unsigned short key_index = 1;
    for (unsigned short i = 0; i < keys_count; i++) {
        struct JSONObjectValue value = values[i];
        target_string[key_index] = '"';
        key_index += 1;
        
        const char *key = value.key;
        const unsigned short key_count = strlen(key);
        for (unsigned short j = 0; j < key_count; j++) {
            target_string[key_index + j] = key[j];
        }
        key_index += key_count;
        
        target_string[key_index] = '"';
        target_string[key_index + 1] = ':';
        key_index += 2;
        
        //printf("test %d\n", i);
        switch (value.type) {
            case JSON_VALUE_TYPE_FLOAT:
                json_to_string_append_float(value.value_float, target_string, key_index);
                key_index += float_size;
                break;
            default:
                target_string[key_index] = '5';
                key_index += 1;
                break;
        }
        if (i != last_keys_count) {
            target_string[key_index] = ',';
            key_index += 1;
        }
    }
    target_string[key_index] = '}';
    target_string[key_index+1] = '\0';
    unsigned long test = strlen(target_string);
    printf("test=%lu, key_index=%d\n", test, key_index);
    strcpy(string, target_string);
}
void json_to_string_append_float(float value, char *string, unsigned short index) {
    char buffer[7];
    //gcvt(value, 7, buffer);
    for (unsigned short i = 0; i < 3; i++) {
        string[index + i] = '1';
    }
}
