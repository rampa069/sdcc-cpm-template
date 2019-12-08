# Prefixes
COMPILER_PREFIX = /usr/local/
#COMPILER_PREFIX = $(SDCC_PREFIX)
ARCH=z180
#ARCH=z80
COMPILER_LIBS = $(COMPILER_PREFIX)/share/sdcc/lib/$(ARCH)/


# Options
QUIET = @

# SDCC commands
CCC = $(COMPILER_PREFIX)/bin/sdcc
CAS = $(COMPILER_PREFIX)/bin/sdasz80
CLD = $(COMPILER_PREFIX)/bin/sdldz80

# Local CC
CC = gcc

# Misc local commands
ECHO = echo
COPY = cp
MOVE = mv
SED = sed

# Project directories
SRC_DIR = src/
CPM_SRC_DIR = $(SRC_DIR)/cpm
SYSLIB_SRC_DIR = $(SRC_DIR)/syslib
HWLIB_SRC_DIR = $(SRC_DIR)/hw
BIN_DIR = bin/

LSRC_DIR = lsrc/
LBIN_DIR = lbin/

ESRC_DIR = esrc/

INCLUDE_DIR = -I$(SRC_DIR)/include -I$(SRC_DIR)

# Compilation / Assembly / Linking flags
CCC_FLAGS = -c -m$(ARCH) -D__SDCC__=1 $(INCLUDE_DIR)
CAS_FLAGS = -plosff 
CLD_FLAGS = 

