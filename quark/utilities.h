//
//  utilities.h
//  quark
//
//  Created by Evan Anderson on 11/7/22.
//

#ifndef utilities_h
#define utilities_h

#include <sys/time.h>
#include "server/quark_server.h"

extern unsigned char TICKS_PER_SECOND;
extern float TICKS_PER_SECOND_MULTIPLIER;
extern unsigned char BLOCK_BREAK_DELAY_TICKS;
extern const float GRAVITY;
extern float GRAVITY_PER_TICK;
extern struct QuarkServer *SERVER;

char *malloc_string(const char string[]);
int64_t current_time_nano(void);
int64_t current_time_milli(void);

#endif /* utilities_h */
