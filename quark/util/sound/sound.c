//
//  sound.c
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "sound.h"
#include "../../utilities.h"

struct Sound *sound_create(const char *identifier) {
    struct Sound *sound = malloc(sizeof(struct Sound));
    if (!sound) {
        printf("failed to allocate memory for a Sound\n");
        return NULL;
    }
    const char *target_identifier = malloc_string(identifier);
    if (!target_identifier) {
        free(sound);
        printf("failed to allocate memory for a Sound target_identifier\n");
        return NULL;
    }
    sound->identifier = target_identifier;
    return sound;
}
void sound_destroy(struct Sound *sound) {
    free((char *) sound->identifier);
    free(sound);
}
