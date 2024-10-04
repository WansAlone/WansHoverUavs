/** @brief this c file mainly implements I2C_Soft communication protocol
    written by Wans
*/
#include "SomeDefine.h"


/**@brief change SCL's potential
   @param uint8_t vbit: 1 or 0
*/
void WI2CS_W_SCL(uint8_t vbit){
	GPIO_WriteBit(GPIOx,SCL,(BitAction)vbit);
	Delay_us(10);
}

/**@brief change SDA's potential
   @param uint8_t vbit: 1 or 0
*/
void WI2CS_W_SDA(uint8_t vbit){
	GPIO_WriteBit(GPIOx,SDA,(BitAction)vbit);
	Delay_us(10);
}

/**@biref read the SDA potential
   @param None
   @return uint8_t
*/
uint8_t WI2CS_R_SDA(void){
	uint8_t vbit = GPIO_ReadInputDataBit(GPIOA,SDA);
	Delay_us(10);
	return vbit;
}

/**@brief I2C protocol Soft GPIO and clock init
   @param None
   @return None
*/
void WI2CS_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef SDA_SCL_Structure;
	SDA_SCL_Structure.GPIO_Mode = GPIO_Mode_Out_OD;
	SDA_SCL_Structure.GPIO_Pin = SDA | SCL;
	SDA_SCL_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &SDA_SCL_Structure);
	//default SDA and SCL is high potential
	GPIO_SetBits(GPIOx, SDA | SCL);
}

/**@brief this is start signal of I2C Soft 
   @param None
   @return None
*/
void WI2CS_Start(void){
	WI2CS_W_SCL(1);
	WI2CS_W_SDA(1);
	WI2CS_W_SCL(0);
	WI2CS_W_SDA(0);
}

/**@brief this is stop signal of I2C Soft  
   @param None
   @return None
*/
void WI2CS_Stop(void){
	WI2CS_W_SCL(0);
	WI2CS_W_SDA(0);
	WI2CS_W_SCL(1);
	WI2CS_W_SDA(1);
}

/**@brief Send a bit data to SDA line.
   @param the Tdata is will be sent data.
   @return None
*/
void WI2CS_SendByte(uint8_t Tdata){
	uint8_t i;
	for(i = 0; i < 8; i++){
		WI2CS_W_SCL(0);
		WI2CS_W_SDA(Tdata & (0x80>>i));
		WI2CS_W_SCL(1);
	}
}

/**@brief Recive the data from SDA line.
   @param None
   @return a bit data byte.
*/
uint8_t WI2CS_RecvByte(void){
	uint8_t byte = 0x00, i;
	WI2CS_W_SDA(1);
	for(i = 0; i < 8; i++){
		WI2CS_W_SCL(1);
		if(WI2CS_R_SDA() == 1)  byte |= 0x80>>i;
		WI2CS_W_SCL(0);
	}
	return byte;
}

/**@brief Choose AckBit send to slever, when master completes data recption.
   @param Response signal AckBit can be 1 or 0, 1 will response.
   @return None.
*/
void WI2CS_SendAck(uint8_t AckBit){
	WI2CS_W_SDA((BitAction)AckBit);
	WI2CS_W_SCL(1);
	WI2CS_W_SCL(0);
}

/**@brief recived the response signal from slever.
   @param None
   @return Ack.
*/
uint8_t WI2CS_RecvAck(void){
	WI2CS_W_SDA(1);
	WI2CS_W_SCL(1);
	uint8_t Ack = WI2CS_R_SDA();
	WI2CS_W_SCL(0);
	return Ack;
}
