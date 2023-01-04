//
//  statistic_active.h
//  gluon
//
//  Created by Evan Anderson on 1/4/23.
//

#ifndef statistic_active_h
#define statistic_active_h

#include "statistic.h"

struct StatisticActive {
    const struct Statistic *statistic;
    union {
        char value_character;
        
        int value_integer;
        long value_long;
        unsigned long value_long_unsigned;
        float value_float;
        double value_double;
    };
};

struct StatisticActive *statistic_active_create(const struct Statistic *statistic);
void statistic_active_destroy(struct StatisticActive *statistic);

void statistic_active_increment_integer(struct StatisticActive *statistic, int amount);
void statistic_active_increment_long(struct StatisticActive *statistic, long amount);
void statistic_active_increment_long_unsigned(struct StatisticActive *statistic, unsigned long amount);
void statistic_active_increment_float(struct StatisticActive *statistic, float amount);
void statistic_active_increment_double(struct StatisticActive *statistic, double amount);

#endif /* statistic_active_h */
