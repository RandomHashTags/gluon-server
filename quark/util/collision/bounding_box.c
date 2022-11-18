//
//  bounding_box.c
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "bounding_box.h"

struct BoundingBox *bounding_box_create(double x1, double y1, double z1, double x2, double y2, double z2) {
    struct BoundingBox *box = malloc(sizeof(struct BoundingBox));
    if (!box) {
        printf("failed to allocate memory for a BoundingBox\n");
        return NULL;
    }
    box->x1 = x1;
    box->y1 = y1;
    box->z1 = z1;
    box->x2 = x2;
    box->y2 = y2;
    box->z2 = z2;
    return box;
}
void bounding_box_destroy(struct BoundingBox *box) {
    free(box);
}
