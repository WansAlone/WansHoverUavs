#ifndef __SERIAL_H
#define __SERIAL_H

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArry(uint8_t *Arry, uint8_t Length);
void Serial_SendString(char *String);
void Serial_SendNum(uint16_t Num, uint16_t Length);
void Serial_ClcFlag(void);

uint16_t Serial_RxData(void);
uint16_t Serial_RxFlag(void);
#endif
