//
//  json_object.h
//  quark
//
//  Created by Evan Anderson on 11/22/22.
//

#ifndef json_object_h
#define json_object_h

struct JSONObject {
    unsigned short keys_boolean_count;
    char **keys_boolean;
    unsigned short *keys_boolean_lengths;
    _Bool *values_booleans;
    
    unsigned short keys_string_count;
    char **keys_string;
    unsigned short *keys_string_lengths;
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

void json_parse_from_fixed_string(char *string, const unsigned long string_length, void *json_function_pointer(struct JSONObject));

char *json_get_string(struct JSONObject *json, char *key);
struct JSONObject *json_get_json(struct JSONObject *json, char *key);

void json_parse_json(char *string, unsigned long string_length, unsigned long byte, struct JSONObject *parsed_json);
void json_parse_string(char *string, unsigned long string_length, unsigned long byte, char *parsed_string);

#endif /* json_object_h */
