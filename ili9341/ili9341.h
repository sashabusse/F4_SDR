#ifndef __ILI_9341_H
#define __ILI_9341_H

#include "ili9341_hw.h"

typedef struct
{
    ili9341_hw_cfg hw;
} ili9341;

void ili9341_hard_reset(ili9341 *inst);

void ili9341_spi_write_command(ili9341 *inst, uint8_t command, bool drive_cs);
void ili9341_spi_write_data(ili9341 *inst, size_t sz, uint8_t *data, bool drive_cs);
void ili9341_spi_write_command_data(ili9341 *inst, uint8_t command, size_t sz, uint8_t *data, bool drive_cs);

void ili9341_init(ili9341 *inst);

#endif
