#include "stm32f10x.h"                  // Device header
#include <math.h>
#include <stdio.h>

uint16_t RxData,RxFlag;
//初始配置
void Serial_Init(void){
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//gpio配置
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//usart 配置
	USART_InitTypeDef USART_Structure;
	USART_Structure.USART_BaudRate = 9600;
	USART_Structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Structure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Structure.USART_Parity = USART_Parity_No;
	USART_Structure.USART_StopBits = USART_StopBits_1;
	USART_Structure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_Structure);
	
	USART_Cmd(USART1,ENABLE);
	//usart中断配置
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef USART_NVIC_Struct;
	USART_NVIC_Struct.NVIC_IRQChannel = USART1_IRQn;
	USART_NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
	USART_NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 1;
	USART_NVIC_Struct.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&USART_NVIC_Struct);
}

//发送
void Serial_SendByte(uint8_t Byte){
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}


//发送数组
void Serial_SendArry(uint8_t *Arry, uint8_t Length){
	int i = 0;
	do{
		USART_SendData(USART1,Arry[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
		i++;
	}while(i<Length);
}

//发送字符串
void Serial_SendString(char *String){
	int i = 0;
	do{
		USART_SendData(USART1,String[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
		i++;
	}while(String[i]!='\0');
}

uint16_t Serial_Pow(uint16_t x, uint16_t y){
	uint16_t result =1 ;
	while(y--){
		result *= x;
	}
	return result;
}

void Serial_SendNum(uint16_t Num, uint16_t Length){
	while(Length--){
		Serial_SendByte(Num/Serial_Pow(10,Length) % 10 + '0');
	}
}

uint16_t Serial_RxData(void){
	return RxData;
}

uint16_t Serial_RxFlag(void){
	return RxFlag;
}

void Serial_ClcFlag(void){
	RxFlag = 0;
}

void USART1_IRQHandler(void){
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == 1){
		RxData = USART_ReceiveData(USART1);
		RxFlag = 1;
		USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);
	}
}
