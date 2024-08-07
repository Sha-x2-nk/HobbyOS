# HobbyOS 
64 bit operating system written for educational purposes.

### Features
Booted using Limine bootloader and its native protocol.

### Steps to build 
You need:
* <b>x86_64-elf cross compiler</b> - Refer OSDev wiki - beware that the cross compiler tutorial does not install libcxx headers...(google it!)
* <b>qemu</b> - emulator, to run BOS. 
```bash
sudo apt-get install qemu-system # to install qemu
```
* <b>xorriso</b> - disk creation. 
```bash
sudo apt-get install xorriso # to install qemu
```
* <b></b> - disk creation. 
```bash
sudo apt-get install xorriso # to install xorriso
```

Then run:

```bash
make            # to create image.iso
make run        # to create image.iso and run it using qemu
make clean      # removes all build files
make distclean  # also removes downloaded stuff - like limine
```

### Work done (Significant points)
* booted using limine bootloader.
* Added C/C++ std lib templates and make rules. Currently contains string functions.