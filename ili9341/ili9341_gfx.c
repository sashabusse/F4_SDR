/**
 * @file ili9341_gfx.c
 * @brief 
 * 
 * @todo    make assertions
 *          standardize cs_control flag
 *          develop async api
 *          reusage of buffer or splitting calls
 */

#include "ili9341_gfx.h"

// common buffer for spi operations
extern uint16_t ili9341_spi_buffer[4096];

void ili9341_set_address_rect(ili9341 *inst, uint16_t x0, uint16_t y0, uint16_t w, uint16_t h)
{
    ili9341_hw_select(&(inst->hw));

    // column address set
    ili9341_spi_write_command_data(inst, 0x2A, 4,
                                   (uint8_t[]){
                                       (x0 >> 8) & 0xFF, x0 & 0xFF,
                                       ((x0 + w - 1) >> 8) & 0xFF, (x0 + w - 1) & 0xFF},
                                   false);

    // row address set
    ili9341_spi_write_command_data(inst, 0x2B, 4,
                                   (uint8_t[]){
                                       (y0 >> 8) & 0xFF, y0 & 0xFF,
                                       ((y0 + h - 1) >> 8) & 0xFF, (y0 + h - 1) & 0xFF},
                                   false);

    // write to RAM
    ili9341_spi_write_command(inst, 0x2C, false);

    ili9341_hw_unselect(&(inst->hw));
}

uint16_t spi_tx_block[80 * 80];
void ili9341_fill_rect(ili9341 *inst, uint16_t color,
                       int16_t x, int16_t y, uint16_t w, uint16_t h)
{
    uint32_t pix_cnt = w * h;

    // fill entire block with ordered color data
    uint16_t color_le = __LEu16(&color);
    for (uint16_t i = 0; i < pix_cnt; ++i)
    {
        spi_tx_block[i] = color_le;
    }

    // select target region
    ili9341_set_address_rect(inst, x, y, w, h);

    ili9341_hw_select(&(inst->hw));
    ili9341_hw_dc_data(&(inst->hw));

    ili9341_hw_spi_send_sync(&(inst->hw), (uint8_t *)spi_tx_block, pix_cnt * 2, false);

    ili9341_hw_unselect(&(inst->hw));
}

void ili9341_draw_map(ili9341 *inst, int x, int y, int w, int h, uint16_t *map)
{
    ili9341_set_address_rect(inst, x, y, w, h);
    int pix_cnt = w * h;

    ili9341_hw_dc_data(&(inst->hw));
    ili9341_hw_select(&(inst->hw));
    ili9341_hw_spi_send_sync(&(inst->hw), (uint8_t *)map, 2 * pix_cnt, false);

    ili9341_hw_unselect(&(inst->hw));
}

void ili9341_drawchar_5x7(ili9341 *inst, uint8_t ch, int x, int y, uint16_t fg_col, uint16_t bg_col)
{
    uint16_t *buf = ili9341_spi_buffer;
    uint16_t bits;
    int c, r;
    for (c = 0; c < 7; c++)
    {
        bits = x5x7_bits[(ch * 7) + c];
        for (r = 0; r < 5; r++)
        {
            *buf++ = (0x8000 & bits) ? fg_col : bg_col;
            bits <<= 1;
        }
    }
    ili9341_draw_map(inst, x, y, 5, 7, ili9341_spi_buffer);
}

void ili9341_drawstring_5x7(ili9341 *inst, const char *str, int x, int y, uint16_t fg_col, uint16_t bg_col)
{
    while (*str)
    {
        ili9341_drawchar_5x7(inst, *str, x, y, fg_col, bg_col);
        x += 5;
        str++;
    }
}

// << text drawing functionality >> ----------------------------------------------------------

// default fonts
const font_t NF20x24 = {20, 24, 1, 24, 1, (const uint32_t *)numfont20x24};
const font_t NF32x24 = {32, 24, 1, 24, 1, (const uint32_t *)numfont32x24};
const font_t NF32x48 = {32, 48, 2, 24, 1, (const uint32_t *)numfont32x24};
const font_t ICON48x20 = {48, 20, 1, 40, 2, (const uint32_t *)icons48x20};

void ili9341_draw_font(ili9341 *inst, uint8_t ch, const font_t *font, int x, int y, uint16_t fg_col, uint16_t bg_col)
{
    uint16_t *buf = ili9341_spi_buffer;
    uint32_t bits;
    const uint32_t *bitmap = &font->bitmap[font->slide * ch];
    int c, r, j, b;

    for (c = 0; c < font->slide; c += font->stride)
    {
        for (j = 0; j < font->scaley; j++)
        {
            int cc = c;
            for (r = 0; r < font->width;)
            {
                bits = bitmap[cc++];
                for (b = 0; b < 32 && r < font->width; b++, r++)
                {
                    *buf++ = (0x80000000UL & bits) ? fg_col : bg_col;
                    bits <<= 1;
                }
            }
        }
    }
    ili9341_draw_map(inst, x, y, font->width, font->height, ili9341_spi_buffer);
}

void ili9341_draw_font_string(ili9341 *inst, const char *str, const font_t *font, int x, int y, uint16_t fg_col, uint16_t bg_col)
{
    while (*str)
    {
        char c = *str++;
        if (c >= '0' && c <= '9')
            ili9341_draw_font(inst, c - '0', font, x, y, fg_col, bg_col);
        else if (c > 0 && c < 7)
            ili9341_draw_font(inst, c + 9, font, x, y, fg_col, bg_col);
        else if (c == '.')
            ili9341_draw_font(inst, 10, font, x, y, fg_col, bg_col);
        else if (c == '-')
            ili9341_draw_font(inst, 11, font, x, y, fg_col, bg_col);
        else
            ili9341_fill_rect(inst, bg_col, x, y, font->width, font->height);
        x += font->width;
    }
}

// -------------------------------------------------------------------------------------------
