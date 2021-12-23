#include "ui_hw.h"
#include "usb_shell.h"
#include "usbcfg.h"
#include "chprintf.h"

static int enc_changed = 0;
static int enc_counter = 0;

void ui_hw_init(void)
{
    enc_changed = 0;
    enc_counter = 0;

    // configure clk interrupt
    SYSCFG->EXTICR[SYSCFG_EXTICR1_EXTI1] &= SYSCFG_EXTICR1_EXTI1_PA;
    EXTI->IMR |= EXTI_IMR_MR1;
    EXTI->RTSR |= EXTI_RTSR_TR1;
    EXTI->FTSR |= EXTI_FTSR_TR1;

    //nvicDisableVector(STM32_EXTI1_NUMBER);
    nvicEnableVector(STM32_EXTI1_NUMBER, STM32_IRQ_EXTI1_PRIORITY);

    //// configure dt interrupt as A0
    //SYSCFG->EXTICR[SYSCFG_EXTICR1_EXTI0] &= SYSCFG_EXTICR1_EXTI0_PA;
    //EXTI->IMR |= EXTI_IMR_MR0;
    //EXTI->RTSR |= EXTI_RTSR_TR0;
    //EXTI->FTSR |= EXTI_FTSR_TR0;
    //
    ////nvicDisableVector(STM32_EXTI0_NUMBER);
    //nvicEnableVector(STM32_EXTI0_NUMBER, STM32_IRQ_EXTI0_PRIORITY);

    // configure dt interrupt as B2
    SYSCFG->EXTICR[SYSCFG_EXTICR1_EXTI2] &= SYSCFG_EXTICR1_EXTI2_PA;
    EXTI->IMR |= EXTI_IMR_MR2;
    EXTI->RTSR |= EXTI_RTSR_TR2;
    EXTI->FTSR |= EXTI_FTSR_TR2;

    //nvicDisableVector(STM32_EXTI0_NUMBER);
    nvicEnableVector(STM32_EXTI2_NUMBER, STM32_IRQ_EXTI2_PRIORITY);
}

#define ENC_CHAN_A 0
#define ENC_CHAN_B 1
#define UI_DEBOUNCE_DELAY_US (30 * 1000)

void ui_hw_encoder_irq_cb(int chan, uint32_t gpio_reg);
void ui_hw_encoder_irq_cb_2(int chan, uint32_t gpio_reg);
// interrupts for encoder
CH_IRQ_HANDLER(STM32_EXTI2_HANDLER)
{
    CH_IRQ_PROLOGUE();
    uint32_t clk_val = (GPIOA->IDR >> 1) & 1;
    uint32_t dt_val = (GPIOA->IDR >> 2) & 1;
    //uint32_t gpio_reg = GPIOA->IDR;
    uint32_t gpio_reg = dt_val | (clk_val << 1);
    //chSysLockFromISR();

    if (EXTI->PR & EXTI_PR_PR2)
    {
        static systime_t prev_call = 0;
        systime_t cur_call = chVTGetSystemTime();
        sysinterval_t dt = chTimeDiffX(prev_call, cur_call);
        prev_call = cur_call;
        if (dt > TIME_US2I(UI_DEBOUNCE_DELAY_US))
        {
            ui_hw_encoder_irq_cb(ENC_CHAN_B, gpio_reg);
        }
        EXTI->PR |= EXTI_PR_PR2;
    }

    //chSysUnlockFromISR();
    CH_IRQ_EPILOGUE();
}

CH_IRQ_HANDLER(STM32_EXTI1_HANDLER)
{
    CH_IRQ_PROLOGUE();
    uint32_t clk_val = (GPIOA->IDR >> 1) & 1;
    uint32_t dt_val = (GPIOB->IDR >> 2) & 1;
    //uint32_t gpio_reg = GPIOA->IDR;
    uint32_t gpio_reg = dt_val | (clk_val << 1);
    //chSysLockFromISR();

    if (EXTI->PR & EXTI_PR_PR1)
    {
        static systime_t prev_call = 0;
        systime_t cur_call = chVTGetSystemTime();
        sysinterval_t dt = chTimeDiffX(prev_call, cur_call);
        prev_call = cur_call;
        if (dt > TIME_US2I(UI_DEBOUNCE_DELAY_US))
        {
            ui_hw_encoder_irq_cb(ENC_CHAN_A, gpio_reg);
        }
        EXTI->PR |= EXTI_PR_PR1;
    }

    //chSysUnlockFromISR();
    CH_IRQ_EPILOGUE();
}

static int enc_state = 0;
int ui_hw_get_state(void) { return enc_state; }

uint32_t ev_idx = 0;
uint32_t events[1024];
uint32_t reg_log[1024];
void ui_hw_encoder_irq_cb(int chan, uint32_t gpio_reg)
{
    reg_log[ev_idx] = gpio_reg;
    uint32_t A_val = (gpio_reg >> GPIOA_ENC_CLK) & 1;
    uint32_t B_val = (gpio_reg >> GPIOA_ENC_DT) & 1;

    uint8_t event_type = 2 * chan;

    if (chan == ENC_CHAN_A)
    {
        event_type |= A_val;
    }
    else
    {
        event_type |= B_val;
    }

    events[ev_idx] = event_type;
    ev_idx = (ev_idx + 1) % 1024;

    const int trans_tbl[4][4] = {
        {0, 0, 3, 3}, // falling A
        {1, 1, 2, 2}, // rising A
        {0, 1, 1, 0}, // falling B
        {3, 2, 2, 3}  // rising B
    };

    if ((enc_state == 0 && event_type == 3))
    {
        enc_counter--;
        enc_changed = 1;
    }
    if ((enc_state == 3 && event_type == 2))
    {
        enc_counter++;
        enc_changed = 1;
    }
    enc_state = trans_tbl[event_type][enc_state];
}

void ui_hw_encoder_irq_cb_2(int chan, uint32_t gpio_reg)
{
    uint32_t A_val = (gpio_reg >> GPIOA_ENC_CLK) & 1;
    uint32_t B_val = (gpio_reg >> GPIOA_ENC_DT) & 1;

    enc_changed = 1;
    if (A_val ^ B_val)
    {
        enc_counter--;
    }
    else
    {
        enc_counter++;
    }
}

// << button interface >>
int ui_hw_read_button(void)
{
    // button pressed polarity is 0
    return palReadPad(GPIOA, 0U) ^ 1;
}

// << encoder interface >>

int ui_hw_encoder_get_changed(void)
{
    return enc_changed;
}

void ui_hw_encoder_set_changed(int val)
{
    enc_changed = val;
}

int ui_hw_encoder_get_count(void)
{
    return enc_counter;
}

void ui_hw_encoder_set_count(int val)
{
    enc_counter = val;
}

void ui_hw_encoder_reset_state(void)
{
    enc_changed = 0;
    enc_counter = 0;
}

/*
int btn_check(void)
{
    int cur_button = read_buttons();
    int changed = last_button ^ cur_button;
    int status = 0;
    uint32_t ticks = chVTGetSystemTime();
    if (changed & (1 << BIT_PUSH))
    {
        if (ticks >= last_button_down_ticks + BUTTON_DEBOUNCE_TICKS)
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
                if (ticks < last_button_down_ticks + BUTTON_DOUBLE_TICKS)
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
        if ((cur_button & (1 << BIT_PUSH)) && !button_event_inhibited && ticks >= last_button_down_ticks + BUTTON_DOWN_LONG_TICKS)
        {
            status |= EVT_BUTTON_DOWN_LONG;
            button_event_inhibited = 1;
        }
    }

    last_button = cur_button;

    return status;
}
*/