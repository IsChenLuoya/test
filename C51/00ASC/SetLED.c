#include <at89c51RC2.h>

void setLED(unsigned char i, unsigned char state) 
{
    if (state) {
        P2 |= (1 << i);
    } else {
        P2 &= ~(1 << i);
    }
}