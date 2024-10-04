#ifndef __SOMEDEFINE_H
#define __SOMEDEFINE_H
#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//USART .h file
#define GPIOx GPIOB
#define SCL GPIO_Pin_10
#define SDA GPIO_Pin_9

//I2C   .h file
/*Soft I2c*/
uint16_t RxData;

#endif
