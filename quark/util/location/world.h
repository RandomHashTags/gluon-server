//
//  world.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef world_h
#define world_h

struct World {
    const int seed[32];
    const char *name;
};

void world_destroy(struct World *world);

void world_load_chunk(struct World *world, int x, int z);
void world_unload_chunk(struct World *world, int x, int z);

#endif /* world_h */
