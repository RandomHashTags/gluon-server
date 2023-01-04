//
//  utilities.h
//  gluon
//
//  Created by Evan Anderson on 11/7/22.
//

#ifndef utilities_h
#define utilities_h

#include <time.h>
#include "server/gluon_server.h"

extern unsigned char TICKS_PER_SECOND;
extern float TICKS_PER_SECOND_MULTIPLIER;
extern unsigned char BLOCK_BREAK_DELAY_TICKS;
extern const float GRAVITY;
extern float GRAVITY_PER_TICK;
extern struct GluonServer *SERVER;

char *malloc_string(const char string[]);
unsigned long current_time_nano(void);
unsigned long current_time_milli(void);

void benchmark_function(int count, void *pointer(void));

#endif /* utilities_h */
