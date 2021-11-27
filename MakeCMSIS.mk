##########################
# ARM_GCC TOOLS
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
LD   = $(TRGT)gcc
CP   = $(TRGT)objcopy
AR   = $(TRGT)ar
#
##########################

# << output directories >> ----------------------------------------------------
BUILDDIR = ./build/CMSIS
OBJDIR = $(BUILDDIR)/obj
DEPDIR = $(BUILDDIR)/.dep
#------------------------------------------------------------------------------

ifeq ($(USE_OPT),)
  USE_OPT = -O0 -ggdb -fomit-frame-pointer -falign-functions=16
endif

# << input files and directories >> -------------------------------------------
CMSIS_DIR = CMSIS
DSPLIB_DIR = ${CMSIS_DIR}/DSP

# DSP lib
DSPLIB_INC = \
	${DSPLIB_DIR}/Include

DSPLIB_SRC = \
	${DSPLIB_DIR}/Source/FilteringFunctions/arm_biquad_cascade_df1_q15.c \
    ${DSPLIB_DIR}/Source/TransformFunctions/arm_cfft_radix4_init_q31.c \
    ${DSPLIB_DIR}/Source/TransformFunctions/arm_cfft_radix4_q31.c \
    ${DSPLIB_DIR}/Source/TransformFunctions/arm_bitreversal.c \
    ${DSPLIB_DIR}/Source/CommonTables/arm_common_tables.c

SRC = $(DSPLIB_SRC)
INCDIR = $(DSPLIB_INC)
#------------------------------------------------------------------------------

# << file lists >> ------------------------------------------------------------
OBJS    := $(addprefix $(OBJDIR)/, $(notdir $(TCSRC:.c=.o)))
IINCDIR   := $(patsubst %,-I%,$(INCDIR))


#------------------------------------------------------------------------------

# << build rules >> -----------------------------------------------------------
DEFS = 
#------------------------------------------------------------------------------