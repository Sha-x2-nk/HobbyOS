#include "kernel/kernelUtils.hpp"

void suspendKernel() {
    asm volatile ("cli; hlt;");
}