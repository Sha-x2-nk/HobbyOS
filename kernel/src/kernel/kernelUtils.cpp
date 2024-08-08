#include "kernel/kernelUtils.hpp"

/* Utility function to hang kernel */
void suspendKernel() {
    asm volatile ("cli; hlt;");
}

/* Utility function to send and recieve a byte from serial ports */
uint8_t in_byte(uint16_t port) {
    uint8_t data = 0;

    asm volatile (
                "inb %%dx, %%al;"   /* asssmebly template */
                : "=a" (data)       /* output operands */
                : "d" (port)        /* input operand */
            );
    
    return data;
}

void out_byte(uint16_t port, uint8_t data) {
    asm volatile (
                "outb %%al, %%dx;"      /* assembly template */
                :                       /* output operands */
                : "a" (data), "d" (port)/* input operands */
    );
}