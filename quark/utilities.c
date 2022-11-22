//
//  utilities.c
//  quark
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

int64_t current_time_nano(void) {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_usec;
}
int64_t current_time_milli(void) {
    struct timeval now;
    gettimeofday(&now, NULL);
    int64_t seconds = (int64_t) now.tv_sec * 1000;
    int64_t milliseconds = now.tv_usec / 1000;
    return seconds + milliseconds;
}
