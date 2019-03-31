
#include<lpc214x.h>

void Tx(unsigned char data){
U1THR=data;
while((U1LSR&0x40)==0);
}

void Rx(){
unsigned char msg;
while((U1LSR&0x01)==0);
msg=U1RBR;

}
void Tx_string( char *msg)
{
	while(*msg)
	{
		Tx(*msg);
		msg++;
	}
}

void delay(int time)
{
	int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<5000;j++);
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
	uart1_init();
	//for sending sms
	Tx_string("AT+CMGF=1\r\n");
	delay(200);
	Tx_string("AT+CMGS=\"9145614631\"\r\n");
	delay(200);
	Tx_string("Hii");
	Tx(0x1a);
	delay(200);
	//for dialing call
	delay(200);
	Tx_string("\r\n");
	Tx_string("ATD9145614631;\r\n");
	delay(200);
	Tx_string("ATH\r\n");
	
	
}