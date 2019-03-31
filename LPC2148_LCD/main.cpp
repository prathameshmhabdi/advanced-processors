#include <LPC214x.h>
#include "lcd.h"


int main(){
lcdInit();
lcdDisplay(1,1,"1234.1234N");
lcdDisplay(2,1,"4321.4321E");


}