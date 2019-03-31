#include <LPC214X.H>
#include "lcd.h"
#include <stdio.h>
char buff[20];
unsigned int count,data;

unsigned int analogRead(char channel){
	unsigned int data;
	AD0CR = 0x01200300 | (1<<channel);	  //select channel
	//AD0CR =  (1<<channel);
	while(!(AD0GDR & 0x80000000));
	data = (AD0GDR & 0x0000FFC0)>>6;
	return data; 		
} 

void timerisr(void) __irq	
{	count++;
	T0IR = 0xff;
	data = analogRead(1);
	sprintf(buff,"%04dcount:%04d",data,count);
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

void initADC(){
	PINSEL1 = 0x05000000;  //ADC channels AD0.1 and AD0.2
	//AD0CR = 0x01200300;	   //ADC control Register ,clck 4mhz
}



int main(){
	
	
	lcdInit();
	initADC();
	
	lcdDisplay(1,1,"ADC");
	timer_init();
	while(1){

	}		

}

	 