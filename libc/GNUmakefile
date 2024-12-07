# Defining compilers and linkers
K_CC ?= x86_64-elf-gcc
K_AR ?= x86_64-elf-ar

SHARED_FLAGS ?= -O2 -g
K_CFLAGS 		 ?=
K_CPPFLAGS 	 ?=

# Setting up sysroot directories
DEST_DIR 		?=
PREFIX 			?= /usr/local
INCLUDE_DIR ?= $(PREFIX)/include
LIB_DIR 		?= $(PREFIX)/lib

# Compiler flags
SHARED_FLAGS += -Wall -Wextra -ffreestanding -fno-stack-protector -fno-stack-check \
								-fno-lto -fno-PIC -m64 -march=x86-64 -mno-80387 -mno-mmx \
								-mno-sse -mno-sse2 -mno-red-zone -mcmodel=kernel
K_CFLAGS     += -std=gnu11 $(SHARED_FLAGS)
K_CPPFLAGS   += -Iinclude -MMD -MP

# Library-specific flags
LIBK_CFLAGS := $(K_CFLAGS)
LIBC_CFLAGS := $(K_CFLAGS)

LIBK_CPPFLAGS := $(K_CPPFLAGS) -D__is_kernel
LIBC_CPPFLAGS := $(K_CPPFLAGS) -D__is_libc

# Object files
FREE_OBJS   := obj/src/string.c.o
HOSTED_OBJS :=
OBJS        := $(FREE_OBJS) $(HOSTED_OBJS)
LIBK_OBJS   := $(FREE_OBJS:.c.o=.c.libk.o)

# Output Binaries
BINARIES := obj/libk.a # libc not ready yet

# CPPLINT
CPPLINT ?= $(shell which cpplint)
REPO_DIR = $(shell pwd)

# Source and header files for cpplint
C_FILES = $(shell find -L * -type f -name '*.c')
H_FILES = $(shell find -L * -type f -name '*.h')

# Header dependencies
HEADER_DEPS = $(addprefix obj/,$(C_FILES:.c=.c.d))
-include $(HEADER_DEPS)

# Default target
.PHONY: all
all: $(BINARIES)

# Building the library
obj/libk.a: $(LIBK_OBJS)
	$(K_AR) rcs $@ $(LIBK_OBJS)

obj/libc.a: $(OBJS)
	$(K_AR) rcs $@(OBJS)

# Compilation rules for *.c files
obj/%.c.o: %.c GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(K_CC) $(LIBC_CFLAGS) $(LIBC_CPPFLAGS) -c $< -o $@

obj/%.c.libk.o: %.c GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(K_CC) $(LIBK_CFLAGS) $(LIBK_CPPFLAGS) -c $< -o $@

# Running cpplint on the source and header files
.PHONY: cpplint
cpplint:
	$(CPPLINT) --quiet --repository=$(REPO_DIR)/include $(C_FILES) $(H_FILES)

# Installation targets
.PHONY: install install-headers install-libs
install: install-headers install-libs
install-headers:
	mkdir -p $(DEST_DIR)$(INCLUDE_DIR)
	cp -R --preserve=timestamps include/. $(DEST_DIR)$(INCLUDE_DIR)/.
install-libs: all
	mkdir -p $(DEST_DIR)$(LIB_DIR)
	cp $(BINARIES) $(DEST_DIR)$(LIB_DIR)

# Cleaning targets
.PHONY: clean distclean
clean:
	rm -rf $(BINARIES)
	rm -rf obj
distclean: clean

# Uninstall targets
.PHONY: uninstall
uninstall:
	rm -rf $(DEST_DIR)$(INCLUDE_DIR)
	rm -rf $(DEST_DIR)$(LIB_DIR)
