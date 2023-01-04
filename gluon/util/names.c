//
//  material_names.c
//  gluon
//
//  Created by Evan Anderson on 11/13/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "names.h"
#include "../utilities.h"

struct Names *names_create(const char *english) {
    struct Names *names = malloc(sizeof(struct Names));
    if (!names) {
        printf("failed to allocate memory for a MaterialNames\n");
        return NULL;
    }
    const char *target_english = malloc_string(english);
    if (!target_english) {
        free(names);
        printf("failed to allocate memory for a MaterialNames target_english\n");
        return NULL;
    }
    names->english = target_english;
    return names;
}
void names_destroy(struct Names *names) {
    free((char *) names->english);
    free(names);
}
