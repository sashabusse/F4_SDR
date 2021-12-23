#include "math_util.h"

uint16_t log2_i64(uint64_t x)
{
    uint64_t mask = 0xffffffff00000000;
    uint16_t bit = 32;
    int16_t y = 63;
    uint8_t i;

    if (x == 0)
        return 0;
    // 32
    if ((x & mask) == 0)
    {
        x <<= bit;
        y -= bit;
    }
    bit >>= 1;
    mask <<= bit;
    // 16
    if ((x & mask) == 0)
    {
        x <<= bit;
        y -= bit;
    }
    bit >>= 1;
    mask <<= bit;
    // 8
    if ((x & mask) == 0)
    {
        x <<= bit;
        y -= bit;
    }
    bit >>= 1;
    mask <<= bit;
    // 4
    if ((x & mask) == 0)
    {
        x <<= bit;
        y -= bit;
    }
    bit >>= 1;
    mask <<= bit;
    // 2
    if ((x & mask) == 0)
    {
        x <<= bit;
        y -= bit;
    }
    bit >>= 1;
    mask <<= bit;
    // 1
    if ((x & mask) == 0)
    {
        x <<= bit;
        y -= bit;
    }
    // msb should be 1. take next 8 bits.
    i = (x >> (63 - 8)) & 0xff;
    // lookup logarythm table
    return (y << 8) | i;
}
