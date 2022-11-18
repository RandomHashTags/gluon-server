//
//  utilities.h
//  quark
//
//  Created by Evan Anderson on 11/7/22.
//

#ifndef utilities_h
#define utilities_h

#include "server/quark_server.h"

extern unsigned short TICKS_PER_SECOND;
extern float TICKS_PER_SECOND_MULTIPLIER;
extern unsigned short BLOCK_BREAK_DELAY_TICKS;
extern struct QuarkServer *SERVER;

char *malloc_string(const char *string);

#endif /* utilities_h */
