//
//  boundary.c
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boundary.h"

struct Boundary *boundary_create(const enum BoundaryType type, struct BoundingBox *box, struct BoundingCircle *circle) {
    struct Boundary *boundary = malloc(sizeof(struct Boundary));
    if (!boundary) {
        printf("failed to allocate memory for a Boundary\n");
        return NULL;
    }
    memcpy((enum BoundaryType *) &boundary->type, &type, sizeof(enum BoundaryType));
    switch (type) {
        case BOUNDARY_TYPE_BOX:
            boundary->box = box;
            break;
        case BOUNDARY_TYPE_CIRCLE:
            boundary->circle = circle;
            break;
        default:
            break;
    }
    return boundary;
}
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
