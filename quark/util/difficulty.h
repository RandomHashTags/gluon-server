//
//  difficulty.h
//  quark
//
//  Created by Evan Anderson on 11/12/22.
//

#ifndef difficulty_h
#define difficulty_h

struct Difficulty {
    const char *identifier;
};

extern const struct Difficulty DIFFICULTY_MINECRAFT_WORLD_BASED;
extern const struct Difficulty DIFFICULTY_MINECRAFT_PEACEFUL;
extern const struct Difficulty DIFFICULTY_MINECRAFT_EASY;
extern const struct Difficulty DIFFICULTY_MINECRAFT_NORMAL;
extern const struct Difficulty DIFFICULTY_MINECRAFT_HARD;

#endif /* difficulty_h */
