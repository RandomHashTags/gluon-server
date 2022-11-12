//
//  difficulty.h
//  quark
//
//  Created by Evan Anderson on 11/12/22.
//

#ifndef difficulty_h
#define difficulty_h

typedef struct Difficulty {
    const char *identifier;
} Difficulty;

extern Difficulty DIFFICULTY_MINECRAFT_WORLD_BASED;
extern Difficulty DIFFICULTY_MINECRAFT_PEACEFUL;
extern Difficulty DIFFICULTY_MINECRAFT_EASY;
extern Difficulty DIFFICULTY_MINECRAFT_NORMAL;
extern Difficulty DIFFICULTY_MINECRAFT_HARD;

#endif /* difficulty_h */
