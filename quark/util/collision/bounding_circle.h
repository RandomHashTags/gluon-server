//
//  bounding_circle.h
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#ifndef bounding_circle_h
#define bounding_circle_h

struct BoundingCircle {
    unsigned short radius;
};

struct BoundingCircle *bounding_circle_create(unsigned short radius);
void bounding_circle_destroy(struct BoundingCircle *circle);

#endif /* bounding_circle_h */
