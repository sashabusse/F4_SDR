#ifndef __UI_COLOR_SCHEME_H
#define __UI_COLOR_SCHEME_H

#include "ili9341.h"

// << common interface colors >> ----------------
#define UI_BG_ACTIVE 0xffff //ILI9341_RGB565(30, 30, 15)
#define UI_BG_NORMAL 0x0000

#define UI_FG_ACTIVE 0x0000 //ILI9341_RGB565(128, 255, 128)
#define UI_FG_NORMAL 0xffff
// ----------------------------------------------

// << spectrogram colors >> ---------------------
#define UI_SPD_BG UI_BG_NORMAL
#define UI_SPD_FG UI_FG_NORMAL
#define UI_SPD_LVL_LINES ILI9341_RGB565(15, 15, 15)
#define UI_SPD_VLINE ILI9341_RGB565(230, 0, 0)
//-----------------------------------------------

#endif