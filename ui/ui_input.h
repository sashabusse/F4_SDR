#ifndef __UI_INPUT_H
#define __UI_INPUT_H

#include <stdio.h>

typedef struct
{
    enum
    {
        FREQ,
        SPDISP,
        MODE_MAX
    } focus;
    int8_t freq_digit;
    uint16_t spd_vline;
    uint32_t freq;
} ui_input_state;

void ui_input_init(ui_input_state *p_ui_state);
void ui_input_update(ui_input_state *p_ui_state);

#endif