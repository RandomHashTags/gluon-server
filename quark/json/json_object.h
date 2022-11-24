//
//  json_object.h
//  quark
//
//  Created by Evan Anderson on 11/22/22.
//

#ifndef json_object_h
#define json_object_h

#include "json_value_type.h"

struct JSONObject {
    unsigned short keys_string_count;
    char **keys_string;
    unsigned char *keys_string_lengths;
    char **values_strings;
    unsigned char *values_strings_length;
    
    unsigned char keys_float_count;
    char **keys_float;
    unsigned char *keys_float_lengths;
    float *values_floats;
    
    unsigned short keys_json_count;
    char **keys_json;
    unsigned char *keys_json_lengths;
    struct JSONObject *values_jsons;
    
    unsigned long to_string_length;
};

struct LegacyJSONObject {
    unsigned long long keys_count;
    
    struct LegacyJSONObjectValue *values;
    
    unsigned long long to_string_length;
};

struct LegacyJSONObjectValue {
    char *key;
    unsigned long long key_length;
    enum JSONValueType type;
    union {
        char *value_string;
        float value_float;
        double value_double;
        long value_long;
        struct LegacyJSONObject value_json;
    };
};

unsigned long json_calculate_string_length(struct JSONObject *json);
unsigned long json_to_string(struct JSONObject *json, char *string);

void json_parse_from_string(char *string, struct JSONObject *json);

#endif /* json_object_h */
