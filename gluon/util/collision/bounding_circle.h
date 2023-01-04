//
//  bounding_circle.h
//  gluon
//
//  Created by Evan Anderson on 11/18/22.
//

#ifndef bounding_circle_h
#define bounding_circle_h

struct BoundingCircle {
    float radius;
};

struct BoundingCircle *bounding_circle_create(float radius);
void bounding_circle_destroy(struct BoundingCircle *circle);

const float bounding_circle_calculate_height(struct BoundingCircle *circle);

#endif /* bounding_circle_h */
