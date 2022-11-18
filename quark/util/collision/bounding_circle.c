//
//  bounding_circle.c
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "bounding_circle.h"

struct BoundingCircle *bounding_circle_create(unsigned short radius) {
    struct BoundingCircle *circle = malloc(sizeof(struct BoundingCircle));
    if (!circle) {
        printf("failed to allocate memory for a BoundingCircle\n");
        return NULL;
    }
    circle->radius = radius;
    return circle;
}
void bounding_circle_destroy(struct BoundingCircle *circle) {
    free(circle);
}
