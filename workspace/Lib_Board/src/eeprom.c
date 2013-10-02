/*****************************************************************************
 *
 *   Copyright(C) 2011, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * Embedded Artists AB assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. Embedded Artists AB
 * reserves the right to make changes in the software without
 * notification. Embedded Artists AB also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 *****************************************************************************/

/*
 * NOTE: I2C must have been initialized before calling any functions in this
 * file.
 */

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "lpc17xx_i2c.h"
#include "eeprom.h"
#include <string.h>

/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/

#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

#define I2CDEV LPC_I2C0

#define EEPROM_I2C_ADDR    (0x50)


#define EEPROM_TOTAL_SIZE 4096
#define EEPROM_PAGE_SIZE    32



/******************************************************************************
 * External global variables
 *****************************************************************************/

/******************************************************************************
 * Local variables
 *****************************************************************************/


/******************************************************************************
 * Local Functions
 *****************************************************************************/

static void eepromDelay(void)
{
    volatile int i = 0;

    for (i = 0; i <0x20000; i++);
}

static int I2CRead(uint8_t addr, uint8_t* buf, uint32_t len)
{
	I2C_M_SETUP_Type rxsetup;

	rxsetup.sl_addr7bit = addr;
	rxsetup.tx_data = NULL;	// Get address to read at writing address
	rxsetup.tx_length = 0;
	rxsetup.rx_data = buf;
	rxsetup.rx_length = len;
	rxsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2CDEV, &rxsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}

static int I2CWrite(uint8_t addr, uint8_t* buf, uint32_t len)
{
	I2C_M_SETUP_Type txsetup;

	txsetup.sl_addr7bit = addr;
	txsetup.tx_data = buf;
	txsetup.tx_length = len;
	txsetup.rx_data = NULL;
	txsetup.rx_length = 0;
	txsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2CDEV, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}

/******************************************************************************
 * Public Functions
 *****************************************************************************/



/******************************************************************************
 *
 * Description:
 *    Initialize the EEPROM Driver
 *
 *****************************************************************************/
void eeprom_init (void)
{

}

/******************************************************************************
 *
 * Description:
 *    Read from the EEPROM
 *
 * Params:
 *   [in] buf - read buffer
 *   [in] offset - offset to start to read from
 *   [in] len - number of bytes to read
 *
 * Returns:
 *   number of read bytes or -1 in case of an error
 *
 *****************************************************************************/
int16_t eeprom_read(uint8_t* buf, uint16_t offset, uint16_t len)
{
	uint16_t i;
	uint8_t off[2];

    if (len > EEPROM_TOTAL_SIZE || offset+len > EEPROM_TOTAL_SIZE) {
        return -1;
    }

    off[0] = ((offset >> 8) & 0xff);
    off[1] = (offset & 0xff);

    I2CWrite(EEPROM_I2C_ADDR, off, 2);
    for ( i = 0; i < 0x2000; i++);
    I2CRead(EEPROM_I2C_ADDR, buf, len);


    return len;
}

/******************************************************************************
 *
 * Description:
 *    Write to the EEPROM
 *
 * Params:
 *   [in] buf - data to write
 *   [in] offset - offset to start to write to
 *   [in] len - number of bytes to write
 *
 * Returns:
 *   number of written bytes or -1 in case of an error
 *
 *****************************************************************************/
int16_t eeprom_write(uint8_t* buf, uint16_t offset, uint16_t len)
{
    int16_t written = 0;
    uint16_t wLen = 0;
    uint16_t off = offset;
    uint8_t tmp[EEPROM_PAGE_SIZE+2];

    if (len > EEPROM_TOTAL_SIZE || offset+len > EEPROM_TOTAL_SIZE) {
        return -1;
    }

    wLen = EEPROM_PAGE_SIZE - (off % EEPROM_PAGE_SIZE);
    wLen = MIN(wLen, len);

    while (len) {

        tmp[0] = ((off >> 8) & 0xff);
        tmp[1] = (off & 0xff);
        memcpy(&tmp[2], (void*)&buf[written], wLen);
        I2CWrite(EEPROM_I2C_ADDR, tmp, wLen+2);

        /* delay to wait for a write cycle */
        eepromDelay();

        len     -= wLen;
        written += wLen;
        off     += wLen;

        wLen = MIN(EEPROM_PAGE_SIZE, len);
    }

    return written;
}

