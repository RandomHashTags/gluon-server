//
//  statistic_value.c
//  quark
//
//  Created by Evan Anderson on 11/21/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "statistic_value.h"

struct StatisticValue *statistic_value_create(const struct Statistic *statistic) {
    struct StatisticValue *value = malloc(sizeof(struct StatisticValue));
    if (!value) {
        printf("failed to allocate memory for a StatisticValue\n");
        return NULL;
    }
    value->statistic = statistic;
    return value;
}
void statistic_value_destroy(struct StatisticValue *value) {
    free((struct Statistic *) value->statistic);
    free(value);
}
