#include <xc.h>
#define _XTAL_FREQ 20000000

void main(void) {
    TRISB0 = 1;
    TRISB1 = 0;
    
    while (1) {
        PORTBbits.RB1 = PORTBbits.RB0;
        //Same as the code below
        /*
        if (PORTBbits.RB0) {
            PORTBbits.RB1=1;
        } else {
            PORTBbits.RB1=0;
        }
         */
    }

    
    return;
}
