//
//  boundary.h
//  gluon
//
//  Created by Evan Anderson on 11/18/22.
//

#ifndef boundary_h
#define boundary_h

#include "boundary_type.h"
#include "bounding_box.h"
#include "bounding_circle.h"

struct Boundary {
    const enum BoundaryType type;
    union {
        struct BoundingBox *box;
        struct BoundingCircle *circle;
    };
};

struct Boundary *boundary_create(const enum BoundaryType type, struct BoundingBox *box, struct BoundingCircle *circle);
void boundary_destroy(struct Boundary *boundary);

#endif /* boundary_h */
