//
//  player.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef player_h
#define player_h

#include <stdio.h>
#include "location.h"

struct Player {
    char uuid[36];
    char name[18];
    char display_name[18];
    struct Location location;
};

#endif /* player_h */
