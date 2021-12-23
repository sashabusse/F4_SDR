#include "ui.h"
#include "ui_input.h"
#include "ui_draw.h"
#include "ui_hw.h"

void ui_input_init(ui_input_state *p_ui_state)
{
    p_ui_state->focus = FREQ;
    p_ui_state->freq_digit = 0;
    p_ui_state->spd_vline = 0;
}

#define BIT_PUSH 0 //??? what for

#define NO_EVENT 0
#define EVT_BUTTON_SINGLE_CLICK 0x01
#define EVT_BUTTON_DOUBLE_CLICK 0x02
#define EVT_BUTTON_DOWN_LONG 0x04
#define EVT_UP 0x10
#define EVT_DOWN 0x20
#define EVT_PUSH_UP 0x30
#define EVT_PUSH_DOWN 0x40

#define BUTTON_DOWN_LONG_MS 1000
#define BUTTON_DOUBLE_MS 400
#define BUTTON_DEBOUNCE_US 500
#define BUTTON_NO_ACTION 0

static uint16_t button_event_inhibited = 0;
int btn_check(void)
{
    static uint32_t last_button_down_ticks;
    static int last_button = 0;

    int cur_button = ui_hw_read_button();
    int changed = last_button ^ cur_button;
    int status = 0;
    uint32_t ticks = chVTGetSystemTime();
    if (changed & (1 << BIT_PUSH))
    {
        if (ticks >= last_button_down_ticks + TIME_US2I(BUTTON_DEBOUNCE_US))
        {
            if (!(cur_button & (1 << BIT_PUSH)))
            {
                // button released
                if (button_event_inhibited)
                {
                    button_event_inhibited = 0;
                }
                else
                {
                    status |= EVT_BUTTON_SINGLE_CLICK;
                }
            }
            else
            {
                // button pushed
                if (ticks < last_button_down_ticks + TIME_MS2I(BUTTON_DOUBLE_MS))
                {
                    status |= EVT_BUTTON_DOUBLE_CLICK;
                }
                else
                {
                    last_button_down_ticks = ticks;
                }
            }
        }
    }
    else
    {
        // button unchanged
        if ((cur_button & (1 << BIT_PUSH)) && !button_event_inhibited && ticks >= last_button_down_ticks + TIME_MS2I(BUTTON_DOWN_LONG_MS))
        {
            status |= EVT_BUTTON_DOWN_LONG;
            button_event_inhibited = 1;
        }
    }

    last_button = cur_button;

    return status;
}

int fetch_encoder_tick(void)
{
    int enc_val = ui_hw_encoder_get_count();
    if (enc_val != 0)
    {
        ui_hw_encoder_set_count(0);
    }
    return enc_val;
}

void ui_input_update(ui_input_state *p_ui_state)
{
    int status = btn_check();
    int tick = fetch_encoder_tick();
    int n;
    if (status & EVT_BUTTON_SINGLE_CLICK)
    {
        p_ui_state->focus++;
        p_ui_state->focus %= MODE_MAX;
        //disp_update();
    }
    else if (status & EVT_BUTTON_DOWN_LONG)
    {
        //save_config_current_channel();
    }

    if (tick != 0)
    {
        if (p_ui_state->focus == SPDISP)
        {
            p_ui_state->spd_vline = (p_ui_state->spd_vline + 50 * tick) % 1024;
        }

        if (ui_hw_read_button() != 0)
        {
            // button pressed

            if (p_ui_state->focus == FREQ)
            {
                if (tick < 0)
                {
                    if (p_ui_state->freq_digit < 7)
                        p_ui_state->freq_digit++;
                    else
                        p_ui_state->focus--;
                }
                if (tick > 0)
                {
                    if (p_ui_state->freq_digit > 0)
                        p_ui_state->freq_digit--;
                    else
                        p_ui_state->focus++;
                }
            }
            else
            {
                if (tick < 0)
                {
                    p_ui_state->focus--;

                    //if (uistat.mode == IQBAL || uistat.mode == RFGAIN)
                    //    disp_clear_aux();
                }
                if (tick > 0)
                {
                    p_ui_state->focus++;

                    //if (uistat.mode == SPDISP)
                    //    disp_clear_aux();
                }
                p_ui_state->focus = p_ui_state->focus % MODE_MAX;
            }
            //disp_update();
            //button_event_inhibited = 1;
        }
        else
        {
            if (p_ui_state->focus == FREQ)
            {
                int32_t step = 1;
                for (n = p_ui_state->freq_digit; n > 0; n--)
                    step *= 10;
                int32_t freq = p_ui_state->freq + step * tick;
                if (freq > 0)
                    p_ui_state->freq = freq;
                //update_frequency();
            }
        }
    }
}