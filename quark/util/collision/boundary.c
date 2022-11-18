//
//  boundary.c
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#include "boundary.h"

void boundary_destroy(struct Boundary *boundary) {
    const enum BoundaryType type = boundary->type;
    switch (type) {
        case BOUNDARY_TYPE_BOX:
            bounding_box_destroy(boundary->box);
            break;
        case BOUNDARY_TYPE_CIRCLE:
            bounding_circle_destroy(boundary->circle);
            break;
        default:
            break;
    }
}
