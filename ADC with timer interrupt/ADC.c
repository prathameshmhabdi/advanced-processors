#include <LPC214X.H>
#include "lcd.h"
#include "UART0.h"
#include <stdio.h>


unsigned int data;
char buff[20];
unsigned char count=0;


void initADC(){
	PINSEL1 = 0x05000000;  //ADC channels AD0.1 and AD0.2
	AD0CR = 0x01200300;	   //ADC control Register ,clck 4mhz
}


void timerisr(void) __irq	
{	
count++;
	T0IR = 0xff;
IOPIN0=~IOPIN0;	
	//	volatile unsigned int data;
	AD0CR = 0x01200300 | (1<<1);	  //select channel
	while(!(AD0GDR & 0x80000000));
	data=(AD0GDR & 0x0000FFC0)>>6;
	sprintf(buff,"%04d%04d",data,count); 
	lcdDisplay(2,1,buff);
	
	VICVectAddr = 0;		   		//Acknowledge Interrupt
}

void timer_init(void)
{
	T0CTCR = 0x00;          //Timer mode
	T0MR0  = 5000; 					//Set Match value
	T0MCR  = 0x03;      //Generate Interrupt,reset TC upon match
	T0PR   = 14999;					//Set prescale
	T0TCR  = 1;				  			//Reset counter on every Pclk
	VICVectCntl1 = 0x20 | 4;			//Assign Timer0 interrupt to slot 1
	VICVectAddr1 = (unsigned)timerisr;		//Assign timerisr() interrupt routine to slot 1
	VICIntEnable |= 1<<4;			 	//Enable Timer0 interrupt
}

unsigned int analogRead(char channel){
	static unsigned int data;
	AD0CR = 0x01200300 | (1<<channel);	  //select channel
	while(!(AD0GDR & 0x80000000));
	data = (AD0GDR & 0x0000FFC0)>>6;
	return data; 		
} 

int main(){
	PINSEL0=0;
	IODIR0=0x01;
	lcdInit();
	while(1){
	data=analogRead(1);

	sprintf(buff,"%04d%04d",data,count); 
	lcdDisplay(2,1,buff);
	}
	timer_init();
	while(1);
	//initUart();
//lcdInit();
//	while(1){
	//data = analogRead(1);
	//}		
	//sprintf(dataArray,"ADC:0x%03x %04d",data,data);
	//lcdDisplay(1,1,dataArray);
//	SerialTxMessage(dataArray);
	//SerialTxMessage("\r\n");

	//data = analogRead(2);	
	//data = map(data,0,1023,0,150);
	//sprintf(dataArray,"Temp: %2d'C",data);
	//lcdDisplay(2,1,dataArray);
	//SerialTxMessage(dataArray);
//	SerialTxMessage("\r\n");
	
}



	 