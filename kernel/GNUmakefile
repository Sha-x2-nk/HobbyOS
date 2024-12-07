# Kernel executable name
KERNEL_NAME ?= kernel

# Defining compilers and linkers
K_CXX ?= x86_64-elf-g++
K_CC ?= x86_64-elf-gcc
K_LD ?= x86_64-elf-ld

# Settings up sysroot directories
DEST_DIR ?=
PREFIX ?= /usr/local
INCLUDE_DIR ?= $(PREFIX)/include
LIB_DIR ?= $(PREFIX)/lib

# Compiler flags
SHARED_FLAGS ?= -O2 -g
SHARED_FLAGS += -Wall -Wextra -ffreestanding -fno-stack-protector \
								-fno-stack-check -fno-lto -fno-PIC -m64 -march=x86-64 \
								-mno-80387 -mno-mmx -mno-sse -mno-sse2 -mno-red-zone \
								-mcmodel=kernel
K_CPPFLAGS 	?=
K_CPPFLAGS 	+= -Iinclude -MMD -MP -D__is_kernel
K_CFLAGS 		?=
K_CLAGS 		+= -std=gnu11
K_CXXFLAGS 	?=
K_CXXFLAGS  += -std=gnu++20 -fno-rtti -fno-exceptions $(SHARED_FLAGS)
K_NASMFLAGS ?= -F dwarf -g
K_NASMFLAGS += -Wall -felf64

# Linker flags
K_LDFLAGS		 ?=
K_LDFLAGS		 += -melf_x86_64 -static -zmax-page-size=0x1000
K_LDFLAGSGCC ?=
K_LDFLAGSGCC += -Wl,-melf_x86_64,-static,-zmax-page-size=0x1000

# Libraries
K_LIBS ?=
K_LIBS += -nostdlib -lk -lk++

# CPPLINT
CPPLINT ?= $(shell which cpplint)
REPO_DIR = $(shell pwd)

# Files
CXX_FILES  = $(shell find -L * -type f -name '*.cpp')
HPP_FILES  = $(shell find -L * -type f -name '*.hpp')
NASM_FILES = $(shell find -L * -type f -name '*.asm')
OBJS = $(addprefix obj/,$(CXX_FILES:.cpp=.cpp.o) $(NASM_FILES:.asm=.asm.o))

# Header dependencies
HEADER_DEPS = $(addprefix obj/,$(CXX_FILES:.cpp=.cpp.d))
-include $(HEADER_DEPS)

.PHONY: all
all: bin/$(KERNEL_NAME)

include/limine/limine.h:
	mkdir -p "$$(dirname $@)"
	curl -Lo $@ https://github.com/limine-bootloader/limine/raw/trunk/limine.h

# Link kernel executable using g++
bin/$(KERNEL_NAME): linker.ld $(OBJS)
	mkdir -p "$$(dirname $@)"
	$(K_CXX) $(OBJS) $(K_CXXFLAGS) $(K_LIBS) -o $@ -Tlinker.ld $(K_LDFLAGSGCC) 

# Compilation rules for *.cpp files
obj/%.cpp.o: %.cpp include/limine/limine.h
	mkdir -p "$$(dirname $@)"
	$(K_CXX) $(K_CXXFLAGS) $(K_CPPFLAGS) -c $< -o $@

# Compilation rules for *.asm files
obj/%.asm.o: %.asm
	mkdir -p "$$(dirname $@)"
	nasm $(K_NASMFLAGS) $< -o $@

.PHONY: cpplint
cpplint:
	$(CPPLINT) --quiet --repository=$(REPO_DIR)/include $(CXX_FILES) $(HPP_FILES)

# Installation targets
.PHONY: install uninstall
install: all
	mkdir -p $(DEST_DIR)$(BOOT_DIR)
	cp bin/$(KERNEL_NAME) $(DEST_DIR)$(BOOT_DIR)
uninstall:
	rm -rf $(DEST_DIR)$(INCLUDE_DIR)
	rm -rf $(DEST_DIR)$(BOOT_DIR)

.PHONY: clean distclean
clean:
	rm -rf bin obj $(HEADER_DEPS)
distclean: clean
	rm -rf include/limine/limine.h
