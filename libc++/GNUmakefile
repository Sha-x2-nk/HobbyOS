# Defining compilers and linkers
K_CXX ?= x86_64-elf-g++
K_LD 	?= x86_64-elf-ld
K_AR 	?= x86_64-elf-ar

# Default flags
SHARED_FLAGS ?= -O2 -g
K_CXXFLAGS 	 ?=
K_CPPFLAGS 	 ?=

DEST_DIR 		?=
PREFIX 			?= /usr/local
INCLUDE_DIR ?= $(PREFIX)/include
LIB_DIR 		?= $(PREFIX)/lib

# Compiler flags
SHARED_FLAGS += -Wall -Wextra -ffreestanding -fno-stack-protector -fno-stack-check \
								-fno-lto -fno-PIC -m64 -march=x86-64 -mno-80387 -mno-mmx \
								-mno-sse -mno-sse2 -mno-red-zone -mcmodel=kernel

K_CXXFLAGS += -std=gnu++20 $(SHARED_FLAGS)
K_CPPFLAGS += -Iinclude -MMD -MP

# Library-specific flags
LIBKXX_CXXFLAGS := $(K_CXXFLAGS)
LIBCXX_CXXFLAGS := $(K_CXXFLAGS)

LIBKXX_CPPFLAGS := $(K_CPPFLAGS) -D__is_kernel
LIBCXX_CPPFLAGS := $(K_CPPFLAGS) -D__is_libcxx

# Object files
FREE_OBJS 	:= obj/src/string.cpp.o
HOSTED_OBJS :=
OBJS := $(FREE_OBJS) $(HOSTED_OBJS)
LIBKXX_OBJS := $(FREE_OBJS:.cpp.o=.cpp.libk++.o)

# Output binaries
BINARIES := obj/libk++.a # libc++ not ready yet

# CPPLINT
CPPLINT ?= $(shell which cpplint)
REPO_DIR = $(shell pwd)

# Source and header files for cpplint
CXX_FILES = $(shell find -L * -type f -name '*.cpp')
HPP_FILES = $(shell find -L * -type f -name '*.hpp')

# Header dependencies
HEADER_DEPS = $(addprefix obj/,$(CXX_FILES:.cpp=.cpp.d))
-include $(HEADER_DEPS)

# Default target
.PHONY: all
all: $(BINARIES)

# Building the library
obj/libk++.a: $(LIBKXX_OBJS)
	$(K_AR) rcs $@ $(LIBKXX_OBJS)

obj/libc++.a: $(OBJS)
	$(K_AR) rcs $@ $(OBJS)

# Include header dependencies
-include $(HEADER_DEPS)

# Compilation rules for *.cpp files
obj/%.cpp.o: %.cpp GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(K_CXX) $(LIBCXX_CXXFLAGS)x86 $(LIBCXX_CPPFLAGS) -c $< -o $@

obj/%.cpp.libk++.o: %.cpp GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(K_CXX) $(LIBKXX_CXXFLAGS) $(LIBKXX_CPPFLAGS) -c $< -o $@

# Running cpplint on the source and header files
.PHONY: cpplint
cpplint:
	$(CPPLINT) --quiet --repository=$(REPO_DIR)/include $(CXX_FILES) $(HPP_FILES)

# Installation targets
.PHONY: install install-headers install-libs uninstall
install: install-headers install-libs
install-headers:
	mkdir -p $(DEST_DIR)$(INCLUDE_DIR)
	cp -R --preserve=timestamps include/. $(DEST_DIR)$(INCLUDE_DIR)
install-libs: all	
	mkdir -p $(DEST_DIR)$(LIB_DIR)
	cp $(BINARIES) $(DEST_DIR)$(LIB_DIR)
uninstall:
	rm -rf $(DEST_DIR)$(INCLUDE_DIR)
	rm -rf $(DEST_DIR)$(LIB_DIR)

# Cleaning targets
.PHONY: clean distclean
clean:
	rm -rf $(BINARIES)
	rm -rf obj
distclean: clean