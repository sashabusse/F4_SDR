#ifndef __UI_HW_H
#define __UI_HW_H

#include "hal.h"
#include "ch.h"

void ui_hw_init(void);

// button interface
int ui_hw_read_button(void);

// encoder interface
int ui_hw_encoder_get_changed(void);
void ui_hw_encoder_set_changed(int val);
int ui_hw_encoder_get_count(void);
void ui_hw_encoder_set_count(int val);
void ui_hw_encoder_reset_state(void);

#endif
