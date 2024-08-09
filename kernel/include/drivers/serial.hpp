#ifndef DRIVERS_SERIAL_HPP
#define DRIVERS_SERIAL_HPP

namespace serial {

    /* 
        Call it once to setup serial logging. 
        Returns false if loopback test fails.
    */
    bool init();

    /* transmit function */
    void transmit(char c);

    /* transmit function */
    void transmit(const char* s);
    
} /* namspace serial */

#endif 