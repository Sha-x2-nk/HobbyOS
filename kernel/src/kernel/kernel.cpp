/*
  Copyright 2024 Shashank Rajora
  All rights reserved.
*/
#include <limine/limine.h>

#include <cstdint>
#include <cstddef>

#include "limine/limineRequests.hpp"
#include "kernel/kernelUtils.hpp"

/*
  The following stubs are required by the Itanium C++ ABI (the one
  limine uses, regardless of the "Itanium" nomenclature).
  These stubs can be moved to a different .cpp file, but should
  not be removed, unless you know what you are doing.
*/
extern "C" {
  int __cxa_atexit(void (*)(void *), void *, void *) { return 0; }
  void __cxa_pure_virtual() { suspendKernel(); }
  void *__dso_handle;
}

extern "C" void kmain() {
  /* Ensure that the bootloader understands our base revision */
  if (LIMINE_BASE_REVISION_SUPPORTED == false)
    suspendKernel();

  /* Fetch the first framebuffer */
  limine_framebuffer *framebuffer =
    framebuffer_request.response->framebuffers[0];

    /* Note: we assume the framebuffer in RGB with 32-bit pixels */
    for (size_t i = 0; i < 100; ++i) {
      volatile uint32_t *fb_ptr =
        static_cast<volatile uint32_t*>(framebuffer->address);
      fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xFFFFFFFF;
    }

    /* halt/hang */
    suspendKernel();
}