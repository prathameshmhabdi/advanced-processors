#include"lcd.h"
 
 unsigned char RxData;
 void SerialTx(unsigned char Txdata){
  	U0THR = Txdata;
		while(!(U0LSR&=0x40));
	 
 }

 void SerialTxMessage(const char *message){
  	while(*message)
		SerialTx(*message++);
 }

 void SerialRx(){
	while(!(U0LSR&=0x01));
	RxData = U0RBR;
	sendData(RxData);
	
 }
 
 
 int main(){
 	lcdInit();
	lcdDisplay(1,1,"Received Info");
  PINSEL0 =0x00000005;   
	U0FCR = 0x07;
	U0LCR = 0x83;
	U0DLL = 98; 
	U0LCR = 0x03;
	SerialTxMessage("Welcome to VIIT");
	sendCommand(0xC0);
	while(1){
	
	 	SerialRx();
	}
 }