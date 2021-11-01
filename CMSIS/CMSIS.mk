CMSIS_DIR = CMSIS

# DSP lib
DSPLIB_DIR = ${CMSIS_DIR}/DSP

DSPLIB_INC = \
	${DSPLIB_DIR}/Include

DSPLIB_SRC = \
	${DSPLIB_DIR}/Source/FilteringFunctions/arm_biquad_cascade_df1_q15.c \
    ${DSPLIB_DIR}/Source/TransformFunctions/arm_cfft_radix4_init_q31.c \
    ${DSPLIB_DIR}/Source/TransformFunctions/arm_cfft_radix4_q31.c \
    ${DSPLIB_DIR}/Source/TransformFunctions/arm_bitreversal.c \
    ${DSPLIB_DIR}/Source/CommonTables/arm_common_tables.c

# Shared variables
ALLCSRC += $(DSPLIB_SRC)
ALLINC  += $(DSPLIB_INC)