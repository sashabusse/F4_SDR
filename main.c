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
#include "chprintf.h"

#include "blinky_thd.h"

#include "ili9341.h"
#include "ili9341_gfx.h"
#include "ui_draw.h"
#include "ui_hw.h"
#include "ui.h"

#include "usb_shell.h"
#include "usbcfg.h"

#include "math_util.h"

#include <stdlib.h>

int32_t signal[2048];
int32_t signal_noise[2048];

extern uint32_t ev_idx;
extern uint32_t events[1024];
extern uint32_t reg_log[1024];

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
    usb_shell_start();
    // -------------------------------------------------------------------------------

    ui_state ui_state_inst;
    ui_init(&ui_state_inst, &ili9341_driver);

    // << generate some data >> ------------------------------------------------------

    arm_cfft_radix4_instance_q31 cfft_inst;
    arm_cfft_radix4_init_q31(&cfft_inst, 1024, 0, 1);
    for (uint16_t i = 0; i < 1024; i++)
    {
        int32_t val = 128 * 1024 * 1024;
        if ((i / 5) % 2 == 1)
        {
            val = -val;
        }
        signal[i * 2] = val;
        signal[i * 2 + 1] = 0;
    }
    // -------------------------------------------------------------------------------

    // start all the threads
    blinky_thd_start();

    uint32_t m_ev_idx = 0;
    int random_max = 30 * 512 * 1024;
    while (true)
    {
        for (int i = 0; i < 2048; i++)
        {
            signal_noise[i] = signal[i] + (rand() % (2 * random_max)) - random_max;
        }
        arm_cfft_radix4_q31(&cfft_inst, signal_noise);
        ui_update(&ui_state_inst, signal_noise);
        //chThdSleepMilliseconds(50);

        /*
        while (m_ev_idx != ev_idx)
        {
            chprintf((BaseSequentialStream *)&SDU1, "ev=%d\r\n", events[m_ev_idx]);
            m_ev_idx = (m_ev_idx + 1) % 1024;
        }
        */

        if (ui_hw_encoder_get_changed() != 0)
        {
            chprintf((BaseSequentialStream *)&SDU1, "%d\r\n", ui_hw_encoder_get_count());
            ui_hw_encoder_set_changed(0);
        }
    }
}
