
#ifndef __I2CHANDLER_H__
#define __I2CHANDLER_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* The M24C08W contains 4 blocks (128byte each) with the adresses below: E2 = 0 */
/* EEPROM Addresses defines */
#define EEPROM_Block0_ADDRESS 0xA0 /* E2 = 0 */
#define EEPROM_Block1_ADDRESS 0xA2 /* E2 = 0 */
//#define EEPROM_Block2_ADDRESS 0xA4 /* E2 = 0 */
//#define EEPROM_Block3_ADDRESS 0xA6 /* E2 = 0 */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void I2C_EE_Init(void);
void I2C_EE_ByteWrite(u8* pBuffer, u8 WriteAddr);
void I2C_EE_PageWrite(u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite);
void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite);
void I2C_EE_BufferRead(u8* pBuffer, u8 ReadAddr, u16 NumByteToRead);
void I2C_EE_WaitEepromStandbyState(void);

extern u16 EEPROM_ADDRESS;

#define IIC1_SCL_PORT  	GPIOB
#define IIC1_SCL_PIN  	GPIO_Pin_6

#define IIC1_SDA_PORT  	GPIOB
#define IIC1_SDA_PIN  	GPIO_Pin_7

#define IIC1_SCL_HIGH() GPIO_WriteBit(IIC1_SCL_PORT,IIC1_SCL_PIN,Bit_SET)
#define IIC1_SCL_LOW() 	GPIO_WriteBit(IIC1_SCL_PORT,IIC1_SCL_PIN,Bit_RESET)

#define IIC1_SDA_HIGH() GPIO_WriteBit(IIC1_SDA_PORT,IIC1_SDA_PIN,Bit_SET)
#define IIC1_SDA_LOW() 	GPIO_WriteBit(IIC1_SDA_PORT,IIC1_SDA_PIN,Bit_RESET)

#define IIC1_READ_DATA 	GPIO_ReadInputDataBit(IIC1_SDA_PORT,IIC1_SDA_PIN)

void IIC1_Init(void);
void IIC1_Start(void);
void IIC1_Stop(void);
u8 IIC1_Wait_Ack(void);
void IIC1_Ack(void);
void IIC1_NAck(void);
void IIC1_Send_Byte(u8 txd);
u8 IIC1_Read_Byte(unsigned char ack);

int I2C_Write(uint8_t block, uint8_t addr, uint8_t* data, uint8_t len);
int I2C_Read(uint8_t block, uint8_t addr, uint8_t* data, uint32_t len);

#endif
