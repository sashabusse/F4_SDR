#ifndef __ILI9341_GFX_H
#define __ILI9341_GFX_H

#include "ili9341.h"
#include "bitmaps/bitmaps.h"

#define __LEu16(addr)                            \
  (((((uint16_t)(*(((uint8_t *)(addr)) + 1)))) | \
    (((uint16_t)(*(((uint8_t *)(addr)) + 0))) << 8U)))

#define __ILI9341_COLOR565(r, g, b) \
  ((((r)&0xF8) << 8) |              \
   (((g)&0xFC) << 3) |              \
   (((b)&0xF8) >> 3))

typedef struct
{
  uint16_t width;
  uint16_t height;
  uint16_t scaley;
  uint16_t slide;
  uint16_t stride;
  const uint32_t *bitmap;
} font_t;

extern const font_t NF20x24;
extern const font_t NF32x24;
extern const font_t NF32x48;
extern const font_t ICON48x20;

void ili9341_set_address_rect(ili9341 *inst, uint16_t x0, uint16_t y0, uint16_t w, uint16_t h);
void ili9341_fill_rect(ili9341 *inst, uint16_t color,
                       int16_t x, int16_t y, uint16_t w, uint16_t h);

void ili9341_draw_map(ili9341 *inst, int x, int y, int w, int h, uint16_t *map);
void ili9341_drawchar_5x7(ili9341 *inst, uint8_t ch, int x, int y, uint16_t fg_col, uint16_t bg_col);

void ili9341_draw_font(ili9341 *inst, uint8_t ch, const font_t *font, int x, int y, uint16_t fg_col, uint16_t bg_col);
void ili9341_draw_font_string(ili9341 *inst, const char *str, const font_t *font, int x, int y, uint16_t fg_col, uint16_t bg_col);

#endif
