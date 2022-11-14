//
//  dye_color.h
//  quark
//
//  Created by Evan Anderson on 11/12/22.
//

#ifndef dye_color_h
#define dye_color_h

#include "color.h"

struct DyeColor {
    const char *identifier;
    const struct Color color;
    const struct Color firework_color;
};

extern struct DyeColor DYE_COLOR_MINECRAFT_BLACK;
extern struct DyeColor DYE_COLOR_MINECRAFT_BLUE;
extern struct DyeColor DYE_COLOR_MINECRAFT_BROWN;
extern struct DyeColor DYE_COLOR_MINECRAFT_CYAN;
extern struct DyeColor DYE_COLOR_MINECRAFT_GRAY;
extern struct DyeColor DYE_COLOR_MINECRAFT_GREEN;
extern struct DyeColor DYE_COLOR_MINECRAFT_LIGHT_BLUE;
extern struct DyeColor DYE_COLOR_MINECRAFT_LIME;
extern struct DyeColor DYE_COLOR_MINECRAFT_MAGENTA;
extern struct DyeColor DYE_COLOR_MINECRAFT_ORANGE;
extern struct DyeColor DYE_COLOR_MINECRAFT_PINK;
extern struct DyeColor DYE_COLOR_MINECRAFT_PURPLE;
extern struct DyeColor DYE_COLOR_MINECRAFT_RED;
extern struct DyeColor DYE_COLOR_MINECRAFT_SILVER;
extern struct DyeColor DYE_COLOR_MINECRAFT_WHITE;
extern struct DyeColor DYE_COLOR_MINECRAFT_YELLOW;

#endif /* dye_color_h */
