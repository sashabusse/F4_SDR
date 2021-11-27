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
#include "ili9341.h"
#include "usb_shell.h"
#include "ili9341_gfx.h"

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

int main(void)
{
  halInit();
  chSysInit();

  usb_shell_init();

  // << init display >> ------------------------------------------------------------
  ili9341 ili9341_driver;
  ili9341_driver.hw.pSPID = &SPID1;
  ili9341_driver.hw.nss_port = GPIOA;
  ili9341_driver.hw.nss_pin = GPIOA_SPI1_NSS;
  ili9341_driver.hw.rst_port = GPIOB;
  ili9341_driver.hw.rst_pin = GPIOB_ILI9341_RESET;
  ili9341_driver.hw.dc_port = GPIOB;
  ili9341_driver.hw.dc_pin = GPIOB_ILI9341_DC;

  ili9341_init(&ili9341_driver);

  ili9341_draw_font_string(&ili9341_driver, "012345", &NF20x24, 0, 0, 0xFFFF, 0x0000);
  // -------------------------------------------------------------------------------

  // Starts the LED blinker thread.
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  while (true)
  {
    usb_shell_poll_usb();
    chThdSleepMilliseconds(100);
  }
}
