//
//  chunk_generator.h
//  gluon
//
//  Created by Evan Anderson on 11/17/22.
//

#ifndef chunk_generator_h
#define chunk_generator_h

struct ChunkGenerator {
    const char *identifier;
};

struct ChunkGenerator *chunk_generator_create(const char *identifier);
void chunk_generator_destroy(struct ChunkGenerator *generator);

#endif /* chunk_generator_h */
