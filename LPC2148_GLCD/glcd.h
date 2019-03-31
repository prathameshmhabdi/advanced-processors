 
#include <LPC214X.H>

#define LCD 0x00ff0000
#define DI  1<<15
#define RW	1<<13
#define EN	1<<12
#define CS1	1<<10
#define CS2	1<<9




void delay(unsigned int time){
	int i,j;
 	for(i=0;i<time;i++)
		for(j=0;j<200;j++);
}

void longDelay(unsigned int time){
 	int i,j;
 	for(i=0;i<time;i++)
		for(j=0;j<400;j++);
}

void sendCommand(unsigned char command){
	delay(100);
	IOCLR0 |= LCD;				
	IOSET0 |= command<<16; 	    
	IOCLR0 |= DI;		 		
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
	IOSET0 |= DI;		 		
	IOCLR0 |= RW;				
	delay(100);
	IOSET0 |= EN;			    
	delay(100);
	IOCLR0 |= EN;
	delay(50);
}

void glcdInit(){
 	PINSEL0 = 0;   				   
	PINSEL1 = 0;
	PINSEL2 = 0;

	IODIR0 |= EN|RW;   			  
	IODIR0 |= LCD|DI|CS1|CS2;	 
	IOSET0 |= CS1|CS2;
	IOCLR0 |= EN|RW;
	IOCLR0 |= DI;
	delay(100);	 
	sendCommand(0x3f);	  
	sendCommand(0xb8);
	sendCommand(0x40); 	  	  
}

void glcdDisplay(const unsigned char *data){
		
	int i,j;
	for(i=0;i<8;i++){
		IOSET0|=CS1;
		IOCLR0|=CS2;	
		sendCommand(0xB8|i);
		sendCommand(0x40);	
	 	for(j=0;j<64;j++){
			sendData(data[i*128+j]);
		}


		IOSET0|=CS2;
		IOCLR0|=CS1;	
		sendCommand(0xB8|i);
		sendCommand(0x40);	
	 	for(j=64;j<128;j++){
			sendData(data[i*128+j]);
		}

	 }
}