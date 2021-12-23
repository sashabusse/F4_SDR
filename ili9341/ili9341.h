#ifndef __ILI_9341_H
#define __ILI_9341_H

#include "ili9341_hw.h"

/**
 * @brief native endianness of platform.
 *          should be LSB or MSB
 */
#define NATIVE_ENDIANNESS_LSB TRUE

/**
 * @brief   size of memory block to allocate statically
 *          for common internal operations like draw_char e.t.c.
 */
#define ILI9341_SPI_BUF_SZ 4096

/**
 * @brief swap endiannes of uint16_t at given addr
 */
#define __LSB2MSBu16_ptr(addr)                     \
    (((((uint16_t)(*(((uint8_t *)(addr)) + 1)))) | \
      (((uint16_t)(*(((uint8_t *)(addr)) + 0))) << 8U)))

/**
 * @brief swap endiannes of uint16_t value
 */
#define __LSB2MSBu16(val)                \
    ((uint16_t)(((uint16_t)val) << 8)) | \
        ((uint16_t)(((uint16_t)val) >> 8))

/**
 * @brief rgb565 format in native endianness of platform
 */
#define __ILI9341_RGB565_NATIVE(r, g, b) \
    ((((r)&0xF8) << 8) |                 \
     (((g)&0xFC) << 3) |                 \
     (((b)&0xF8) >> 3))

/**
 * @brief ili9341 spi endianess is msb
 *          so if platform is lsb (arm) we need to swap bytes
 *          all the color variable in this api are expected to be in msb format
 */
#if NATIVE_ENDIANNESS_LSB
#define ILI9341_RGB565(r, g, b) __LSB2MSBu16(__ILI9341_RGB565_NATIVE(r, g, b))
#endif
#if !NATIVE_ENDIANNESS_LSB
#define ILI9341_RGB565(r, g, b) __ILI9341_RGB565_NATIVE(r, g, b)
#endif

typedef struct
{
    ili9341_hw_cfg hw;
} ili9341;

void ili9341_hard_reset(ili9341 *driver_inst);

void ili9341_spi_write_command(ili9341 *driver_inst, uint8_t command, bool drive_cs);
void ili9341_spi_write_data(ili9341 *driver_inst, size_t sz, uint8_t *data, bool drive_cs);
void ili9341_spi_write_command_data(ili9341 *driver_inst, uint8_t command, size_t sz, uint8_t *data, bool drive_cs);

void ili9341_init(ili9341 *driver_inst);

#endif
