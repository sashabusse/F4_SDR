#ifndef __USB_SHELL_H
#define __USB_SHELL_H

#define SHELL_WA_SIZE THD_WORKING_AREA_SIZE(512)

void usb_shell_init(void);
void usb_shell_poll_usb(void);

#endif