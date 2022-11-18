//
//  sound.h
//  quark
//
//  Created by Evan Anderson on 11/18/22.
//

#ifndef sound_h
#define sound_h

struct Sound {
    const char *identifier;
};

struct Sound *sound_create(const char *identifier);
void sound_destroy(struct Sound *sound);

#endif /* sound_h */
