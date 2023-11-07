#include <xc.h>

#define _XTAL_FREQ 20000000

#define EN PORTDbits.RD2
#define RW PORTDbits.RD1
#define RS PORTDbits.RD0

unsigned int a,b,c,d,e,f;
unsigned int temp,adc;
float temperature,adc1;


void delay(unsigned int i)
{
    while(i--);	
}

void lcd_command(unsigned char a)
{
    PORTC=a;
    EN=1;
    RS=0;
    RW=0;
    delay(500);
    EN=0;
}

void chr(unsigned char b)
{
    PORTC=b;
    EN=1;
    RS=1;
    RW=0;
    delay(500);
    EN=0;
}

void str(const char *d,char n)
{
    char o;
    for(o=0;o<n;o++)
    {
        chr(d[o]);
        delay(500);
    }
}	

void lcd_init()
{
    lcd_command(0x38);
    lcd_command(0x06);
    lcd_command(0x0c);
    lcd_command(0x01);
}

void interrupt ISR()
{
    if (PIR1bits.ADIF) {
        //Handle the interrupt
        adc=(ADRESH<<8);   // temp =  0x 0000 0000 0000 0000  & (ADRESH<<8) = 0x 0000 0011 0000 0000 & temp = 0x 0000 0011 0000 0000
		adc=adc+ADRESL;   // temp =  0x 0000 0011 1111 1111
        PIR1bits.ADIF = 0;
    }

}

void adc_init()
{
    ADCON0 = 0x41;
    ADCON1 = 0x8E;
}

void interrupt_init()
{
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    PIE1bits.ADIE = 1;//Enable ADC  interrupt bit
}

void main(void) {
    
    interrupt_init();
    
    TRISD=0X00;
	TRISC=0X00;
	
	PORTC=0x00;
    PORTD=0X00;
	lcd_init();
    
	lcd_command(0x80);
	str("SENSOR:",7);
    
    adc_init();
    
    while (1) {
        ADCON0 |= 0x04;
        
        adc1 = adc/2046; //Find temp value
        temperature = adc1*100;
        
        lcd_command(0x89);    // 0123
		a=(int)temperature/10;   // 012
		b=(int)temperature%10;  // 3
		c=a%10;        // 2
		d=a/10;       // 01
		e=d%10;       // 1
		f=d/10;       // 0
		chr(f+0x30);
		chr(e+0x30);
        
        chr('.');
		chr(c+0x30);
		chr(b+0x30);
    }

    return;
}
