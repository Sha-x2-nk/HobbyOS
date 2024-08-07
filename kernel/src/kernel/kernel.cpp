/* free standing headers */ 
#include <cstdint>  /* uint32_t */
#include <cstddef>  /* size_t, null */


/* Limine headers */ 
#include "limine.h"

/* kernel utils */
#include "kernel/kernelUtils.hpp"

/*
    Set the base revision to 2, this is recommended as this is the latest
    base revision described by the Limine boot protocol specification.
    See specification for more info.
*/
namespace {
    
    __attribute__((used, section(".requests")))
    volatile LIMINE_BASE_REVISION(2);

}

/*
    The Limine requests can be placed anywhere, but it is important that
    the compiler does not optimise them away, so, usually, they should be 
    made volatile or equivalent, and they should be accessed at least
    once or marked as used with "used" attribute as done here.
*/

namespace {

    __attribute__((used, section(".requests")))
    volatile limine_framebuffer_request framebuffer_request = {
        .id = LIMINE_FRAMEBUFFER_REQUEST,
        .revision = 0,
        .response = nullptr
    };

}

/*
    FInally, define the start and end markers for the Limine requests.
    These can also be moved anywhere, to any .cpp file, as seen fit.
*/

namespace {

    __attribute__((used, section(".requests_start_marker")))
    volatile LIMINE_REQUESTS_START_MARKER;

    __attribute__((used, section(".requests_end_marker")))
    volatile LIMINE_REQUESTS_END_MARKER;

}

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

    /* Ensure we got a framebuffer. */
    if (framebuffer_request.response == nullptr
     || framebuffer_request.response->framebuffer_count < 1) {
        suspendKernel();
    }

    /* Fetch the first framebuffer */
    limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    /* Note: we assume the framebuffer is RGB with 32-bit pixels */
    for(std::size_t i = 0; i < 100; ++i) {
        volatile std::uint32_t *fb_ptr = static_cast<volatile std::uint32_t*>(framebuffer->address);
        fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xFFFFFFFF;
    }

    suspendKernel();

}