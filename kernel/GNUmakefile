# Our kernel executable name
KERNEL_NAME			?=	kernel

# Defining compilers and linkers
KCXX				?=	x86_64-elf-g++
KCC					?=	x86_64-elf-gcc
KLD					?=	x86_64-elf-ld

SHARED_FLAGS		?= 	-O2 -g
KCXX				?=
KC_FLAGS			?=
KCPP_FLAGS			?=
KLD_FLAGS			?=
KLD_FLAGS_GCC		?=	-Wl
KLIBS				?=

DEST_DIR			?=
PREFIX				?=	/usr/local
BOOT_DIR			?=	$(PREFIX)/boot
INCLUDE_DIR			?=	$(PREFIX)/include

SHARED_FLAGS		+=							\
						-Wall					\
						-Wextra					\
						-ffreestanding			\
						-fno-stack-protector	\
						-fno-stack-check		\
						-fno-lto				\
						-fPIE					\
						-m64					\
						-march=x86-64			\
						-mno-80387				\
						-mno-mmx				\
						-mno-sse				\
						-mno-sse2				\
						-mno-red-zone			\

KCXX_FLAGS			+=							\
						-std=gnu++20			\
						-fno-rtti				\
						-fno-exceptions			\
						$(SHARED_FLAGS)			\

KCC_FLAGS			+=							\
						-std=gnu11				\
						$(SHARED_FLAGS)			\

KCPP_FLAGS			+=							\
						-Iinclude				\
						-MMD					\
						-MP						\
						-D__is_kernel			\

KLD_FLAGS			+=							\
						-melf_x86_64			\
						-pie					\
						-ztext					\
						-zmax-page-size=0x1000	\

KLD_FLAGS_GCC		:=	$(KLD_FLAGS_GCC),-pie,-ztext,-zmax-page-size=0x1000,-melf_x86_64

# -lk means libk - with extension .a or .so
KLIBS				+=							\
						-nostdlib				\
						-lk						\
						-lk++					\

# Searching files 
CXX_FILES			=	$(shell find -L * -type f -name '*.cpp')
C_FILES				=	$(shell find -L * -type f -name '*.c')
OBJ					=	$(addprefix obj/,$(CXX_FILES:.cpp=.cpp.o) $(C_FILES:.c=.c.o))
HEADER_DEPS			=	$(addprefix obj/,$(CXX_FILES:.cpp=.cpp.d) $(C_FILES:.c=.c.d))

.PHONY: all
all: bin/$(KERNEL_NAME)

include/limine.h:
	mkdir -p "$$(dirname $@)"
	curl -Lo $@ https://github.com/limine-bootloader/limine/raw/trunk/limine.h

# Link rules for the final kernel executable.	\
The magic printf/dd command is used to force the final ELF file type to ET_DYN. \
GNU binutils, for silly reasons, forces the ELF type to ET_EXEC even for \
relocatable PIEs, if the base load address is non-0. \
See https://sourceware.org/bugzilla/show_bug.cgi?id=31795 for more information. 

# linkage done through g++. with ld - you'll have to manuall set -L PATH_TO_SYSROOT_LIB
bin/$(KERNEL_NAME): GNUmakefile linker.ld $(OBJ)
	mkdir -p "$$(dirname $@)"
	$(KCXX) $(OBJ) $(KCXX_FLAGS) $(KLIBS) -o $@ -Tlinker.ld $(KLD_FLAGS_GCC)

	printf '\003' | dd of=$@ bs=1 count=1 seek=16 conv=notrunc 2>/dev/null

# Include header dependencies.
-include $(HEADER_DEPS)

# Compiler rules for *.cpp files.
obj/%.cpp.o: %.cpp GNUmakefile include/limine.h
	mkdir -p "$$(dirname $@)"
	$(KCXX) $(KCXX_FLAGS) $(KCPP_FLAGS) -c $< -o $@

# Compilation rules for *.c files.
obj/%.c.o: %.c GNUmakefile include/limine.h
	mkdir -p "$$(dirname $@)"
	$(KCC) $(KC_FLAGS) $(KCPP_FLAGS) -c $< -o $@

.PHONY: install
install: install-headers install-kernel

.PHONY: install-headers
install-headers: include/limine.h
	mkdir -p $(DEST_DIR)$(INCLUDE_DIR)
	cp -R --preserve=timestamps include/. $(DEST_DIR)$(INCLUDE_DIR)

.PHONY: install-kernel
install-kernel: all
	mkdir -p $(DEST_DIR)$(BOOT_DIR)
	cp bin/$(KERNEL_NAME) $(DEST_DIR)$(BOOT_DIR)

.PHONY: clean
clean:
	rm -rf bin obj $(HEADER_DEPS)

.PHONY: distclean
distclean:
	rm -rf include/limine.h

.PHONY: uninstall
uninstall:
	rm -rf $(DEST_DIR)$(INCLUDE_DIR)
	rm -rf $(DEST_DIR)$(BOOT_DIR)
