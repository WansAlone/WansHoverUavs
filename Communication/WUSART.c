/*this c file mainly implements USART communication protocol
  write by Wans
*/
#include "SomeDefine.h"

/**
  * @brief USART Iint and configuration
  */
void WansUsart_Init(void){
	//turn on USART and GPIO's clock.
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//the GPIO of USART, GPIOA_9/10 config.
	GPIO_InitTypeDef URIO_InitStructure;
	URIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	URIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	URIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &URIO_InitStructure);
	
	URIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	URIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	URIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &URIO_InitStructure);
	//the USART init config.
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	
	//the USART and GPIO enable.
	
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
	
	//turn on the interrupt of USART recive. 
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef USART_NVIC_Struct;
	USART_NVIC_Struct.NVIC_IRQChannel = USART1_IRQn;
	USART_NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
	USART_NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 1;
	USART_NVIC_Struct.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&USART_NVIC_Struct);
}

/**
  * @brief send byte data
*/
void URTSendByte(uint16_t byte){
	USART_SendData(USART1,byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

/**
  * @brief send arry data
*/
void URTSendArry(uint16_t *Arry, uint8_t length){
	int i = 0;
	do{
		USART_SendData(USART1,Arry[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
		i++;
	}while(i<length);
}

/**
  * @brief send string data
*/
void URTSendString(char *string){
	int i = 0;
	do{
		URTSendByte(string[i]);
		i++;
	}while(string[i] != '\0');
}

/**
  * @brief send number data
*/
void URTSendNum(uint16_t Num, uint8_t Numlen){
	uint16_t pow = 1;
	do{
		if(Numlen <= 1) break;
		URTSendByte(Num/pow %10 + '0');
		pow = pow*10;
	}while(Numlen--);
}

/**
  * @brief recive data
*/
uint16_t URTRecive(void){
	return RxData;
}

void USART1_IRQHandler(void){
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == 1){
		RxData = USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);
	}
}
