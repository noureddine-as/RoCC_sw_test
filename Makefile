#******************************************************************************
#    Noureddine Ait Said
#    nouredddine.aitsaid0@gmail.com
#------------------------------------------------------------------------------
SRC_DIR = ./src/
BUILD_DIR = .

SOURCES = $(SRC_DIR)entry.S \
			$(SRC_DIR)main.c \
			$(SRC_DIR)syscalls.c

INCLUDES = -I./include

#include sources.mk
##################################################################
PROJi  = proj1
TARGET = $(BUILD_DIR)/$(PROJi)

LINKER = test.ld
LOG_FILE = $(PROJi)_log.txt

ISA ?= rv64imafd
ABI ?= lp64
N_PROC ?= 1
SPIKE_RBB_PORT = 9824
#SPIKE_SIMULATION ?= -DSPIKE_SIMULATION
#ENABLE_DEBUG = 1

ifndef RISCV
$(error "[ ERROR ] - RISCV variable not set!")
endif


CC = $(RISCV)/bin/riscv64-unknown-elf-gcc
LD = $(RISCV)/bin/riscv64-unknown-elf-ld
DUMPER = $(RISCV)/bin/riscv64-unknown-elf-objdump
SIZE = $(RISCV)/bin/riscv64-unknown-elf-size
SPIKE = $(RISCV)/bin/spike

ifdef ENABLE_DEBUG
CFLAGS = -g -Og -ggdb  
else
CFLAGS = -O3
endif

CFLAGS +=  -march=$(ISA) -mabi=$(ABI) -mcmodel=medany -ffreestanding -static -nostdlib -nostartfiles $(INCLUDES) 
LDFLAGS = -T $(LINKER)

OBJS = $(SOURCES:.c=.o)
DEPS = $(SOURCES:.c=.d)

%.i : %.c
	#------>>  Preprocessing
	$(CC) -E $(CFLAGS) $(SPIKE_SIMULATION) $< -o $@

%.S : %.c
	#------>>  Generating Assembly files
	$(CC) -S $(CFLAGS) $(SPIKE_SIMULATION) $< -o $@

%.o : %.S %.c
	#------>>  Generating object file
	$(CC) -c $(CFLAGS) $(SPIKE_SIMULATION) $< -o $@
	
%.dump : %.out
	$(DUMPER) -S -D $<

.PHONY: all
all: $(TARGET).out

.PHONY: compile-all
compile-all: $(OBJS)

.PHONY: build
build: all

$(TARGET).out: compile-all
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(SPIKE_SIMULATION) -o $@
	$(SIZE) $@

.PHONY: sim
sim:
	@echo "-------------  Starting Spike ISS Simulation  -------------"
	$(SPIKE) -p$(N_PROC) --isa=$(ISA) $(TARGET).out 
	
.PHONY: interactive-debug
interactive-debug:
	@echo "-------------------  Starting Interactive Debugging  -------------------"
	$(SPIKE) -d -p$(N_PROC) --isa=$(ISA) $(TARGET).out

.PHONY: gdb-debug
gdb-debug:
	@echo "-------------------  Starting GDB Debugging  -------------------"
	$(SPIKE) --rbb-port=$(SPIKE_RBB_PORT) -p$(N_PROC) --isa=$(ISA) $(TARGET).out

.PHONY: log
log:
	@echo "-------------------  Starting Logging Debug Information  -------------------"
	@echo ">> " $(LOG_FILE)
	@$(SPIKE) -p$(N_PROC) --isa=$(ISA) $(TARGET).out 2> $(LOG_FILE)


.PHONY: sim-cache
sim-cache: $(TARGET).out
#  --hartids=<a,b,...>   Explicitly specify hartids, default is 0,1,...
#  --ic=<S>:<W>:<B>      Instantiate a cache model with S sets,
#  --dc=<S>:<W>:<B>        W ways, and B-byte blocks (with S and
#  --l2=<S>:<W>:<B>        B both powers of 2).
#	DEFAULT lowRISC values
#  --ic=64:4:8      Instantiate a cache model with S sets,
#  --dc=64:4:8        W ways, and B-byte blocks (with S and
#  --l2=256:8:8        B both powers of 2).
	@echo ""
	@echo "-------------  Build done, starting simulation  -------------"
	@$(SPIKE) -p$(N_PROC) --isa=$(ISA) --ic=64:4:8 --dc=64:4:8 --l2=256:8:8 $(TARGET).out

.PHONY: clean
clean:
#	rm -f $(SRC_DIR)*.i $(SRC_DIR)*.s $(SRC_DIR)*.asm $(SRC_DIR)*.o $(SRC_DIR)*.d $(SRC_DIR)*.out $(SRC_DIR)*.map $(TARGET).out
	rm -f $(SRC_DIR)*.i $(SRC_DIR)*.asm $(SRC_DIR)*.o $(SRC_DIR)*.d $(SRC_DIR)*.out $(SRC_DIR)*.map *.out
	
