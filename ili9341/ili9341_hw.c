#include "ili9341_hw.h"

void ili9341_hw_init(ili9341_hw_cfg *hw)
{
    hw->_dcfg.circular = false;
    hw->_dcfg.end_cb = NULL;
    hw->_dcfg.ssport = hw->nss_port;
    hw->_dcfg.sspad = hw->nss_pin;
    hw->_dcfg.cr1 = (0 << SPI_CR1_BIDIMODE_Pos) |
                    (0 << SPI_CR1_CRCEN_Pos) |
                    (0 << SPI_CR1_DFF_Pos) |
                    (1 << SPI_CR1_SSM_Pos) |
                    (1 << SPI_CR1_SSI_Pos) |
                    (0 << SPI_CR1_LSBFIRST_Pos) |
                    (ILI9341_HW_SPI_BR << SPI_CR1_BR_Pos) |
                    (1 << SPI_CR1_MSTR_Pos) |
                    (0 << SPI_CR1_CPOL_Pos) |
                    (0 << SPI_CR1_CPHA_Pos);
    hw->_dcfg.cr2 = 0;

    spiStart(hw->pSPID, &(hw->_dcfg));
}

void ili9341_hw_select(ili9341_hw_cfg *hw)
{
    spiSelect(hw->pSPID);
}

void ili9341_hw_unselect(ili9341_hw_cfg *hw)
{
    spiUnselect(hw->pSPID);
}

void ili9341_hw_dc_data(ili9341_hw_cfg *hw)
{
    palSetPad(hw->dc_port, hw->dc_pin);
}

void ili9341_hw_dc_command(ili9341_hw_cfg *hw)
{
    palClearPad(hw->dc_port, hw->dc_pin);
}

void ili9341_hw_reset_write(ili9341_hw_cfg *hw, int val)
{
    if (val == 0)
        palClearPad(hw->rst_port, hw->rst_pin);
    else
        palSetPad(hw->rst_port, hw->rst_pin);
}

void ili9341_hw_spi_send_sync(ili9341_hw_cfg *hw, uint8_t *data, size_t n, bool drive_cs)
{
    if (drive_cs)
        ili9341_hw_select(hw);

    spiSend(hw->pSPID, n, data);

    if (drive_cs)
        ili9341_hw_unselect(hw);
}

void ili9341_hw_delay_ms(int delay_ms)
{
    chThdSleepMilliseconds(delay_ms);
}
