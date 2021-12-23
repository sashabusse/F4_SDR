#include "ui_draw.h"
#include "ili9341_gfx.h"
#include "math_util.h"
#include <stdlib.h>

/**
 * @brief buffer to hold partial color maps
 *          probably need to find an better desigion than have buffer for ili9341 driver and also buffer here
 *          mb dynamic allocation
 */
uint16_t ui_buffer[UI_BUFFER_SZ];

void ui_draw_init(ui_draw_cfg *ui_new_inst, ili9341 *ili9341_inst)
{
    ui_new_inst->ili9341_inst = ili9341_inst;

    // mb later should be adde options to pass as arg or load from memory previous state
    ui_new_inst->spectrogram_cfg.sample_freq = 48e3;
    ui_new_inst->spectrogram_cfg.n_fft = 1024;
    ui_new_inst->spectrogram_cfg.offset = 0;
    ui_new_inst->spectrogram_cfg.stride = 1;
    ui_new_inst->spectrogram_cfg.vline_x = 0;

    ui_new_inst->spectrogram_cfg.tick_first_x = 0;
    ui_new_inst->spectrogram_cfg.tick_step_x = 35;
    ui_new_inst->spectrogram_cfg.tick_digit_cnt = 3;

    // draw all the ui elements
    ui_clear(ui_new_inst);
}

/**
 * @brief clear of the screen
 * 
 * @param ui_inst 
 */
void ui_clear(ui_draw_cfg *ui_inst)
{
    ili9341_fill_rect(ui_inst->ili9341_inst, 0, 0, 320, 240, UI_BG_NORMAL);
}

/**
 * @brief draws spectrogram
 * 
 * @param pspec_cfg 
 * @param spectrum spectrum data in complex int32_t format
 * @param x0 x origin coordinate
 * @param y0 y origin coordinate
 */
void ui_draw_spd_ci32(ui_draw_cfg *ui_inst, int32_t *spectrum, bool focused)
{
    uint16_t bg_global = UI_SPD_BG;
    uint16_t fg_global = UI_SPD_FG;
    if (focused)
    {
        bg_global = UI_BG_ACTIVE;
        fg_global = UI_FG_ACTIVE;
    }

    int i = ui_inst->spectrogram_cfg.offset;
    int16_t stride = ui_inst->spectrogram_cfg.stride;
    int16_t vline_x = ui_inst->spectrogram_cfg.vline_x;
    uint32_t n_fft = ui_inst->spectrogram_cfg.n_fft;

    uint16_t(*block)[32] = (uint16_t(*)[32])ui_buffer;
    for (uint16_t sx = 0; sx < 320; sx += 32)
    {
        for (uint8_t x = 0; x < 32; x++)
        {
            uint16_t bg = bg_global;
            if (sx + x == vline_x)
                bg = UI_SPD_VLINE;

            int i0 = i;
            int64_t acc = 0;
            for (; i < i0 + stride; i++)
            {
                int32_t ii = spectrum[(i % n_fft) * 2];
                int32_t qq = spectrum[(i % n_fft) * 2 + 1];
                acc += (int64_t)ii * ii + (int64_t)qq * qq;
            }

            int v = (log2_i64(acc) - (36 << 8)) / 77; // 1dB/pixel
            if (v > 64)
                v = 64;
            if (v < 0)
                v = 0;
            uint8_t y;
            for (y = 0; y < v; y++)
                block[63 - y][x] = fg_global;
            for (; y < 64; y++)
            {
                block[63 - y][x] = bg;
                if (bg == 0 && y % 10 == 0)
                    // draw 10dB/ scale on background. 10dB/10pixel
                    block[63 - y][x] = UI_SPD_LVL_LINES;
            }
        }
        ili9341_draw_map(ui_inst->ili9341_inst, sx, 72, 32, 64, (uint16_t *)block);
    }
}

void ui_draw_spd_tick(ui_draw_cfg *ui_inst)
{
    uint16_t bg = UI_SPD_BG;
    uint16_t fg = UI_SPD_FG;

    // clear background
    ili9341_fill_rect(ui_inst->ili9341_inst, 0, 136, 320, 16, bg);

    uint32_t offset = ui_inst->spectrogram_cfg.offset;
    uint16_t stride = ui_inst->spectrogram_cfg.stride;
    uint32_t fs = ui_inst->spectrogram_cfg.sample_freq;
    uint32_t n_fft = ui_inst->spectrogram_cfg.n_fft;

    // chosing unit name
    uint32_t max_freq = (((uint64_t)(offset + 320 * stride)) * fs) / n_fft;
    char *unit_name = "Hz";
    float32_t fs_div = fs;
    if (max_freq >= 1000)
    {
        unit_name = "kHz";
        fs_div = fs / 1000;
    }
    if (max_freq >= 1000 * 1000)
    {
        unit_name = "MHz";
        fs_div = fs / (1000 * 1000);
    }

    bool first = true;
    char str[10];
    int tick_x = ui_inst->spectrogram_cfg.tick_first_x;
    for (; tick_x < 320; tick_x += ui_inst->spectrogram_cfg.tick_step_x)
    {
        float32_t freq = ((offset + tick_x * stride) * fs_div) / n_fft;
        bool zero = freq == 0;
        // whole part
        itoa(freq, str, 10);
        // resigne part
        float32_t res_part = freq - (uint16_t)freq;
        int wp_digits = 0;
        while (freq > 1)
        {
            freq /= 10;
            wp_digits++;
        }
        int rp_digits = ui_inst->spectrogram_cfg.tick_digit_cnt - wp_digits;
        if (rp_digits > 0 && !zero)
        {
            for (uint8_t iter = 0; iter < rp_digits; iter++)
                res_part *= 10;

            strcat(str, ".");
            itoa(res_part, str + wp_digits + 1, 10);
        }

        // add unit name to te first label
        if (first)
        {
            strcat(str, unit_name);
            first = false;
        }
        int xx = tick_x - strlen(str) * 5 / 2;
        if (xx < 0)
            xx = 0;

        ili9341_draw_string_5x7(ui_inst->ili9341_inst, str, xx, 142, fg, bg);
        ili9341_fill_rect(ui_inst->ili9341_inst, tick_x, 136, 2, 5, fg);
    }
}

static const struct
{
    uint8_t r, g, b;
} colormap[] = {
    {0, 0, 0},
    {0, 0, 255},
    {0, 255, 0},
    {255, 0, 0},
    {255, 255, 255}};

static uint16_t pick_color(int mag) /* mag: 0 - 63 */
{
    int idx = (mag >> 4) & 0x3;
    int prop = mag & 0x0f;
    int nprop = 0x10 - prop;
    int r = colormap[idx].r * nprop + colormap[idx + 1].r * prop;
    int g = colormap[idx].g * nprop + colormap[idx + 1].g * prop;
    int b = colormap[idx].b * nprop + colormap[idx + 1].b * prop;
    return ILI9341_RGB565(r >> 4, g >> 4, b >> 4);
}

static int16_t vsa = 152;
void ui_draw_waterfall(ui_draw_cfg *ui_inst, int32_t *spectrum)
{
    int x;

    uint16_t *block = ui_buffer;
    int i = ui_inst->spectrogram_cfg.offset;
    uint16_t stride = ui_inst->spectrogram_cfg.stride;
    uint32_t n_fft = ui_inst->spectrogram_cfg.n_fft;
    uint16_t bg = UI_SPD_BG;
    uint16_t c;

    for (x = 0; x < 320; x++)
    {
        int64_t acc = 0;
        int i0 = i;
        for (; i < i0 + stride; i++)
        {
            q31_t ii = spectrum[(i % n_fft) * 2];
            q31_t qq = spectrum[(i % n_fft) * 2 + 1];
            acc += (int64_t)ii * ii + (int64_t)qq * qq;
        }
        int v = (log2_i64(acc) - (34 << 8)) >> 6;
        if (v < 0)
            v = 0;
        if (v > 63)
            v = 63;
        c = pick_color(v);
        if (c == 0)
            c = bg;
        *block++ = c;
    }

    vsa++;
    if (vsa >= 240)
        vsa = 152;
#if 0
	// Vertical Scroll Address
	uint8_t vscrsadd[2] = { vsa>>8, vsa };
	send_command(0x37, 2, vscrsadd);
#endif
    ili9341_draw_map(ui_inst->ili9341_inst, 0, vsa, 320, 1, ui_buffer);
}

static void itoa_padded(int value, char *buf, int dig, int pad)
{
    char neg = 0;
    if (dig == 0)
    {
        itoa(value, buf, 10);
        return;
    }
    if (value < 0)
    {
        neg = '-';
        value = -value;
    }

    buf[dig--] = '\0';
    do
    {
        buf[dig--] = (value % 10) + '0';
        value /= 10;
    } while (value > 0 && dig >= 0);
    if (neg && dig >= 0)
    {
        buf[dig--] = neg;
    }
    while (dig >= 0)
    {
        buf[dig--] = pad;
    }
}

void ui_draw_freq(ui_draw_cfg *ui_inst, uint32_t freq, bool focused, int focus_digit)
{
    char str[10];
    itoa_padded(freq, str, 8, ' ');

    uint16_t x = 0;
    const uint16_t x_sep_interval[] = {0, 16, 0, 0, 16, 0, 0, 0};

    for (int i = 0; i < 8; i++)
    {
        uint16_t bg = UI_BG_NORMAL;
        uint16_t fg = UI_FG_NORMAL;
        if (focused && (focus_digit == 7 - i))
        {
            bg = UI_BG_ACTIVE;
            fg = UI_FG_ACTIVE;
        }
        int8_t c = str[i] - '0';
        if (c >= 0 && c <= 9)
            ili9341_draw_font(ui_inst->ili9341_inst, c, &NF32x48, x, 0, fg, bg);
        else
            ili9341_fill_rect(ui_inst->ili9341_inst, x, 0, 32, 48, bg);
        x += 32;

        // fill gaps
        if (x_sep_interval[i] > 0)
        {
            ili9341_fill_rect(ui_inst->ili9341_inst, x, 0, x_sep_interval[i], 48, bg);
            x += x_sep_interval[i];
        }
    }

    // draw Hz symbol
    ili9341_draw_font(ui_inst->ili9341_inst, 10, &NF32x48, x, 0, UI_FG_NORMAL, UI_BG_NORMAL);
}
