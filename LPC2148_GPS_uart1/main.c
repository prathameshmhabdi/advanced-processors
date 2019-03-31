#include"lcd.h"
 
unsigned char RxData;


void Tx(unsigned char data){	
	U1THR=data;
	while((U1LSR&0x40)==0);
}
void Tx_string( unsigned char *msg)
{
	while(*msg)
	{
		Tx(*msg);
		msg++;
	}
}
 unsigned char SerialRx(){
	while((U1LSR&0x01)==0);
	RxData=U1RBR;
	return RxData;
	
 }
 void GPS_string(unsigned char *temp)
{
	unsigned int i=0;
	do
	{
		temp[i] = SerialRx();
	}
	while(temp[i++] != '*');
	temp[i] = '\0';						
}

void uart1_init(){
PINSEL0=0x05<<16;
U1TER=0x80;
U1FCR=0x07;
U1LCR=0x83;
U1DLM=0;
U1DLL=98;
U1LCR=0x03;
}
 
 int main(){
 


	unsigned char  temp[40],lat[10],lon[10];
	unsigned int i=0,j=0;
 	lcdInit();
	uart1_init();
	while(1){
	
	 		if(SerialRx() == '$')	//if '$' is received
		{
				
				GPS_string(temp);				 //fetch all characters upto '*'		
				i=0;
				j=0;
				while(temp[i++] != ',');	 	//ignore $GPGGA 
				while(temp[i++] != ',');	 	//ignore time
				while(temp[i] != ',')			//Capture Latitude
				lat[j++] = temp[i++];
				j=0;
				while(temp[i++] != ',');
				while(temp[i] != ',')			//Capture Longitude
				lon[j++] = temp[i++];
				lcdDisplay(1,1,lat);	
				lcdDisplay(2,1,lon);
				

			}
		}
	
 }