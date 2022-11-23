//
//  json_object.h
//  quark
//
//  Created by Evan Anderson on 11/22/22.
//

#ifndef json_object_h
#define json_object_h

#include "json_value_type.h"

struct LegacyJSONObject {
    unsigned long keys_index;
    unsigned long keys_count;
    
    struct LegacyJSONObjectValue *values;
    
    unsigned long to_string_length;
};

struct LegacyJSONObjectValue {
    const char *key;
    enum JSONValueType type;
    union {
        char *value_string;
        float value_float;
        double value_double;
        long value_long;
    };
};

void json_parse_from_string(char *string, struct LegacyJSONObject *json);

void json_get_value(const char *key, const enum JSONValueType type, void *value);

void json_to_string(struct LegacyJSONObject json, char *string);
void json_to_string_append_float(float value, char *string, unsigned long index);
void json_to_string_append_string(char *value, char *string, unsigned long index);

#endif /* json_object_h */
