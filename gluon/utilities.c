//
//  utilities.c
//  gluon
//
//  Created by Evan Anderson on 11/7/22.
//

#include <stdlib.h>
#include <string.h>
#include "utilities.h"

char *malloc_string(const char string[]) {
    const size_t string_length = strlen(string);
    char *copy = malloc(string_length + 1);
    if (!copy) {
        return NULL;
    }
    size_t i;
    for (i = 0; i < string_length; i++) {
        copy[i] = string[i];
    }
    copy[string_length] = '\0';
    return copy;
}

unsigned long current_time_nano(void) {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_nsec;
}
unsigned long current_time_milli(void) {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    unsigned long seconds = (unsigned long) now.tv_sec * 1000;
    unsigned long milliseconds = (unsigned long) now.tv_nsec / 1000;
    return seconds + milliseconds;
}

void benchmark_function(int count, void *pointer(void)) {
    clock_t now;
    for (int i = 0; i < count; i++) {
        now = clock();
        pointer();
        now = clock() - now;
        double took_s = ((double) now) / CLOCKS_PER_SEC;
        double took_ms = took_s * 1000;
        double took_ns = took_ms * 1000000;
        printf("benchmark_function; took %f seconds (%fms, %fns)\n", took_s, took_ms, took_ns);
    }
}
