//
//  bounding_box.h
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#ifndef bounding_box_h
#define bounding_box_h

struct BoundingBox {
    float x1, x2;
    float y1, y2;
    float z1, z2;
};

struct BoundingBox *bounding_box_create(double x1, double y1, double z1, double x2, double y2, double z2);
void bounding_box_destroy(struct BoundingBox *box);

float bounding_box_calculate_height(struct BoundingBox *box);

#endif /* bounding_box_h */
