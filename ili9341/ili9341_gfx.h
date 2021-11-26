#ifndef __ILI9341_GFX_H
#define __ILI9341_GFX_H

#include "ili9341.h"

#define __LEu16(addr)                            \
  (((((uint16_t)(*(((uint8_t *)(addr)) + 1)))) | \
    (((uint16_t)(*(((uint8_t *)(addr)) + 0))) << 8U)))

#define __ILI9341_COLOR565(r, g, b) \
  ((((r)&0xF8) << 8) |              \
   (((g)&0xFC) << 3) |              \
   (((b)&0xF8) >> 3))

void ili9341_set_address_rect(ili9341 *inst, uint16_t x0, uint16_t y0, uint16_t w, uint16_t h);
void ili9341_fill_rect(ili9341 *inst, uint16_t color,
                       int16_t x, int16_t y, uint16_t w, uint16_t h);
void ili9341_transmit_color(ili9341 *inst, uint16_t size, uint16_t color[] /* already byte-swapped (LE) */, bool wait);

#endif
