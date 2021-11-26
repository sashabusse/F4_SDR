#ifndef __ILI9341_HW_H
#define __ILI9341_HW_H

#include "hal.h"
#include "ch.h"

typedef struct ili9341_hw_cfg
{
    SPIDriver *pSPID;

    ioportid_t rst_port;
    uint_fast8_t rst_pin;

    ioportid_t dc_port;
    uint_fast8_t dc_pin;

    ioportid_t nss_port;
    uint_fast8_t nss_pin;

    SPIConfig _dcfg;
} ili9341_hw_cfg;

void ili9341_hw_init(ili9341_hw_cfg *hw);

void ili9341_hw_select(ili9341_hw_cfg *hw);
void ili9341_hw_unselect(ili9341_hw_cfg *hw);

void ili9341_hw_dc_data(ili9341_hw_cfg *hw);
void ili9341_hw_dc_command(ili9341_hw_cfg *hw);

void ili9341_hw_reset_write(ili9341_hw_cfg *hw, int val);

void ili9341_hw_spi_send_sync(ili9341_hw_cfg *hw, uint8_t *data, size_t n, bool drive_cs);

void ili9341_hw_delay_ms(int delay_ms);

#endif
