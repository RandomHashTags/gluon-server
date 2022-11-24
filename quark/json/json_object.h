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
    struct JSONObject **values_jsons;
    
    unsigned long to_string_length;
};

unsigned long json_calculate_string_length(struct JSONObject *json);
unsigned long json_to_string(struct JSONObject *json, char *string);

void json_parse_from_fixed_string(char *string, unsigned long string_length, struct JSONObject *json);

char *json_get_string(struct JSONObject *json, char *key);
struct JSONObject *json_get_json(struct JSONObject *json, char *key);

void json_parse_string(char *string, unsigned long string_length, unsigned long byte, char *parsed_string);

enum JSONObjectParsingIdentity {
    JSON_PARSING_IDENTITY_NULL,
    JSON_PARSING_IDENTITY_KEY,
    JSON_PARSING_IDENTITY_VALUE
};

#endif /* json_object_h */
