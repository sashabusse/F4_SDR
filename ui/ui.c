#include "ui.h"
#include "chprintf.h"
#include "usbcfg.h"

void ui_init(ui_state *p_ui_state, ili9341 *p_ili9341)
{
    ui_hw_init();
    ui_input_init(&(p_ui_state->inp_state));

    ui_draw_init(&(p_ui_state->draw_cfg), p_ili9341);
    (p_ui_state->draw_cfg).spectrogram_cfg.vline_x = 0;

    ui_draw_spd_tick(&(p_ui_state->draw_cfg));
    (p_ui_state->inp_state).freq = 7925400;
    ui_draw_freq(&(p_ui_state->draw_cfg), (p_ui_state->inp_state).freq, (p_ui_state->inp_state).focus == FREQ, (p_ui_state->inp_state).freq_digit);
}

void ui_update(ui_state *p_ui_state, int32_t *signal_spectrum)
{
    chprintf((BaseSequentialStream *)&SDU1, "focus %d\r\n", (p_ui_state->inp_state).focus);
    chprintf((BaseSequentialStream *)&SDU1, "freq %d\r\n", (p_ui_state->inp_state).freq_digit);
    ui_input_update(&(p_ui_state->inp_state));
    p_ui_state->draw_cfg.spectrogram_cfg.vline_x = p_ui_state->inp_state.spd_vline;

    ui_draw_freq(&(p_ui_state->draw_cfg), p_ui_state->inp_state.freq, (p_ui_state->inp_state).focus == FREQ, (p_ui_state->inp_state).freq_digit);
    //ui_draw_freq(&(p_ui_state->draw_cfg), p_ui_state->inp_state.freq, true, 2);
    ui_draw_spd_ci32(&(p_ui_state->draw_cfg), signal_spectrum, (p_ui_state->inp_state).focus == SPDISP);
    //ui_draw_spd_ci32(&(p_ui_state->draw_cfg), signal_spectrum, true);
    ui_draw_waterfall(&(p_ui_state->draw_cfg), signal_spectrum);
}