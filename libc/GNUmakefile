# Defining compilers and linkers
KCC					?=	x86_64-elf-gcc
KLD					?=	x86_64-elf-ld

KAR					?=	x86_64-elf-ar

SHARED_FLAGS		?= 	-O2 -g
KC_FLAGS			?=
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
						-std=gnu11				\
						$(SHARED_FLAGS)			\

KCPP_FLAGS			+=							\
						-Iinclude				\
						-MMD					\
						-MP						\

LIBK_C_FLAGS		:=							\
						$(KC_FLAGS)				\

LIBC_C_FLAGS		:=							\
						$(KC_FLAGS)				\

LIBK_CPP_FLAGS		:=							\
						$(KCPP_FLAGS)			\
						-D__is_kernel			\

LIBC_CPP_FLAGS		:= 							\
						$(KCPP_FLAGS)			\
						-D__is_libc				\

FREE_OBJS			=							\
						obj/string/memcmp.c.o	\
						obj/string/memcpy.c.o	\
						obj/string/memmove.c.o	\
						obj/string/memset.c.o	\
						obj/string/strlen.c.o	\

HOSTED_OBJS			=

OBJS				=							\
						$(FREE_OBJS)			\
						$(HOSTED_OBJS)			\
					
LIBK_OBJS			=	$(FREE_OBJS:.c.o=.c.libk.o)	\

BINARIES			=	obj/libk.a	# libc not ready yet/

# Searching files 
C_FILES				=	$(shell find -L * -type f -name '*.c')
HEADER_DEPS			=	$(addprefix obj/,$(C_FILES:.c=.c.d))

.PHONY: all
all: $(BINARIES)

obj/libk.a: $(LIBK_OBJS)
	$(KAR) rcs $@ $(LIBK_OBJS)

obj/libc.a: $(OBJS)
	$(KAR) rcs $@ $(OBJS)

# Include header dependencies.
-include $(HEADER_DEPS)

# Compilation rules for *.c files.
obj/%.c.o: %.c GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(KCC) $(LIBC_C_FLAGS) $(LIBC_CPP_FLAGS) -c $< -o $@

obj/%.c.libk.o: %.c GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(KCC) $(LIBK_C_FLAGS) $(LIBK_CPP_FLAGS) -c $< -o $@

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