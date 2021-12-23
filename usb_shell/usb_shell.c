#include "usb_shell.h"

#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"
#include "usbcfg.h"

static const ShellCommand commands[] = {
    {NULL, NULL}};

static const ShellConfig shell_cfg1 = {
    (BaseSequentialStream *)&SDU1,
    commands};

void usb_shell_init(void)
{
    shellInit();

    // USB VCP DRIVER
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    usbDisconnectBus(serusbcfg.usbp);
    //chThdSleepMilliseconds(200);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);
}

void usb_shell_start(void)
{
    while (!(SDU1.config->usbp->state == USB_ACTIVE))
    {
    }

    thread_t *shelltp = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
                                            "shell", NORMALPRIO + 1,
                                            shellThread, (void *)&shell_cfg1);
}