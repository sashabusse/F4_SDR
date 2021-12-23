#ifndef __UI_DRAW_H
#define __UI_DRAW_H

#include <stdint.h>
#include "ili9341.h"
#include "ui_color_scheme.h"

#define UI_BUFFER_SZ 4096

typedef struct ui_spectrogram_cfg
{
    uint32_t sample_freq;
    uint32_t n_fft;
    uint32_t offset;
    uint16_t stride;
    uint16_t vline_x;
    uint16_t tick_first_x;
    uint16_t tick_step_x;
    uint8_t tick_digit_cnt;
} ui_spectrogram_cfg;

typedef struct ui_draw_cfg
{
    ili9341 *ili9341_inst;
    ui_spectrogram_cfg spectrogram_cfg;
} ui_draw_cfg;

void ui_draw_init(ui_draw_cfg *ui_new_inst, ili9341 *ili9341_inst);
void ui_clear(ui_draw_cfg *ui_inst);
void ui_draw_spd_ci32(ui_draw_cfg *ui_inst, int32_t *spectrum, bool focused);
void ui_draw_waterfall(ui_draw_cfg *ui_inst, int32_t *spectrum);
void ui_draw_spd_tick(ui_draw_cfg *ui_inst);
void ui_draw_freq(ui_draw_cfg *ui_inst, uint32_t freq, bool focused, int focus_digit);

#endif