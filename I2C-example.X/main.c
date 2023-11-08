//TODO: Create functions for I2C start & stop conditions, read & write operations

#include<xc.h>
#define _XTAL_FREQ 20000000

#define RS PORTBbits.RB0
#define RW PORTBbits.RB1
#define EN PORTBbits.RB2

// rtc macros for ds1307
#define DS1307_address 0xD0
#define second        0x00
#define minute        0x01
#define hour          0x02
#define day           0x03
#define date          0x04
#define month         0x05
#define year          0x06
#define control_reg   0x07

void DS1307_write(char sec, char min, char hr, char _day, char _date, char _month, char _year);
void DS1307_read(char slave_address,char register_address);

void delay(unsigned int Delay);

void bcd_to_ascii(unsigned char value);
char decimal_to_bcd(unsigned char value);


void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_Init();
void lcd_word( const unsigned char *words);

unsigned char __sec,__min,__hr,__day,__date,__month,__yr,__con;
void main(void)
{
    TRISC  = 0xFF;
    SSPADD = 49;
    SSPCON = 0x28;
    TRISD=0x00;
    PORTD=0x00;
    TRISB=0x00;
    PORTB=0x00;
    lcd_Init();
   
    lcd_cmd(0x80);	
    lcd_word("CLOCK:");
     lcd_cmd(0xC0);	
    lcd_word("DATE:");
    DS1307_write(3,2,1,1,5,4,20);
    __delay_ms(300);
    while(1) {
        __delay_ms(20);
        DS1307_read(DS1307_address,0);    
    }
    
    return;
}

void bcd_to_ascii(unsigned char value)
{
    unsigned char bcd;
    bcd= value;
    bcd=bcd&0xf0;
    bcd=bcd>>4; 
    bcd=bcd|0x30;
    lcd_data(bcd);
    bcd=value;
    bcd=bcd&0x0f;
    bcd=bcd|0x30;
    lcd_data(bcd);
}

char decimal_to_bcd(unsigned char value)
{
	unsigned char msb,lsb,hex;
    msb=value/10;       
    lsb=value%10;        
    hex = ((msb<<4)+lsb);
    return hex;
}

void DS1307_write(char _second, char _minute, char _hour, char _day, char _date, char _month, char _year)
{
    /* start bit*/
    SSPCON2bits.SEN = 1;      // initiate start condition
    while(SEN);               // wait for start condition to complete
    PIR1bits.SSPIF = 0;       // clear SSPIF flag
    
    /* slave address bits*/
    SSPBUF = DS1307_address;    // send the slave address high and r/w = 0 for write
    while(!SSPIF);            // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;       // clear SSPIF flag
    if(SSPCON2bits.ACKSTAT)   
    {  
        SSPCON2bits.PEN = 1;  // initiate stop condition 
        while(PEN);           // wait for stop condition to complete 
        return;               // exit write (no acknowledgment)
    }
    
    SSPBUF = second;    // send the slave address high and r/w = 0 for write
    while(!SSPIF);            // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;       // clear SSPIF flag
    if(SSPCON2bits.ACKSTAT)   
    {  
        SSPCON2bits.PEN = 1;  // initiate stop condition 
        while(PEN);           // wait for stop condition to complete 
        return;               // exit write (no acknowledgment)
    }
    
    SSPBUF =  decimal_to_bcd(_second);          // send the data 
    while(!SSPIF);             // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;        // clear SSPIF flag
    
    SSPBUF = decimal_to_bcd( _minute);          // send the data 
    while(!SSPIF);             // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;        // clear SSPIF flag
    
    SSPBUF =  decimal_to_bcd(_hour);          // send the data 
    while(!SSPIF);             // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;        // clear SSPIF flag
    
    SSPBUF = decimal_to_bcd(_day);          // send the data 
    while(!SSPIF);             // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;        // clear SSPIF flag
 
    SSPBUF =  decimal_to_bcd(_date);          // send the data 
    while(!SSPIF);             // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;        // clear SSPIF flag
    
    SSPBUF =  decimal_to_bcd(_month);          // send the data 
    while(!SSPIF);             // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;        // clear SSPIF flag
    
    SSPBUF =  decimal_to_bcd(_year);          // send the data 
    while(!SSPIF);             // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;        // clear SSPIF flag
    
    SSPBUF = 0x00;          // send the data 
    while(!SSPIF);             // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;        // clear SSPIF flag

    /*  stop bits */
    SSPCON2bits.PEN = 1;   // initiate stop condition 
    while(PEN);            // wait for stop condition to complete 
}


void DS1307_read(char slave_address,char register_address)
{
          /* start bit*/
    SSPCON2bits.SEN = 1;      // initiate start condition
    while(SEN);               // wait for start condition to complete
    PIR1bits.SSPIF = 0;       // clear SSPIF flag
    
    /* slave address bits*/
    SSPBUF = slave_address;    // send the slave address high and r/w = 0 for write
    while(!SSPIF);            // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;       // clear SSPIF flag
    if(SSPCON2bits.ACKSTAT)   
    {  
        SSPCON2bits.PEN = 1;  // initiate stop condition 
        while(PEN);           // wait for stop condition to complete 
        return;               // exit write (no acknowledgment)
    }
        /* slave address bits*/
    SSPBUF = register_address;    // send the slave address high and r/w = 0 for write
    while(!SSPIF);            // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;       // clear SSPIF flag
    if(SSPCON2bits.ACKSTAT)   
    {  
        SSPCON2bits.PEN = 1;  // initiate stop condition 
        while(PEN);           // wait for stop condition to complete 
        return;               // exit write (no acknowledgment)
    }
          /* Repeated start bit*/
    SSPCON2bits.RSEN = 1;      // initiate start condition
    while(RSEN);               // wait for start condition to complete
    PIR1bits.SSPIF = 0;       // clear SSPIF flag 
    
    /* slave address bits*/
    SSPBUF = (slave_address + 1);    // send the slave address high and r/w = 1 bit
    while(!SSPIF);            // wait for acknowledge SSPIF is set for every 9th clock cycle
    PIR1bits.SSPIF = 0;       // clear SSPIF flag
    if(SSPCON2bits.ACKSTAT)   
    {  
        SSPCON2bits.PEN = 1;  // initiate stop condition 
        while(PEN);           // wait for stop condition to complete 
        return ;               // exit write (no acknowledgment)
    }
    
        /* Receive enable bit*/
    SSPCON2bits.RCEN = 1;                  // initiate receive enable
    while(!SSPSTATbits.BF);               // wait for BUFFER TO BE FULL
    __sec = SSPBUF;                  // clear SSPIF flag 
 
        
    SSPCON2bits.ACKDT = 0;     // Prepare to send NACK
    SSPCON2bits.ACKEN = 1;     // Initiate to send NACK 
    while(ACKEN);      
    
            /* Receive enable bit*/
    SSPCON2bits.RCEN = 1;                  // initiate receive enable
    while(!SSPSTATbits.BF);               // wait for BUFFER TO BE FULL
    __min = SSPBUF;                  // clear SSPIF flag 
   
    
    SSPCON2bits.ACKDT = 0;     // Prepare to send NACK
    SSPCON2bits.ACKEN = 1;     // Initiate to send NACK 
    while(ACKEN);      
    
    
            /* Receive enable bit*/
    SSPCON2bits.RCEN = 1;                  // initiate receive enable
    while(!SSPSTATbits.BF);               // wait for BUFFER TO BE FULL
    __hr = SSPBUF;                  // clear SSPIF flag 
   
    
    SSPCON2bits.ACKDT = 0;     // Prepare to send NACK
    SSPCON2bits.ACKEN = 1;     // Initiate to send NACK 
    while(ACKEN);      
    
            /* Receive enable bit*/
    SSPCON2bits.RCEN = 1;                  // initiate receive enable
    while(!SSPSTATbits.BF);               // wait for BUFFER TO BE FULL
    __day = SSPBUF;                  // clear SSPIF flag 

    
    SSPCON2bits.ACKDT = 0;     // Prepare to send NACK
    SSPCON2bits.ACKEN = 1;     // Initiate to send NACK 
    while(ACKEN);      
    
            /* Receive enable bit*/
    SSPCON2bits.RCEN = 1;                  // initiate receive enable
    while(!SSPSTATbits.BF);               // wait for BUFFER TO BE FULL
    __date = SSPBUF;                  // clear SSPIF flag 
  
    
    SSPCON2bits.ACKDT = 0;     // Prepare to send NACK
    SSPCON2bits.ACKEN = 1;     // Initiate to send NACK 
    while(ACKEN);      
    
    
            /* Receive enable bit*/
    SSPCON2bits.RCEN = 1;                  // initiate receive enable
    while(!SSPSTATbits.BF);               // wait for BUFFER TO BE FULL
    __month = SSPBUF;                  // clear SSPIF flag 
  
    
    SSPCON2bits.ACKDT = 0;     // Prepare to send NACK
    SSPCON2bits.ACKEN = 1;     // Initiate to send NACK 
    while(ACKEN);      
    
            /* Receive enable bit*/
    SSPCON2bits.RCEN = 1;                  // initiate receive enable
    while(!SSPSTATbits.BF);               // wait for BUFFER TO BE FULL
    __yr = SSPBUF;                  // clear SSPIF flag 
 
 
    SSPCON2bits.ACKDT = 0;     // Prepare to send NACK
    SSPCON2bits.ACKEN = 1;     // Initiate to send NACK 
    while(ACKEN);      
    
            /* Receive enable bit*/
    SSPCON2bits.RCEN = 1;                  // initiate receive enable
    while(!SSPSTATbits.BF);               // wait for BUFFER TO BE FULL
    __con = SSPBUF;                  // clear SSPIF flag 
    
    SSPCON2bits.ACKDT = 1;     // Prepare to send NACK
    SSPCON2bits.ACKEN = 1;     // Initiate to send NACK 
    while(ACKEN);              // WAIT  FOR NACK TO COMPLETE
    
        /*  stop bits */
      SSPCON2bits.PEN = 1;   // initiate stop condition 
      while(PEN);            // wait for stop condition to complete 
      
      
    lcd_cmd(0x88);
    bcd_to_ascii(__hr);  
    lcd_data(':'); 
    bcd_to_ascii(__min);  
    lcd_data(':');   
    bcd_to_ascii(__sec);
    
    lcd_cmd(0xC7);
    bcd_to_ascii(__date);  
    lcd_data('/'); 
    
    bcd_to_ascii(__month);  
    lcd_data('/');
    
    bcd_to_ascii(__yr); 
}
void delay(unsigned int Delay)
{
while(Delay--);
}

void lcd_Init()
{
lcd_cmd(0x38);
lcd_cmd(0x06);
lcd_cmd(0x0c);
lcd_cmd(0x01);
lcd_cmd(0x80);		
}	

void lcd_cmd(unsigned char cmd)
{
	PORTD = cmd;
	EN=1;
	RS=0;
	RW=0;
	delay(500);
	EN=0;		
}

void lcd_data(unsigned char data)
{
	PORTD =data;
	EN=1;
	RS=1;
	RW=0;
	delay(500);
	EN=0;	
	
}

void lcd_word( const unsigned char *words)
{
	int i=0;
  while(words[i]!='\0')
  {
	lcd_data(words[i]);
    i++;	 

  } 	
	
}	