#ifndef color_h
#define color_h

#include "app.h"

/* may just be a place to put the color array... but may go for raw rgb values */
typedef struct {
   u8    r;
   u8    g;
   u8    b;
} color;

color colorRanger(u8 input, u8 type);
color color8(u8 input, u8 type);
color colorRotator(color cIn, s8 direction);

color colorArpTriad(u8 arpmode, u8 increment);
color colorArpMcp(u8 arpmode, u8 increment);

#endif /* color_h */
