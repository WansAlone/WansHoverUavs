#include "stm32f10x.h"                  // Device header

/*USART Functions*/
void WansUsart_Init(void);
void URTSendByte(uint16_t byte);
void URTSendArry(uint16_t *Arry, uint8_t length);
void URTSendString(char *string);
void URTSendNum(uint16_t Num, uint8_t Numlen);
uint16_t URTRecive(void);

/*I2C Soft Functions*/
void WI2CS_Init(void);
void WI2CS_W_SCL(uint8_t vbit);
void WI2CS_W_SDA(uint8_t vbit);
void WI2CS_Start(void);
void WI2CS_Stop(void);
void WI2CS_SendByte(uint8_t Tdata);
void WI2CS_SendAck(uint8_t AckBit);
uint8_t WI2CS_RecvAck(void);
uint8_t WI2CS_RecvByte(void);
uint8_t WI2CS_R_SDA(void);