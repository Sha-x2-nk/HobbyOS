# Defining compilers and linkers
KCXX				?=	x86_64-elf-g++
KLD					?=	x86_64-elf-ld

KAR					?=	x86_64-elf-ar

SHARED_FLAGS		?= 	-O2 -g
KCXX_FLAGS			?=
KCPP_FLAGS			?=

DEST_DIR			?=
PREFIX				?=	/usr/local
INCLUDE_DIR			?=	$(PREFIX)/include
LIB_DIR				?=	$(PREFIX)/lib

SHARED_FLAGS		+=							\
						-Wall					\
						-Wextra					\
						-ffreestanding			\
						-fno-stack-protector	\
						-fno-stack-check		\
						-fno-lto				\
						-fno-PIC				\
						-m64					\
						-march=x86-64			\
						-mno-80387				\
						-mno-mmx				\
						-mno-sse				\
						-mno-sse2				\
						-mno-red-zone			\
						-mcmodel=kernel			\

KC_FLAGS			+=							\
						-std=gnu++20			\
						$(SHARED_FLAGS)			\

KCPP_FLAGS			+=							\
						-Iinclude				\
						-MMD					\
						-MP						\

LIBKXX_CXX_FLAGS	:=							\
						$(KC_FLAGS)				\

LIBCXX_CXX_FLAGS	:=							\
						$(KC_FLAGS)				\

LIBKXX_CPP_FLAGS	:=							\
						$(KCPP_FLAGS)			\
						-D__is_kernel			\

LIBC_CPP_FLAGS		:= 							\
						$(KCPP_FLAGS)			\
						-D__is_libcxx			\

FREE_OBJS			=							\
						obj/string/memcmp.cpp.o	\
						obj/string/memcpy.cpp.o	\
						obj/string/memmove.cpp.o\
						obj/string/memset.cpp.o	\
						obj/string/strlen.cpp.o	\

HOSTED_OBJS			=

OBJS				=							\
						$(FREE_OBJS)			\
						$(HOSTED_OBJS)			\
					
LIBKXX_OBJS			=	$(FREE_OBJS:.cpp.o=.cpp.libk++.o)	\

BINARIES			=	obj/libk++.a	# libc++ not ready yet

# Searching files 
CXX_FILES			=	$(shell find -L * -type f -name '*.cpp')
HEADER_DEPS			=	$(addprefix obj/,$(C_FILES:.cpp=.cpp.d))

.PHONY: all
all: $(BINARIES)

obj/libk++.a: $(LIBKXX_OBJS)
	$(KAR) rcs $@ $(LIBKXX_OBJS)

obj/libc++.a: $(OBJS)
	$(KAR) rcs $@ $(OBJS)

# Include header dependencies.
-include $(HEADER_DEPS)

# Compilation rules for *.c files.
obj/%.cpp.o: %.cpp GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(KCXX) $(LIBCXX_CXX_FLAGS) $(LIBCXX_CPP_FLAGS) -c $< -o $@

obj/%.cpp.libk++.o: %.cpp GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(KCXX) $(LIBKXX_CXX_FLAGS) $(LIBKXX_CPP_FLAGS) -c $< -o $@

.PHONY: install
install: install-headers install-libs

.PHONY: install-headers
install-headers:
	mkdir -p $(DEST_DIR)$(INCLUDE_DIR)
	cp -R --preserve=timestamps include/. $(DEST_DIR)$(INCLUDE_DIR)/.

.PHONY: install-libs
install-libs: all
	mkdir -p $(DEST_DIR)$(LIB_DIR)
	cp $(BINARIES) $(DEST_DIR)$(LIB_DIR)

.PHONY: clean
clean:
	rm -rf $(BINARIES)
	rm -rf obj

.PHONY: distclean
distclean:

.PHONY: uninstall
uninstall:
	rm -rf $(DEST_DIR)$(INCLUDE_DIR)
	rm -rf $(DEST_DIR)$(LIB_DIR)