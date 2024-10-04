#include "stm32f10x.h"                  // Device header
#include "stdint.h"
#include "ComProtocol.h"

int main(){
 //	uint16_t Arry[]={0x21,0x04,0x11};
	uint16_t byte = 12;
	WansUsart_Init();
	
	URTSendByte(byte);
}
