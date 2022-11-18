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
