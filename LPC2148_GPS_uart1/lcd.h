#include <LPC214X.H>

#define LCD 0x00ff0000
#define RS  1<<15
#define RW	1<<13
#define EN	1<<12


void delay(unsigned int time){
	int i,j;
 	for(i=0;i<time;i++)
		for(j=0;j<200;j++);
}

void sendCommand(unsigned char command){
	delay(100);
	IOCLR0 |= LCD;				
	IOSET0 |= command<<16; 	    
	IOCLR0 |= RS;
	IOCLR0 |= RW;				
	delay(100);
	IOSET0 |= EN;			    
	delay(100);
	IOCLR0 |= EN;
	delay(50);
}

void sendData(unsigned char data){
	IOCLR0 |= LCD;				
	IOSET0 |= data<<16; 	
	IOSET0 |= RS;		 		
	IOCLR0 |= RW;				
	delay(100);
	IOSET0 |= EN;			  
	delay(100);
	IOCLR0 |= EN;
	delay(50);
}

void lcdInit(){
 	PINSEL0 = 0;   
	PINSEL1 = 0;
	PINSEL2 = 0;
	IODIR0 |= RS|EN|RW;   
	IODIR0 |= LCD;	   	  
	sendCommand(0x38);	  
	sendCommand(0x0E);
	sendCommand(0x01);
	sendCommand(0x06);	  	  	  
}

void lcdDisplay(unsigned int row,unsigned int column,unsigned char *message){
	if(row == 1)
  		row = 0x80;
	else
		row = 0xC0;

	sendCommand((column-1|row)); 
	while(*message){			 
	 	sendData(*message++);
	}
}