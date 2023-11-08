#include<xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 20000000

unsigned int a;
void spi_write  (unsigned int value)
{
    SSPBUF = value;
    while(!SSPSTATbits.BF);
}
unsigned char spi_read()
{
    SSPBUF = 0x00;                // initiate bus cycle
    while(!PIR1bits.SSPIF);  // wait until cycle complete
    return ( SSPBUF );            // return with byte read	
}
void write_eeprom(unsigned char msb, unsigned char lsb, unsigned char data)
{
    PORTBbits.RB0 = 0;
    spi_write(0x02);
    spi_write(msb);
    spi_write(lsb);
    spi_write(data);
    PORTBbits.RB0 = 1;	
}
void  read_eeprom(unsigned char msb, unsigned char lsb)
{
    PORTBbits.RB0 = 0;
    spi_write(0x03);
    spi_write(msb);
    spi_write(lsb);
    while( !SSPSTATbits.BF );
    a = (spi_read());  
    PORTBbits.RB0 = 1;
}
void main()
{
    TRISCbits.TRISC3  =  0;        //   SERIAL CLOCK AS OUTPUT
    TRISCbits.TRISC4  = 1;       //  MISO AS INPUT
    TRISCbits.TRISC5  = 0;       // MOSI AS OUTPUT
    TRISBbits.TRISB0  = 0;       // SLAVE SELECT PIN AS OUTPUT

    SSPCON = 0x20;
    SSPSTAT = 0x00;
    
    PORTBbits.RB0 = 0;      // slave select low
    spi_write(0x06);
    PORTBbits.RB0 = 1;    // slave select high

    write_eeprom(0x03,0x43,0x09);  // 0x0343 = 09
    __delay_ms(1000);

    PORTBbits.RB0 = 0;   // slave select low
    spi_write(0x04);
    PORTBbits.RB0 = 1;  // slave select high

    __delay_ms(1000);
    read_eeprom(0x03,0x43);
    while(1){
        
    }
    return;
}