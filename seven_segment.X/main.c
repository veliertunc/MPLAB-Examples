/*
 * File:   main.c
 * Author: veli.ertunc
 *
 * Created on 06 Kas?m 2023 Pazartesi, 14:26
 */
#define _XTAL_FREQ 200000000

#include <xc.h>
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

//7-segment display port bit config
//Values to write to get digits 0-9
uint8_t table[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x6F};

void main(void) {
    
    while(1)
    {
        int i;
        for (i = 0; i < 10; i++) {
            PORTC=table[i];
            __delay_ms(1000);
        }
    }
    
    return;
}
