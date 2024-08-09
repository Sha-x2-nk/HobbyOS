#include "gdt/gdt.hpp"

#include <cstdint> /* uint16_t, uint64_t */

namespace gdt {

    uint64_t getEntry(uint8_t selector_type, /* Type of selector (4-bit):
                                            |--------------------------------------------------------------------------|
                                            | BITS |       CODE_DESC             |         DATA_DESC                   |
                                            |------|-----------------------------|-------------------------------------|
                                            |Bit 3:|           1                 |             0                       |
                                            |------|-----------------------------|-------------------------------------|
                                            |Bit 2:| Conforming bit (google it!) | causes limit to grow                |
                                            |      |                             | downwards, instead of               |
                                            |      |                             | up - useful for stack selectors.    |
                                            |------|-----------------------------|-------------------------------------|
                                            |Bit 1:| Read-only access to code    | allows writing to this region of    |
                                            |      | accessing constants.        | memory. Region is read-only if      |
                                            |      | Otherwise code cannot be    | cleared.                            |
                                            |      | read as data, only for      |                                     |
                                            |      | instruction fetches.        |                                     |
                                            |------|-----------------------------|-------------------------------------|
                                            |Bit 0:| flag for the cpu to communicate to the OS that the descriptor has |
                                            |      | been accessed in someway, but this feature is mostly abandoned,   |
                                            |      | and should not be used. Most compilers assume enabled, so enable. |
                                            |------|-------------------------------------------------------------------|
                                            */

                    bool not_system_descriptor, /* System Descriptors - TSS, IDT (Not relevant in GDT) or gate-type descriptor (unused in long mode, ignore)*/
                    uint8_t privilige_lvl, /* 0 to 3 - 0 for kernel, 1/2 generally unused, 3 for user */
                    bool present, /* If not set, descriptor is ignored */
                    bool long_mode /* set if descriptor is for long mode (64-bit) */
    ) {
        uint64_t descriptor = 0;

        descriptor |= (static_cast<uint64_t> (selector_type)) << 8;
        descriptor |= (static_cast<uint64_t> (not_system_descriptor)) << 12;
        descriptor |= (static_cast<uint64_t> (privilige_lvl)) << 13;
        descriptor |= (static_cast<uint64_t> (present)) << 15;
        descriptor |= (static_cast<uint64_t> (long_mode)) << 21;

        descriptor = descriptor << 32;
        return descriptor;
    }

    /* loads new GDT */
    void load() {
        const int NUM_ENTRIES = 5; /* 5 entries in GDT */

        /* STATIC is important, otherwise entries will be cleared from memory once out of function scope. */
        static uint64_t gdt_entries[NUM_ENTRIES];

        /* First entry null */
        gdt_entries[0] = 0;

        /* Kernel code */
        gdt_entries[1] = getEntry(/*selector_type = */ 0b1011, 
                                /* not_system_descriptor = */ 1, 
                                /* privilige_lvl = */ 0, 
                                /* present = */ 1,
                                /* long_mode = */ 1
                        );

        /* Kernel data */
        gdt_entries[2] = getEntry(/*selector_type = */ 0b0011, 
                                /* not_system_descriptor = */ 1, 
                                /* privilige_lvl = */ 0, 
                                /* present = */ 1,
                                /* long_mode = */ 1
                        );
        
        /* User code */
        gdt_entries[3] = getEntry(/*selector_type = */ 0b1011, 
                                /* is_system_descriptor = */ 1, 
                                /* privilige_lvl = */ 3, 
                                /* present = */ 1,
                                /* long_mode = */ 1
                        );
        
        /* User data */
        gdt_entries[4] = getEntry(/*selector_type = */ 0b0011, 
                                /* not_system_descriptor = */ 1, 
                                /* privilige_lvl = */ 3, 
                                /* present = */ 1,
                                /* long_mode = */ 1
                        );

        /* Preparing a struct to feed to lgdt register */
        /* STATIC is important, otherwise entries will be cleared from memory once out of function scope. */
        static struct GDTR {
            uint16_t limit;
            uint64_t address;
        } __attribute__((packed)) example_gdtr;

        example_gdtr.limit = NUM_ENTRIES * sizeof(uint64_t) - 1;
        example_gdtr.address = reinterpret_cast<uint64_t> (gdt_entries);

        /* lgdt instruction */
        asm volatile (
                    "lgdt %0"      /* assembly template */
                    :                       /* output operands */
                    : "m" (example_gdtr)    /* input operands */
        );
    }

    /* Reload the current selectors since they're currently using cached info from prv GDT */
    void flush() {
        asm volatile (
                    /* Kernel data at index 0x10 */
                    "mov $0x10, %%ax\n"      
                    "mov %%ax, %%ds\n"
                    "mov %%ax, %%es\n"
                    "mov %%ax, %%fs\n"
                    "mov %%ax, %%gs\n"
                    "mov %%ax, %%ss\n"

                    /* Kernel code at index 0x8 */
                    "pop %%rdi\n"
                    "push $0x8\n"
                    "push %%rdi\n"
                    "lretq\n"

                    :       /* output operands */
                    :       /* input operands */
                    : "ax", "rdi"      /* clobbered registers */
        );
    }

} /* namespace gdt */