/*
  Copyright 2024 Shashank Rajora
  All rights reserved.
*/
#include "limine/limineRequests.hpp"

#include <limine/limine.h>

#include <cstdint>
#include <cstddef>

/*
  Set the base revision to 2, this is recommended as this is the latest base
  revision described by the Limine boot protocol specification.
  
  The below variable is not declared static/"anynymous namespace" because we
  want to use this variable in kmain.
*/
__attribute__((used, section(".requests")))
volatile LIMINE_BASE_REVISION(2);

/*
  Limine requests can be placed anywhere, but it is important the compiler does
  not optimise them away, so, usually they should be made volatile or
  equivalent, and they should be accessed at least once or marked as used with
  the "used" attribute as done below.
  
  The below variable is not declared static/"anonymous namespace" because we
  want to use this variable in our kmain.
*/
__attribute__((used, section(".requests")))
volatile limine_framebuffer_request framebuffer_request = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0,
  .response = nullptr
};

/* Finally, define the start and end markers for Limine Requests */
namespace {

__attribute__((used, section(".requests_start_marker")))
volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".requests_end_marker")))
volatile LIMINE_REQUESTS_END_MARKER;

}
