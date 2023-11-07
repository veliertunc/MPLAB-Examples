#include <xc.h>

#define _XTAL_FREQ 20000000

void SetPWM(uint32_t dutyCycle)
{
    CCPR1L = dutyCycle>>2;
    CCP1CON &= 0xCF;
    CCP1CON |= 0x30 & (dutyCycle << 4);
}


void main(void) {
    
    TRISC    = 0x00; // Make CCP1 pin as output
    T2CONbits.TMR2ON = 1;
    CCP1CON  = 0x0C; // Configure CCP1 module in PWM mode
	PR2      = 0xFF; // Configure the Timer2 period (~20 kHz)    
    
    while (1) {
        int i;
        for (i = 0; i < 1023; i++) {
            SetPWM(i);
        }
        for (i = 1023; i > 0; i--) {
            SetPWM(i);
        }
    }

    return;
}
