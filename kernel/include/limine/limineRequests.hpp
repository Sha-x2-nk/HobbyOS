/*
  Copyright 2024 Shashank Rajora
  All rights reserved.
*/
#ifndef LIMINE_LIMINEREQUESTS_HPP_
#define LIMINE_LIMINEREQUESTS_HPP_

#include <limine/limine.h>

/* We will use it check if Limine understands our base revision */
extern volatile uint64_t limine_base_revision[3]; 

/* Will use it to fetch framebuffer in kmain */
extern volatile limine_framebuffer_request framebuffer_request;

#endif /* LIMINE_LIMINEREQUESTS_HPP_ */
