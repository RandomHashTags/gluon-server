//
//  statistic.h
//  quark
//
//  Created by Evan Anderson on 11/21/22.
//

#ifndef statistic_h
#define statistic_h

struct Statistic {
    const char *identifier;
};

struct Statistic *statistic_create(const char *identifier);
void statistic_destroy(struct Statistic *statistic);

#endif /* statistic_h */
