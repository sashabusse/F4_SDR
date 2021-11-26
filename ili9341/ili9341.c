#include "ili9341.h"
#include "ch.h"
#include "hal.h"

/**
 * @brief hardware reset of driver
 * 
 * @param hw 
 */
void ili9341_hard_reset(ili9341 *inst)
{
    ili9341_hw_reset_write(&(inst->hw), 0);
    ili9341_hw_delay_ms(200);
    ili9341_hw_reset_write(&(inst->hw), 1);

    ili9341_hw_unselect(&(inst->hw));
}

void ili9341_spi_write_command(ili9341 *inst, uint8_t command, bool drive_cs)
{
    ili9341_hw_dc_command(&(inst->hw));
    ili9341_hw_spi_send_sync(&(inst->hw), &command, 1, drive_cs);
}

void ili9341_spi_write_data(ili9341 *inst, size_t sz, uint8_t *data, bool drive_cs)
{
    ili9341_hw_dc_data(&(inst->hw));
    ili9341_hw_spi_send_sync(&(inst->hw), data, sz, drive_cs);
}

void ili9341_spi_write_command_data(ili9341 *inst, uint8_t command, size_t sz, uint8_t *data, bool drive_cs)
{
    if (drive_cs)
        ili9341_hw_select(&(inst->hw));

    ili9341_spi_write_command(inst, command, false);
    ili9341_spi_write_data(inst, sz, data, false);

    if (drive_cs)
        ili9341_hw_unselect(&(inst->hw));
}

void ili9341_init(ili9341 *inst)
{
    ili9341_hw_init(&(inst->hw));
    ili9341_hard_reset(inst);

    // select to let other send operation not to drive cs
    ili9341_hw_select(&(inst->hw));

    // SOFTWARE RESET
    ili9341_spi_write_command(inst, 0x01, false);
    ili9341_hw_delay_ms(1000);

    // POWER CONTROL A
    ili9341_spi_write_command_data(inst, 0xCB, 5, (uint8_t[]){0x39, 0x2C, 0x00, 0x34, 0x02}, false);

    // POWER CONTROL B
    ili9341_spi_write_command_data(inst, 0xCF, 3, (uint8_t[]){0x00, 0xC1, 0x30}, false);

    // DRIVER TIMING CONTROL A
    ili9341_spi_write_command_data(inst, 0xE8, 3, (uint8_t[]){0x85, 0x00, 0x78}, false);

    // DRIVER TIMING CONTROL B
    ili9341_spi_write_command_data(inst, 0xEA, 2, (uint8_t[]){0x00, 0x00}, false);

    // POWER ON SEQUENCE CONTROL
    ili9341_spi_write_command_data(inst, 0xED, 4, (uint8_t[]){0x64, 0x03, 0x12, 0x81}, false);

    // PUMP RATIO CONTROL
    ili9341_spi_write_command_data(inst, 0xF7, 1, (uint8_t[]){0x20}, false);

    // POWER CONTROL,VRH[5:0]
    ili9341_spi_write_command_data(inst, 0xC0, 1, (uint8_t[]){0x23}, false);

    // POWER CONTROL,SAP[2:0];BT[3:0]
    ili9341_spi_write_command_data(inst, 0xC1, 1, (uint8_t[]){0x10}, false);

    // VCM CONTROL
    ili9341_spi_write_command_data(inst, 0xC5, 2, (uint8_t[]){0x3E, 0x28}, false);

    // VCM CONTROL 2
    ili9341_spi_write_command_data(inst, 0xC7, 1, (uint8_t[]){0x86}, false);

    // MEMORY ACCESS CONTROL
    ili9341_spi_write_command_data(inst, 0x36, 1, (uint8_t[]){0x48}, false);

    // PIXEL FORMAT
    ili9341_spi_write_command_data(inst, 0x3A, 1, (uint8_t[]){0x55}, false);

    // FRAME RATIO CONTROL, STANDARD RGB COLOR
    ili9341_spi_write_command_data(inst, 0xB1, 2, (uint8_t[]){0x00, 0x18}, false);

    // DISPLAY FUNCTION CONTROL
    ili9341_spi_write_command_data(inst, 0xB6, 3, (uint8_t[]){0x08, 0x82, 0x27}, false);

    // 3GAMMA FUNCTION DISABLE
    ili9341_spi_write_command_data(inst, 0xF2, 1, (uint8_t[]){0x00}, false);

    // GAMMA CURVE SELECTED
    ili9341_spi_write_command_data(inst, 0x26, 1, (uint8_t[]){0x01}, false);

    // POSITIVE GAMMA CORRECTION
    ili9341_spi_write_command_data(inst, 0xE0, 15,
                                   (uint8_t[]){0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00}, false);

    // NEGATIVE GAMMA CORRECTION
    ili9341_spi_write_command_data(inst, 0xE1, 15,
                                   (uint8_t[]){0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F}, false);

    // EXIT SLEEP
    ili9341_spi_write_command(inst, 0x11, false);
    ili9341_hw_delay_ms(120);

    // TURN ON DISPLAY
    ili9341_spi_write_command(inst, 0x29, false);

    // MADCTL ; constraint landscape inverse orientation fro now for easier operation
    ili9341_spi_write_command_data(inst, 0x36, 1, (uint8_t[]){0x20 | 0x08}, false);

    // release cs after operation
    ili9341_hw_unselect(&(inst->hw));
}
