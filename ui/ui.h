#ifndef __UI_H
#define __UI_H

#include "ui_draw.h"
#include "ui_input.h"
#include "ui_hw.h"

typedef struct ui_state
{
    ui_draw_cfg draw_cfg;
    ui_input_state inp_state;
} ui_state;

void ui_init(ui_state *p_ui_state, ili9341 *p_ili9341);
void ui_update(ui_state *p_ui_state, int32_t *signal_spectrum);

#endif