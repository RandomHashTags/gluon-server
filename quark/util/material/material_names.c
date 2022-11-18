//
//  material_names.c
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "material_names.h"
#include "../../utilities.h"

struct MaterialNames *material_names_create(const char *english) {
    struct MaterialNames *names = malloc(sizeof(struct MaterialNames));
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
void material_names_destroy(struct MaterialNames *names) {
    free((char *) names->english);
    free(names);
}
