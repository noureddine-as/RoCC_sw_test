
SOURCES = $(SRC_DIR)entry.S \
			$(SRC_DIR)main.c \
			$(SRC_DIR)syscalls.c

INCLUDES = -I./include


##################################################################
#  SPECIFIC PARAMETERS
##################################################################
PROJi  = proj1
N_PROC ?= 1
ISA ?= rv64imafd
ABI ?= lp64
SPIKE_RBB_PORT = 9824
CEMUL_RBB_PORT = 9823
#SPIKE_SIMULATION ?= -DSPIKE_SIMULATION
ENABLE_DEBUG = 0