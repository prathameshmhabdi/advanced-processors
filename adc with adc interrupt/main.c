#include <lpc214x.h>
#include "lcd.h"
#include <stdio.h>
#define CLKDIV (15-1) //4Mhz ADC clock 
#define BURST_MODE_ON (1<<16) 
#define CLKS_10bit ((0<<19)|(0<<18)|(0<<17)) //10bit - used in burst mode only
#define PowerUP (1<<21)
unsigned int count,data;
char buff[20];

__irq void AD0ISR(void);



int main(void)
{
	lcdInit();
	
	PINSEL1 |= (1<<25)|(1<<24) ; 
	
	VICIntEnable |= (1<<18) ;
	VICVectCntl0 = (1<<5) | 18 ;
	VICVectAddr0 = (unsigned) AD0ISR;
	unsigned long AD0CR_setup = (CLKDIV<<8) | BURST_MODE_ON | CLKS_10bit | PowerUP; //Setup ADC
	AD0INTEN = (1<<1)  ;  
	AD0CR =  AD0CR_setup | (1<<1) ; 
	while(1)
	{	
	}
}

__irq void AD0ISR(void) //AD0 Interrupt Function
{
	count++;
	data = (AD0GDR& 0x0000FFFF)>>6;
	data=780;
	sprintf(buff,"ADC:%04dI:%04d",data,count); 
	lcdDisplay(2,1,buff);
	VICVectAddr = 0x0; //Signal that ISR has finished
}