#include "kernel/kernelUtils.hpp"

#include <cstdint> /* uint8_t, uint16_t */

/* Utility function to hang kernel */
void suspendKernel() {
    asm volatile (
                "cli\n"
                "hlt\n"
            );
}

/* Utility function to send and recieve a byte from serial ports */
std::uint8_t in_byte(std::uint16_t port) {
    std::uint8_t data = 0;

    asm volatile (
                "inb %%dx, %%al;"   /* asssmebly template */
                : "=a" (data)       /* output operands */
                : "d" (port)        /* input operand */
    );
    
    return data;
}

void out_byte(std::uint16_t port, std::uint8_t data) {
    asm volatile (
                "outb %%al, %%dx;"      /* assembly template */
                :                       /* output operands */
                : "a" (data), "d" (port)/* input operands */
    );
}