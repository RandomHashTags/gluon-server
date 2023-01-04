//
//  statistic_active.c
//  gluon
//
//  Created by Evan Anderson on 1/4/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "statistic_active.h"

struct StatisticActive *statistic_active_create(const struct Statistic *statistic) {
    struct StatisticActive *value = malloc(sizeof(struct StatisticActive));
    if (!value) {
        printf("failed to allocate memory for a StatisticActive\n");
        return NULL;
    }
    value->statistic = statistic;
    return value;
}
void statistic_active_destroy(struct StatisticActive *statistic) {
    free((struct StatisticActive *) statistic->statistic);
    free(statistic);
}

void statistic_active_increment_integer(struct StatisticActive *statistic, int amount) {
    statistic->value_integer += amount;
}
void statistic_active_increment_long(struct StatisticActive *statistic, long amount) {
    statistic->value_long += amount;
}
void statistic_active_increment_long_unsigned(struct StatisticActive *statistic, unsigned long amount) {
    statistic->value_long_unsigned += amount;
}
void statistic_active_increment_float(struct StatisticActive *statistic, float amount) {
    statistic->value_float += amount;
}
void statistic_active_increment_double(struct StatisticActive *statistic, double amount) {
    statistic->value_double += amount;
}
