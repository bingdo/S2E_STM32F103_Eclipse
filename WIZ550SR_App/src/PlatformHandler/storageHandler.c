/*
 * storageHandler.c
 *
 *  Created on: 2014. 9. 16.
 *      Author: Raphael Kwon
 */


#include <string.h>
#include "storageHandler.h"
#include "flashHandler.h"
#include "i2cHandler.h"
#include "eepromHandler.h"

#if !defined(MULTIFLASH_ENABLE)
#define BLOCK_SIZE	FLASH_PAGE_SIZE
//#define CONFIG_PAGE_ADDR	0x801F800	// Page126,127	(STM32103RBT6, the last page of 128kB on-chip flash, 2kB size)
#endif

int read_storage(uint8_t isConfig, void *data, uint16_t size)
{
#if !defined(EEPROM_ENABLE)
	uint32_t address;

	if(isConfig == 1) {
#if !defined(MULTIFLASH_ENABLE)
		address = BLOCK_SIZE + CONFIG_PAGE_ADDR;
#else
		address = flash.flash_page_size + flash.config_page_addr;
#endif
	}
	else {
#if !defined(MULTIFLASH_ENABLE)
		address = 0x00000000 + CONFIG_PAGE_ADDR;
#else
		address = 0x00000000 + flash.config_page_addr;
#endif
	}

	return read_flash(address, data, size);
#else

#if defined(I2CPERI_ENABLE)
	int i;
	uint8_t addr;
	uint8_t Receive_Data[EEPROM_BLOCK_SIZE];

	if(size > EEPROM_BLOCK_SIZE)
		size = EEPROM_BLOCK_SIZE;

	memset(&Receive_Data[0], 0x00, EEPROM_BLOCK_SIZE);

	addr = 0x00;

	if(isConfig == 0)
		EEPROM_ADDRESS = EEPROM_Block0_ADDRESS;
	else
		EEPROM_ADDRESS = EEPROM_Block1_ADDRESS;

	/* Read from I2C EEPROM from EEPROM_ReadAddress1 */
	I2C_EE_BufferRead(&Receive_Data[0], addr, size);

	memcpy(data, &Receive_Data[0], size);

#if 0
    printf("[DB App R0x%.2X] ", EEPROM_ADDRESS);
	for(i=0; i<162; i++)
		printf("0x%.2X ",Receive_Data[i]);
	printf("\r\n");
#endif
	delay_ms(100);
	delay_ms(100);
	delay_ms(50);

	return 0;
#else
	int ret=0, i;
	uint8_t Receive_Data[EEPROM_BLOCK_SIZE];
	uint16_t address;

	if(size > EEPROM_BLOCK_SIZE)
		size = EEPROM_BLOCK_SIZE;

	memset(&Receive_Data[0], 0x00, EEPROM_BLOCK_SIZE);

	if(isConfig == 0)
		address = 0x00;
	else
		address = 0x00+EEPROM_BLOCK_SIZE;

	EE24AAXX_Read(address, &Receive_Data[0], size);

	memcpy(data, &Receive_Data[0], size);

#if 0
    printf("[DB App R0x%.2X] ", address);
	for(i=0; i<162; i++)
		printf("0x%.2X ",Receive_Data[i]);
	printf("\r\n");
#endif
	delay_ms(100);
	delay_ms(100);
	delay_ms(50);

	return ret;
#endif

#endif
}

int write_storage(uint8_t isConfig, void *data, uint16_t size)
{
#if !defined(EEPROM_ENABLE)
	uint32_t address;

	if(isConfig == 1) {
#if !defined(MULTIFLASH_ENABLE)
		address = BLOCK_SIZE + CONFIG_PAGE_ADDR;
#else
		address = flash.flash_page_size + flash.config_page_addr;
#endif
	}
	else {
#if !defined(MULTIFLASH_ENABLE)
		address = 0x00000000 + CONFIG_PAGE_ADDR;
#else
		address = 0x00000000 + flash.config_page_addr;
#endif
	}

	erase_flash_page(address);
	return write_flash(address, data, size);
#else

#if defined(I2CPERI_ENABLE)
	uint8_t addr;
	uint8_t Transmit_Data[EEPROM_BLOCK_SIZE];

	memset(&Transmit_Data[0], 0x00, EEPROM_BLOCK_SIZE);
	memcpy(&Transmit_Data[0], data, size);

	if(size > EEPROM_BLOCK_SIZE)
		size = EEPROM_BLOCK_SIZE;

	addr = 0x00;

	if(isConfig == 0)
		EEPROM_ADDRESS = EEPROM_Block0_ADDRESS;
	else
		EEPROM_ADDRESS = EEPROM_Block1_ADDRESS;

	/* Write on I2C EEPROM from EEPROM_WriteAddress1 */
	I2C_EE_BufferWrite(&Transmit_Data[0], addr, size);

#if 0
	int j;
	printf("\r\n");
    printf("[DB App W0x%.2X] ", EEPROM_ADDRESS);
	for(j=0; j<162; j++)
		printf("0x%.2X ",Transmit_Data[j]);
	printf("\r\n");
#endif
	delay_ms(100);
	delay_ms(100);
	delay_ms(50);

	return 0;
#else
	int ret=0;
	uint8_t Transmit_Data[EEPROM_BLOCK_SIZE];
	uint16_t address;

	memset(&Transmit_Data[0], 0x00, EEPROM_BLOCK_SIZE);
	memcpy(&Transmit_Data[0], data, size);

	if(size > EEPROM_BLOCK_SIZE)
		size = EEPROM_BLOCK_SIZE;

	if(isConfig == 0)
		address = 0x00;
	else
		address = 0x00+EEPROM_BLOCK_SIZE;

	EE24AAXX_Write(address, &Transmit_Data[0], size);

#if 0
	int j;
	printf("\r\n");
    printf("[DB App W0x%.2X] ", address);
	for(j=0; j<162; j++)
		printf("0x%.2X ",Transmit_Data[j]);
	printf("\r\n");
#endif
	delay_ms(100);
	delay_ms(100);
	delay_ms(50);

	return ret;
#endif

#endif
}
