#include <xc.h>

#define _XTAL_FREQ 20000000
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define RS PORTDbits.RD0
#define RW PORTDbits.RD1
#define EN PORTDbits.RD2

#ifndef USE_4BIT
void lcd_data(uint8_t data)
{
    PORTC=data;
    RS=1;
    RW=0;
    EN=1;
    __delay_ms(5);
    EN=0;
    
}


void lcd_command(uint8_t cmd)
{
    PORTC = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void lcd_initialise()
{
    lcd_command(0x38);
    lcd_command(0x06);
    lcd_command(0x0C);
    lcd_command(0x01);
}
#else
void lcd_command(unsigned char cmd)
{
	PORTB  = (cmd & 0xF0) ; 
	EN = 1;
    RW = 0;
	RS = 0;
    __delay_ms(2);
	EN = 0;
	PORTB  = ((cmd<<4) & 0xF0) ; 
	EN = 1;
    RW = 0;
	RS = 0;
    __delay_ms(2);
	EN = 0;	
}

void lcd_data(unsigned char data)
{
   	PORTB  = (data & 0xF0) ; 
	EN = 1;
    RW = 0;
	RS = 1;
    __delay_ms(2);
	EN = 0;
	PORTB  = ((data<<4) & 0xF0) ; 
	EN = 1;
    RW = 0;
	RS = 1;
    __delay_ms(2);
	EN = 0;	
}

void lcd_initialise()
{
    lcd_command(0x28); // 4bit mode and 16 columns and 2 rows of lcd
    lcd_command(0x0C);
    lcd_command(0x06); // auto increment 
    lcd_command(0x01); // clearscreen
}
#endif

void lcd_string(const uint8_t *str, uint32_t length)  
{
    uint32_t i;
    for(i=0;i<length;i++)
    {
      lcd_data(str[i]);  
        
    }
}


void main(void) {
    
    TRISC = 0x00;
    TRISD = 0x00;
    lcd_initialise();
    
    while (1) {
        lcd_command(0x38);
        lcd_string("EMBEDDED",8);
        lcd_command(0xC3);
        lcd_string("SYSTEMS",7);
    }

    
    return;
}
