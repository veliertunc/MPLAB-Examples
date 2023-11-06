/*
 * File:   main.c
 * Author: veli.ertunc
 *
 * Created on 06 Kas?m 2023 Pazartesi, 15:18
 */
#define _XTAL_FREQ 20000000

#include <xc.h>

uint8_t num = 42;

uint8_t seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x6F};


void main(void) {
    TRISB=0x00;//All pins are output
    TRISC=0x00;//All pins are output. Using C0 and C1 as mux
    
    while(1)
    {
        //Turn on 1st display
        PORTCbits.RC0 = 0x01;
        PORTCbits.RC1 = 0x00;
        //Print the 1st digit on the 1st display
        PORTB = seg[num/10];
        __delay_ms(10);
        //Turn on 2nd display
        PORTCbits.RC0 = 0x00;
        PORTCbits.RC1 = 0x01;
        //Print 2nd digit on the 2nd display
        PORTB = seg[num%10];
        __delay_ms(10);
    }

    return;
}
