//
//  json_value_type.h
//  quark
//
//  Created by Evan Anderson on 11/22/22.
//

#ifndef json_value_type_h
#define json_value_type_h

enum JSONValueType {
    JSON_VALUE_TYPE_JSON_OBJECT,
    JSON_VALUE_TYPE_JSON_ARRAY,
    
    JSON_VALUE_TYPE_STRING,
    JSON_VALUE_TYPE_INTEGER,
    JSON_VALUE_TYPE_FLOAT,
    JSON_VALUE_TYPE_DOUBLE
};

#endif /* json_value_type_h */
