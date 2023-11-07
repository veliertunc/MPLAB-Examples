#include <xc.h>

#define _XTAL_FREQ 20000000

uint8_t eeprom_read(uint8_t addr)
{
    uint8_t data=0;
    EEADR = addr;
    EEPGD = 0;
    RD = 1;
    data = EEDATA;
    
    return data;
}

void eeprom_write(uint8_t addr,uint8_t data)
{
    char value1=0,value2=0;
    __delay_ms(200);
    //Set addr and data
    EEADR = addr;
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    //Enable write
    EECON1bits.WREN = 1;
    EECON2 = value1;
    EECON2 = value2;
    EECON1bits.WR = 1;
    //Wait for the flag to to se if it's completed
    while (EEIF ==0);
    PIR2bits.EEIF = 0;
    EECON1bits.WR = 0;
    EECON1bits.WREN = 0;
    while (EECON1bits.WR);
}

void main(void) {
    return;
}
