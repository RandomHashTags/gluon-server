//
//  dye_color.h
//  quark
//
//  Created by Evan Anderson on 11/12/22.
//

#ifndef dye_color_h
#define dye_color_h

#include "color.h"

typedef struct DyeColor {
    const char identifier[24];
    const struct Color color;
    const struct Color firework_color;
} DyeColor;

extern DyeColor DYE_COLOR_MINECRAFT_BLACK;
extern DyeColor DYE_COLOR_MINECRAFT_BLUE;
extern DyeColor DYE_COLOR_MINECRAFT_BROWN;
extern DyeColor DYE_COLOR_MINECRAFT_CYAN;
extern DyeColor DYE_COLOR_MINECRAFT_GRAY;
extern DyeColor DYE_COLOR_MINECRAFT_GREEN;
extern DyeColor DYE_COLOR_MINECRAFT_LIGHT_BLUE;
extern DyeColor DYE_COLOR_MINECRAFT_LIME;
extern DyeColor DYE_COLOR_MINECRAFT_MAGENTA;
extern DyeColor DYE_COLOR_MINECRAFT_ORANGE;
extern DyeColor DYE_COLOR_MINECRAFT_PINK;
extern DyeColor DYE_COLOR_MINECRAFT_PURPLE;
extern DyeColor DYE_COLOR_MINECRAFT_RED;
extern DyeColor DYE_COLOR_MINECRAFT_SILVER;
extern DyeColor DYE_COLOR_MINECRAFT_WHITE;
extern DyeColor DYE_COLOR_MINECRAFT_YELLOW;

#endif /* dye_color_h */
