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
    unsigned char keys_string_count;
    char **keys_string;
    unsigned char *keys_string_lengths;
    char **values_strings;
    unsigned char *values_strings_length;
    
    unsigned char keys_float_count;
    char **keys_float;
    unsigned char *keys_float_lengths;
    float *values_floats;
    
    unsigned char keys_json_count;
    char **keys_json;
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

void json_parse_from_string(char *string, struct LegacyJSONObject *json);

void json_get_value(const char *key, const enum JSONValueType type, void *value);

void json_append_string_fixes(void);

void legacy_json_append_string_fixed(struct LegacyJSONObject *json, char *key, const unsigned long long key_length, char *value, const unsigned long long value_length);
void legacy_json_append_json_fixed(struct LegacyJSONObject *json, char *key, const unsigned long long key_length, struct LegacyJSONObject *target_json);

unsigned long legacy_json_to_string(struct LegacyJSONObject json, char *string);
void json_to_string_append_float(float value, char *string, unsigned long long index);
void json_to_string_append_string(char *value, unsigned long long value_length, char *string, unsigned long long index);

#endif /* json_object_h */
