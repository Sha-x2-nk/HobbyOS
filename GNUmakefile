IMAGE_NAME				=	image
KERNEL_NAME				=	kernel

# Capture the current working directory
PWD						=	$(shell pwd)
SYSROOT					=	$(PWD)/sysroot
DEST_DIR				=	$(SYSROOT)
PREFIX					=	/usr
BOOT_DIR				=	/boot
INCLUDE_DIR				=	$(PREFIX)/include
LIB_DIR					=	$(PREFIX)/lib

# Defining compilers and linkers
KCXX					=	x86_64-elf-g++
KCC						=	x86_64-elf-gcc
KLD						=	x86_64-elf-ld
KAR						=	x86_64-elf-ar

SHARED_FLAGS			=	-O2 -g
KCXX_FLAGS				=
KCC_FLAGS				=
KCPP_FLAGS				=
KLD_FLAGS				=
KLD_FLAGS_GCC			=	-Wl

# Flags shared with both gcc and g++
# Conditional export of KCC with -isysroot option
SHARED_FLAGS			+=							\
							--sysroot=$(SYSROOT)	\

# We built our compiler with --no-headers option, so it won't look in sysroot/include as well
SHARED_FLAGS			+=							\
							-isystem=$(INCLUDE_DIR)	\

# Exporting variables for sub makefiles 
export KERNEL_NAME

export KCXX
export KCC
export KLD
export KAR

export SHARED_FLAGS
export KCXX_FLAGS
export KCC_FLAGS
export KCPP_FLAGS
export KLD_FLAGS
export KLD_FLAGS_GCC

export SYSROOT
export DEST_DIR
export PREFIX
export BOOT_DIR
export INCLUDE_DIR
export LIB_DIR

.PHONY: all
all: $(IMAGE_NAME).iso

$(IMAGE_NAME).iso: limine.cfg limine/limine libc libc++ kernel
	mkdir -p iso_root/boot

	cp -v $(DEST_DIR)$(BOOT_DIR)/$(KERNEL_NAME) iso_root/boot/
	mkdir -p iso_root/boot/limine
	cp -v limine.cfg iso_root/boot/limine
	mkdir -p iso_root/EFI/BOOT
	cp -v limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/boot/limine
	cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
	cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/
	
	xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot boot/limine/limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label iso_root -o $(IMAGE_NAME).iso
	
	./limine/limine bios-install $(IMAGE_NAME).iso
	rm -rf iso_root

limine/limine:
	rm -rf limine
	git clone https://github.com/limine-bootloader/limine.git --branch=v7.x-binary --depth=1
	$(MAKE) -C limine

.PHONY: libc
libc:
	$(MAKE) -C libc install

.PHONY: libc++
libc:
	$(MAKE) -C libc++ install

.PHONY: kernel
kernel:
	$(MAKE) -C kernel install

.PHONY: run
run: install
	qemu-system-x86_64 -M q35 -m 2G -cdrom iso/$(IMAGE_NAME).iso -boot d

.PHONY: install
install: $(IMAGE_NAME).iso
	mkdir -p iso
	cp $(IMAGE_NAME).iso iso/$(IMAGE_NAME).iso

.PHONY: clean
clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C libc++ clean
	$(MAKE) -C libc clean
	rm -rf $(IMAGE_NAME).iso

.PHONY: distclean
distclean:
	$(MAKE) -C kernel distclean
	$(MAKE) -C libc++ distclean
	$(MAKE) -C libc distclean
	rm -rf limine

.PHONY: uninstall
uninstall:
	$(MAKE) -C kernel uninstall
	$(MAKE) -C libc++ uninstall
	$(MAKE) -C libc uninstall
	rm -rf $(SYSROOT)
	rm -rf iso