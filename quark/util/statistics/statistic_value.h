//
//  statistic_value.h
//  quark
//
//  Created by Evan Anderson on 11/21/22.
//

#ifndef statistic_value_h
#define statistic_value_h

#include "statistic.h"
#include "../value_type.h"

struct StatisticValue {
    const struct Statistic *statistic;
    union {
        char value_char;
        unsigned char value_char_unsigned;
        short value_short;
        unsigned short value_short_unsigned;
        
        int value_integer;
        unsigned int value_integer_unsigned;
        long value_long;
        unsigned long value_long_unsigned;
        
        float value_float;
        double value_double;
    };
};

struct StatisticValue *statistic_value_create(const struct Statistic *statistic);
void statistic_value_destroy(struct StatisticValue *value);

#endif /* statistic_value_h */
