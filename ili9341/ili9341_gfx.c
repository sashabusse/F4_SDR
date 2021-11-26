#include "ili9341_gfx.h"

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
    uint32_t num_pixels = w * h;

    // fill entire block with ordered color data
    uint16_t color_le = __LEu16(&color);
    for (uint16_t i = 0; i < num_pixels; ++i)
    {
        spi_tx_block[i] = color_le;
    }

    // select target region
    ili9341_set_address_rect(inst, x, y, w, h);

    ili9341_hw_select(&(inst->hw));
    ili9341_hw_dc_data(&(inst->hw));

    // repeatedly send MIN(remaining-words, block-words) words of color data until
    // all rect words have been sent.
    ili9341_transmit_color(inst, num_pixels * 2 /*16-bit words*/, spi_tx_block, true);

    ili9341_hw_unselect(&(inst->hw));
}

void ili9341_transmit_color(ili9341 *inst, uint16_t size, uint16_t color[] /* already byte-swapped (LE) */, bool wait)
{
    if ((NULL == inst) || (0 == size) || (NULL == color))
    {
        return;
    }

    ili9341_hw_spi_send_sync(&(inst->hw), (uint8_t *)color, size, false);
}