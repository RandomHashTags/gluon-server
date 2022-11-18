//
//  material_names.h
//  quark
//
//  Created by Evan Anderson on 11/13/22.
//

#ifndef material_names_h
#define material_names_h

struct MaterialNames {
    const char *english;
};

struct MaterialNames *material_names_create(const char *english);
void material_names_destroy(struct MaterialNames *names);

#endif /* material_names_h */
