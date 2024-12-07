# Hobby OS
x86_64 Operating System, made for learning purposes.

Booted using Limine boot protocol.
## Requirements
* **GCC**: I have set up a cross compiler to avoid any mistakes while compiling it, steps for building a cross compiler mentioned on OSdev wiki.
* **NASM**: For compiling asm files `sudo apt install nasm`.
* **QEMU**: Emulator for running our OS `sudo apt install qemu-system`.
* **XORRISO**: For making our iso `sudo apt install xorriso`.
*  **CPPLINT**: linter for C++ files. `sudo apt install cpplint`.

## Building and running
`make run`
