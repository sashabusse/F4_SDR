#ifndef __MATH_UTIL_H
#define __MATH_UTIL_H

#define __FPU_PRESENT 1U
#include "CMSIS/DSP/Include/arm_math.h"
#include "math.h"

/**
 * @brief fixed point log2 (8 binary digits after point)
 * 
 * @param x 
 * @return uint16_t 
 */
uint16_t log2_i64(uint64_t x);

#endif
