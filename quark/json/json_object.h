//
//  json_object.h
//  quark
//
//  Created by Evan Anderson on 11/25/22.
//

#ifndef json_object_h
#define json_object_h

struct JSONObject {
    unsigned long strings_count;
    struct JSONObjectValueString *strings;
    
    unsigned long jsons_count;
    struct JSONObject *jsons;
    
    unsigned long to_string_length;
};

struct JSONObjectValueString {
    char *key;
    unsigned char key_length;
    char *value;
    unsigned char value_length;
    unsigned short to_string_length;
};

void json_object_destroy(struct JSONObject *json);
void json_object_calculate_string_length(struct JSONObject *json);
void json_object_to_string(struct JSONObject *json, char *to_string);

void json_object_value_string_calculate_string_length(struct JSONObjectValueString *value_string);
void json_object_value_string_to_string(struct JSONObjectValueString *value_string, char *to_string);

void json_object_parse_fixed_size(const char *string, const unsigned long string_length, const unsigned long string_count, struct JSONObject *parsed_json);

void json_parse_string(const char *string, const unsigned long string_length, unsigned long byte, char *parsed_string);

#endif /* json_object_h */
