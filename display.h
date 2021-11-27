#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <stdint.h>

typedef struct
{
    uint32_t sample_freq;
    int16_t offset;
    int16_t stride;
    int16_t overgain;

    int16_t origin;
    int16_t tickstep;
    int16_t tickbase;
    int16_t tickunit;
    const char *unitname;
} spectrumdisplay_param_t;

#endif