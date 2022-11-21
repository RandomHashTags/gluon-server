//
//  statistic.c
//  quark
//
//  Created by Evan Anderson on 11/21/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "statistic.h"
#include "../../utilities.h"

struct Statistic *statistic_create(const char *identifier) {
    struct Statistic *statistic = malloc(sizeof(struct Statistic));
    if (!statistic) {
        printf("failed to allocate memory for a Statistic\n");
        return NULL;
    }
    const char *target_identifier = malloc_string(identifier);
    if (!target_identifier) {
        free(statistic);
        printf("failed to allocate memory for a Statistic target_identifier\n");
        return NULL;
    }
    statistic->identifier = target_identifier;
    return statistic;
}
