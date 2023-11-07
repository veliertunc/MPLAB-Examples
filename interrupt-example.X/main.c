/*
 * File:   main.c
 * Author: veli.ertunc
 *
 * Created on 07 Kas?m 2023 Sal?, 08:51
 */


#include <xc.h>
#define _XTAL_FREQ 20000000

void interrupt ISR()
{
    if (INTCONbits.INTF) {//Check the register
        PORTCbits.RC0 ^= 1;//Toggle the output
        INTCONbits.INTF = 0;//Clear the interrupt flag
    }

}

void main(void) {
    INTCONbits.GIE = 1;//Enable global interrupt
    INTCONbits.PEIE = 1;//Enable peripheral interrupt
    INTCONbits.INTE = 1; //Enable RB0 external interrupt

    OPTION_REGbits.INTEDG = 1;
    
    TRISC0 = 0;
    while (1) {

    }

    return;
}
