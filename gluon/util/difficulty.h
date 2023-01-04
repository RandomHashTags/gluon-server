//
//  difficulty.h
//  gluon
//
//  Created by Evan Anderson on 11/12/22.
//

#ifndef difficulty_h
#define difficulty_h

#include "names.h"

struct Difficulty {
    const char *identifier;
    const struct Names *names;
};

struct Difficulty *difficulty_create(const char *identifier, const struct Names *names);
void difficulty_destroy(struct Difficulty *difficulty);

#endif /* difficulty_h */
