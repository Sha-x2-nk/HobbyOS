#ifndef GDT_GDT_HPP
#define GDT_GDT_HPP

namespace gdt {

    /* loads new GDT */
    void load();

    /* Reload the current selectors since they're currently using cached info from prv GDT */
    void flush();

} /* namespace gdt */

#endif