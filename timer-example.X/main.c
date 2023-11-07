/*
 * File:   main.c
 * Author: veli.ertunc
 *
 * Created on 07 Kas?m 2023 Sal?, 09:04
 */


#include <xc.h>
#define _XTAL_FREQ 20000000

uint8_t timer_count = 0;

void interrupt ISR()
{
    if (INTCONbits.TMR0IF) {
        timer_count++;
        INTCONbits.TMR0IF = 0;
    }

}

void init_tim0(void)
{
    OPTION_REGbits.T0CS = 0;//Use internal clock
    OPTION_REGbits.PSA = 0; //Use Timer 0
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;//Timer clock = clock /256
    
    //Formula for load value
    // delay = (255-TMR0)*Prescalar*Machine Cycle
    //where machine cycle= 4/20Mhz =200 ns
    //To get time dleay of 10 ms at prescalar 256 TMR0 = 59
    TMR0 = 59;
}

void main(void) {
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.TMR0IE = 1;
    
    TRISB0=0;
    
    init_tim0();
    
    while (1) {
        if (timer_count == 0) {
            PORTBbits.RB0 = 1;
        }
        
        if (timer_count == 100) {
            PORTBbits.RB0 = 0;
        }
        
        if (timer_count >= 200) {
            timer_count = 0;
        }
        
    }

    return;
}
