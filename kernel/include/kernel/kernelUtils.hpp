#ifndef KERNEL_KERNEL_UTILS_HPP
#define KERNEL_KERNEL_UTILS_HPP

#include <cstdint> /* uint8_t */

/* Utility function to hang kernel */
void suspendKernel();

/* Utility function to send and recieve a byte from serial ports */
std::uint8_t in_byte(std::uint16_t port);
void out_byte(std::uint16_t port, std::uint8_t data);

#endif