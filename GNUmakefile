IMAGE_NAME  = image
KERNEL_NAME = kernel

# Toolchain for building limine executable
HOST_CC  		 	= cc
HOST_CFLAGS  	= -g -O2 -pipe
HOST_CPPFLAGS =
HOST_LDFLAGS 	=
HOST_LIBS 		=

# Setting up sysroot directories
PWD 				= $(shell pwd)
SYSROOT 		= $(PWD)/sysroot
DEST_DIR 		= $(SYSROOT)
PREFIX 			= /usr
BOOT_DIR 		= /boot
INCLUDE_DIR = $(PREFIX)/include
LIB_DIR 		= $(PREFIX)/lib

# Toolchain to build kernel
K_CXX = x86_64-elf-g++
K_CC 	= x86_64-elf-gcc
K_LD 	= x86_64-elf-ld
K_AR 	= x86_64-elf-ar

# Compiler and linker flags for kernel
SHARED_FLAGS 	= -O2 -g --sysroot=$(SYSROOT) -isystem=$(INCLUDE_DIR)
K_CFLAGS 			=
K_CPPFLAGS 		=
K_CXXFLAGS 		=
K_LDFLAGS 		=
K_LDFLAGS_GCC =
K_NASMFLAGS 	=

# Linter for cpp files
CPPLINT = $(shell which cpplint)

# Exporting variables for sub makefiles
export KERNEL_NAME K_CXX K_CC K_LD K_AR CPPLINT
export SHARED_FLAGS K_CFLAGS K_CPPFLAGS K_CXXFLAGS K_LDFLAGS K_LDFLAGS_GCC K_NASMFLAGS
export SYSROOT DEST_DIR PREFIX BOOT_DIR INCLUDE_DIR LIB_DIR

# Primary target
.PHONY: all
all: $(IMAGE_NAME).iso

.PHONY: install
install: $(IMAGE_NAME).iso
	mkdir -p iso
	cp $(IMAGE_NAME).iso iso/$(IMAGE_NAME).iso

# Running the built ISO
.PHONY: run
run: ovmf/ovmf-code-x86_64.fd install
	qemu-system-x86_64 -M q35 -m 2G \
		-drive if=pflash,unit=0,format=raw,file=ovmf/ovmf-code-x86_64.fd,readonly=on \
		-cdrom iso/$(IMAGE_NAME).iso -boot d

# Running the built ISO, with serial ports to be used to input output
.PHONY: run-serialio
run-serialio: ovmf/ovmf-code-x86_64.fd install
	qemu-system-x86_64 -M q35 -m 2G \
		-drive if=pflash,unit=0,format=raw,file=ovmf/ovmf-code-x86_64.fd,readonly=on \
		-cdrom iso/$(IMAGE_NAME).iso -boot d -serial stdio

ovmf/ovmf-code-x86_64.fd:
	mkdir -p ovmf
	curl -Lo $@ https://github.com/osdev0/edk2-ovmf-nightly/releases/latest/download/ovmf-code-x86_64.fd

$(IMAGE_NAME).iso: limine.conf limine/limine libc libc++ kernel
	rm -rf iso_root
	mkdir -p iso_root/boot
	cp -v $(DEST_DIR)$(BOOT_DIR)/$(KERNEL_NAME) iso_root/boot/
	mkdir -p iso_root/boot/limine
	cp -v limine.conf iso_root/boot/limine
	mkdir -p iso_root/EFI/BOOT
	cp -v limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/boot/limine
	cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
	cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/

	xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
		-apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o $(IMAGE_NAME).iso
	
	./limine/limine bios-install $(IMAGE_NAME).iso
	rm -rf iso_root

limine/limine:
	rm -rf limine
	git clone https://github.com/limine-bootloader/limine.git --branch=v8.x-binary --depth=1
	$(MAKE) -C limine \
		CC="$(HOST_CC)" \
		CFLAGS="$(HOST_CFLAGS)" \
		CPPFLAGS="$(HOST_CPPFLAGS)" \
		LDFLAGS="$(HOST_LDFLAGS)" \
		LIBS="$(HOST_LIBS)"

# Building and installing libraries and kernel
.PHONY: libc libc++ kernel
libc:
	$(MAKE) -C libc install
libc++:
	$(MAKE) -C libc++ install
kernel:
	$(MAKE) -C kernel install

# Running cpplint on codebase
.PHONY: cpplint
cpplint:
	# $(MAKE) -C libc cpplint
	# $(MAKE) -C libc++ cpplint
	$(MAKE) -C kernel cpplint

# Cleaning and removing build artifacts
.PHONY: clean
clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C libc++ clean
	$(MAKE) -C libc clean
	rm -rf $(IMAGE_NAME).iso

.PHONY: distclean
distclean: clean
	$(MAKE) -C kernel distclean
	$(MAKE) -C libc++ distclean
	$(MAKE) -C libc distclean
	rm -rf ovmf
	rm -rf limine

.PHONY: uninstall
uninstall:
	$(MAKE) -C kernel uninstall
	$(MAKE) -C libc++ uninstall
	$(MAKE) -C libc uninstall
	rm -rf $(SYSROOT)
	rm -rf iso