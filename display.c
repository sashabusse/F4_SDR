#include "display.h"

#define __FPU_PRESENT
#include "CMSIS/DSP/Include/arm_math.h"

void draw_spectrogram(void)
{
    q31_t *buf = spdispinfo.buffer;
    arm_cfft_radix4_q31(&cfft_inst, buf);

    uint16_t mode = uistat.spdispmode;
    const spectrumdisplay_param_t *param = GET_SPDISP_PARAM(mode);
    int i = param->offset;
    int16_t stride = param->stride;
    int16_t tune_pos = param->origin;
    if (uistat.spdispmode == 0)
        tune_pos += (int)mode_freq_offset * 1024 / (48000 * stride);
    uint16_t(*block)[32] = (uint16_t(*)[32])spi_buffer;
    int sx, x, y;
    for (sx = 0; sx < 320; sx += 32)
    {
        for (x = 0; x < 32; x++)
        {
            uint16_t bg = 0;
            if (sx + x == tune_pos)
                bg = RGB565(128, 255, 128);
            int i0 = i;
            int64_t acc = 0;
            for (; i < i0 + stride; i++)
            {
                q31_t ii = buf[(i & 1023) * 2];
                q31_t qq = buf[(i & 1023) * 2 + 1];
                acc += (int64_t)ii * ii + (int64_t)qq * qq;
            }

            int v = (log2_i64(acc) - (36 << 8)) / 77; // 1dB/pixel
            if (v > 64)
                v = 64;
            if (v < 0)
                v = 0;
            for (y = 0; y < v; y++)
                block[63 - y][x] = 0xffff;
            for (; y < 64; y++)
            {
                block[63 - y][x] = bg;
                if (bg == 0 && y % 10 == 0)
                    // draw 10dB/ scale on background. 10dB/10pixel
                    block[63 - y][x] = RGB565(15, 15, 15);
            }
        }
        ili9341_draw_bitmap(sx, 72, 32, 64, (uint16_t *)block);
    }
}
