//
//  statistic.h
//  gluon
//
//  Created by Evan Anderson on 11/21/22.
//

#ifndef statistic_h
#define statistic_h

#include "../value_type.h"

struct Statistic {
    const char *identifier;
    const enum ValueType value_type;
};

struct Statistic *statistic_create(const char *identifier, const enum ValueType value_type);
void statistic_destroy(struct Statistic *statistic);

#endif /* statistic_h */
