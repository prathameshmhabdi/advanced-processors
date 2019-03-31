
 unsigned char RxData;

 void SerialTx(unsigned char Txdata){
  	U0THR = Txdata;
	while(!(U0LSR&=0x40));
	 
 }

 void SerialTxMessage( char *message){
  	while(*message)
		SerialTx(*message++);
 }

 int SerialRx(){
	while(!(U0LSR&=0x01));
	RxData = U0RBR;
	return RxData;
 }
 
 
 void initUart(){
 	
  	PINSEL0 =0x00000005;   //Selecting pin Tx Rx
	U0FCR = 0x07;
	U0LCR = 0x83;
	U0DLL = 98;
	//U0DLM = 
	U0LCR = 0x03;
	
 }