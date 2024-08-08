#include "drivers/serial.hpp"
#include "kernel/kernelUtils.hpp"

#define COM1_PORT 0x3F8
namespace serial {

    /* 
        Call it once to setup serial logging. 
        Returns false if loopback test fails.
    */
    bool init() {
        out_byte(COM1_PORT + 1, 0x00);    /* Disable all interrupts */
        out_byte(COM1_PORT + 3, 0x80);    /* Enable DLAB (set baud rate divisor) */
        out_byte(COM1_PORT + 0, 0x03);    /* Set divisor to 3 (lo byte) 38400 baud */
        out_byte(COM1_PORT + 1, 0x00);    /*                  (hi byte)            */
        out_byte(COM1_PORT + 3, 0x03);    /* 8 bits, no parity, one stop bit */
        out_byte(COM1_PORT + 2, 0xC7);    /* Enable FIFO, clear them, with 14-byte threshold */
        out_byte(COM1_PORT + 4, 0x0B);    /* IRQs enabled, RTS/DSR set */
        out_byte(COM1_PORT + 4, 0x1E);    /* Set in loopback mode, test the serial chip */
        out_byte(COM1_PORT + 0, 0xAE);    /* Test serial chip (send byte 0xAE and check if serial returns same byte) */

        /* Check if serial is faulty (i.e: not same byte as sent) */
        if(in_byte(COM1_PORT + 0) != 0xAE) {
            return false;
        }

        /* 
            If serial is not faulty set it in normal operation mode
            (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
        */
        out_byte(COM1_PORT + 4, 0x0F);
        return true;
    }

    /* transmit function */
    void transmit(char c) {
        auto is_transmit_buffer_empty = [](){ return in_byte(COM1_PORT + 5) & 0x20; };

        while (is_transmit_buffer_empty() == false) {}

        /* if not empty */
        out_byte(COM1_PORT, static_cast<uint8_t> (c));
    }

    /* transmit function */
    void transmit(char* s) {
        int len = 0;
        
        while (s[len]) {
            transmit(s[len]);
            ++len;
        }
    }

} /* namspace serial */