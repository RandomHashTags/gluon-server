//
//  difficulty.c
//  gluon
//
//  Created by Evan Anderson on 11/12/22.
//

#include <stdlib.h>
#include "difficulty.h"

void difficulty_destroy(struct Difficulty *difficulty) {
    free((char *) difficulty->identifier);
    names_destroy((struct Names *) difficulty->names);
    free(difficulty);
}
