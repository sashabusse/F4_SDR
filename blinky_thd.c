#include "blinky_thd.h"
#include "hal.h"

static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg)
{

    (void)arg;
    chRegSetThreadName("blinker");
    while (true)
    {
        palClearLine(LED_LINE);
        chThdSleepMilliseconds(500);
        palSetLine(LED_LINE);
        palSetPad(GPIOC, GPIOC_LED);
        chThdSleepMilliseconds(500);
    }
}

void blinky_thd_start(void)
{
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
}