; Copyright 2024 Shashank Rajora
; All rights reserved.
BITS 64

section .text

; Utility function to hang kernel
global suspendKernel

suspendKernel:
  cli
  hlt
