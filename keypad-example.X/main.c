#include <xc.h>

#define RS PORTDbits.RD0
#define RW PORTDbits.RD1
#define EN PORTDbits.RD2

//Keypad columns
#define C1 PORTBbits.RB0
#define C2 PORTBbits.RB1
#define C3 PORTBbits.RB2
//Keypad rows
#define R1 PORTBbits.RB4
#define R2 PORTBbits.RB5
#define R3 PORTBbits.RB6
#define R4 PORTBbits.RB7

void lcd_data(unsigned char data)
{
    PORTC = data;
    RS = 1;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void lcd_command(unsigned char cmd)
{
    PORTC = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void lcd_string(const unsigned char *str,unsigned char num)  
{
    unsigned char i;
    for(i=0;i<num;i++)
    {
      lcd_data(str[i]);  
        
    }
}

void lcd_initialise()
{
    lcd_command(0x38);
    lcd_command(0x06);
    lcd_command(0x0C);
    lcd_command(0x01);
}

void keypad(void)
{
    C1=1;C2=0;C3=0;//Energize 1st column
    if(R1==1)
    {
        lcd_data('1');
        while(R1==1);
    }
    if(R2==1)
    {
        lcd_data('4');
        while(R2==1);
    }
    if(R3==1)
    {
        lcd_data('7');
        while(R3==1);
    }
    if(R4==1)
    {
        lcd_data('*');
        while(R4==1);
    }
    C1=0;C2=1;C3=0;//Energize 2nd column
    if(R1==1)
    {
        lcd_data('2');
        while(R1==1);
    }
    if(R2==1)
    {
        lcd_data('5');
        while(R2==1);
    }
    if(R3==1)
    {
        lcd_data('8');
        while(R3==1);
    }
    if(R4==1)
    {
        lcd_data('0');
        while(R4==1);
    }
    C1=0;C2=0;C3=1;//Energize 3d column
    if(R1==1)
    {
        lcd_data('3');
        while(R1==1);
    }
    if(R2==1)
    {
        lcd_data('6');
        while(R2==1);
    }
    if(R3==1)
    {
        lcd_data('9');
        while(R3==1);
    }
    if(R4==1)
    {
        lcd_data('#');
        while(R4==1);
    }
}
void main(void) {
    TRISC = 0x00;//Set all port C pins as output
    TRISD = 0x00;//Set all port D pins as output
    TRISB = 0xF0;//Set B7,B6,B5,B4 as input, set others output
    lcd_initialise();
    lcd_command(0x80);
    lcd_string("KEYPAD:",7);
    lcd_command(0xC0);
    while(1)
    {
       keypad(); 
    }
    return;
}
