//
//  names.h
//  gluon
//
//  Created by Evan Anderson on 11/13/22.
//

#ifndef names_h
#define names_h

struct Names {
    const char *english;
};

struct Names *names_create(const char *english);
void names_destroy(struct Names *names);

#endif /* names_h */
