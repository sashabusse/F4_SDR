/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"
#include "nanosdr.h"
#include "shell.h"
#include "usbcfg.h"
#include "chprintf.h"

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

// restored from/into flash memory
config_t config = {
    .magic = CONFIG_MAGIC,
    .dac_value = 1080,
    .agc = {
        .target_level = 6,
        .maximum_gain = 127},
    .uistat = {.mode = CHANNEL, .channel = 0, .freq = 567000, .digit = 3, .modulation = MOD_AM, .volume = 0,
               .rfgain = 40, // 0 ~ 95
                             //.agcmode = AGC_MANUAL,
               .agcmode = AGC_MID,
               .cw_tone_freq = 800},
    .channels = {/*    freq, modulation */
                 {567000, MOD_AM},
                 {747000, MOD_AM},
                 {1287000, MOD_AM},
                 {1440000, MOD_AM},
                 {7100000, MOD_LSB},
                 {14100000, MOD_USB},
                 {21100000, MOD_USB},
                 {26800200, MOD_FM_STEREO},
                 {27500200, MOD_FM_STEREO},
                 {28400200, MOD_FM_STEREO},
                 {2932000, MOD_USB},
                 {5628000, MOD_USB},
                 {6655000, MOD_USB},
                 {8951000, MOD_USB},
                 {10048000, MOD_USB},
                 {11330000, MOD_USB},
                 {13273000, MOD_USB},
                 {17904000, MOD_USB}},
    .button_polarity = 0x01,
    .freq_inverse = -1,
    .lcd_rotation = 0};

static void cmd_echo(BaseSequentialStream *chp, int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
  {
    chprintf(chp, argv[i]);
  }
  chprintf(chp, "\r\n");
}

static void cmd_do1(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  for (int i = 0; i < argc; i++)
  {
    chprintf(chp, "doing 1 ...\r\n");
  }
}

static void cmd_do2(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  for (int i = 0; i < argc; i++)
  {
    chprintf(chp, "doing 2 ...\r\n");
  }
}

#define SHELL_WA_SIZE THD_WORKING_AREA_SIZE(512)

static const ShellCommand commands[] = {
    {"echo", cmd_echo},
    {"do1", cmd_do1},
    {"do2", cmd_do2},
    {NULL, NULL}};

static const ShellConfig shell_cfg1 = {
    (BaseSequentialStream *)&SDU1,
    commands};

int main(void)
{
  halInit();
  chSysInit();

  // ili9341_init();

  // dsp_init();

  // disp_init();
  // ili9341_set_direction(config.lcd_rotation);

  SerialConfig sd_config;
  sd_config.speed = 115200;
  sd_config.cr1 = 0;
  sd_config.cr2 = USART_CR2_STOP1_BITS;
  sd_config.cr3 = 0;

  sdStart(&SD2, &sd_config);

  shellInit();

  // USB VCP DRIVER
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);

  usbDisconnectBus(serusbcfg.usbp);
  //chThdSleepMilliseconds(200);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  /*
   * Starts the LED blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  while (true)
  {
    if (SDU1.config->usbp->state == USB_ACTIVE)
    {
      thread_t *shelltp = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
                                              "shell", NORMALPRIO + 1,
                                              shellThread, (void *)&shell_cfg1);
      chprintf((BaseSequentialStream *)&SD2, "got here\r\n");
      chThdWait(shelltp); /* Waiting termination.             */
    }

    chprintf((BaseSequentialStream *)&SDU1, "in the loop USB\r\n");
    chprintf((BaseSequentialStream *)&SD2, "in the loop UART\r\n");
    chThdSleepMilliseconds(1000);
  }
}
