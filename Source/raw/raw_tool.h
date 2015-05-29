#ifndef XEEN_RAW_TOOL_H
#define XEEN_RAW_TOOL_H

#include <stdio.h>
#include "../xeen/xeen.h"
#include "../sprite/sprite_tool.h"

extern uint16_t xeen_raw_size[XEEN_COORDS];

int xeen_read_raw(FILE *fp, long o, XeenSprite *raw);

#endif /* XEEN_RAW_TOOL_H */

