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


/******************************************************************************
 * Includes
 *****************************************************************************/

#include "lpc17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_adc.h"
#include "board.h"




/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/

#define RF_DEV      ((LPC_UART_TypeDef *)LPC_UART3)

#define RX_BUF_SIZE (256)


/******************************************************************************
 * External global variables
 *****************************************************************************/

/******************************************************************************
 * Local variables
 *****************************************************************************/


/*
 * UART receive buffer
 */

static uint8_t rxqIn = 0;
static uint8_t rxqOut = 0;
static uint8_t rxq[RX_BUF_SIZE];

/******************************************************************************
 * Local Functions
 *****************************************************************************/

static void rxq_put(uint8_t data)
{
  // full
  if (rxqOut == (rxqIn + 1) % RX_BUF_SIZE) {
    return;
  }
  rxq[rxqIn] = data;
  rxqIn = (rxqIn + 1) % RX_BUF_SIZE;
}

static uint8_t rxq_get(void)
{
  uint8_t d = 0;
  // empty
  if (rxqIn == rxqOut) {
    return 0;
  }

  d = rxq[rxqOut];
  rxqOut = (rxqOut + 1) % RX_BUF_SIZE;

  return d;
}

static uint8_t rxq_isEmpty(void)
{
  return (rxqIn == rxqOut);
}

static void rf_uartRecvCb(void)
{
  uint8_t data = 0;
  uint32_t len = 0;

  while(1) {
      len = UART_Receive(RF_DEV, &data, 1, NONE_BLOCKING);

      if (len) {
        rxq_put(data);
      }

      // there is no more data
      else {

        break;
      }
  }
}


/******************************************************************************
 * Public Functions
 *****************************************************************************/


/******************************************************************************
 *
 * Description:
 *   Initialize the UART connected to the XBee/Jennic module
 *
 *****************************************************************************/
void rf_uart_init(void)
{
  PINSEL_CFG_Type PinCfg;
  UART_CFG_Type uartCfg;

  /* Initialize UART3 pin connect */
  PinCfg.Funcnum = 2;
  PinCfg.Portnum = 0;
  PinCfg.Pinnum = 0;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 1;
  PINSEL_ConfigPin(&PinCfg);

  uartCfg.Baud_rate = 9600;
  uartCfg.Databits = UART_DATABIT_8;
  uartCfg.Parity = UART_PARITY_NONE;
  uartCfg.Stopbits = UART_STOPBIT_1;

  UART_Init(RF_DEV, &uartCfg);

  UART_SetupCbs(RF_DEV, 0, &rf_uartRecvCb);

  UART_TxCmd(RF_DEV, ENABLE);

  UART_IntConfig(RF_DEV, UART_INTCFG_RBR, ENABLE);
  NVIC_EnableIRQ(UART3_IRQn);
}

/******************************************************************************
 *
 * Description:
 *   Send data to the XBee/Jennic module.
 *
 * Params:
 *   [in] txbuf - buffer containing data to send
 *   [in] buflen - number of bytes to send
 *   [in] flag - indicates blocking or non-blocking transfer
 *
 * Returns:
 *   Number of bytes sent.
 *
 *****************************************************************************/
uint32_t rf_uart_send(uint8_t *txbuf, uint32_t buflen,
    TRANSFER_BLOCK_Type flag)
{
  return UART_Send(RF_DEV, txbuf, buflen, flag);
}

/******************************************************************************
 *
 * Description:
 *   Send a null-terminates string to the XBee/Jennic.
 *
 * Params:
 *   [in] str - the string to send
 *
 * Returns:
 *   Number of bytes sent.
 *
 *****************************************************************************/
uint32_t rf_uart_sendString(uint8_t *str)
{
  return UART_SendString(RF_DEV, str);
}

/******************************************************************************
 *
 * Description:
 *   Receive a block of data from the Xbee/Jennic module.
 *
 * Params:
 *   [in] rxbuf - pointer to receive buffer
 *   [in] buflen - length of buffer
 *
 * Returns:
 *   Number of bytes sent.
 *
 *****************************************************************************/
uint32_t rf_uart_receive(uint8_t *buf, uint32_t buflen)
{
  uint32_t pos = 0;

  while(buflen > 0 && !rxq_isEmpty()) {
    buf[pos] = rxq_get();
    pos++;
    buflen--;
  }

  return pos;
}

uint8_t rf_uart_recvIsEmpty(void)
{
  return rxq_isEmpty();
}

void UART3_IRQHandler(void)
{
  UART3_StdIntHandler();
}

void ssp1_init(void)
{
  SSP_CFG_Type SSP_ConfigStruct;
  PINSEL_CFG_Type PinCfg;

  /*
   * Initialize SPI pin connect
   * P0.7 - SCK;
   * P0.8 - MISO
   * P0.9 - MOSI
   * P2.2 - SSEL - used as GPIO
   */
  PinCfg.Funcnum = 2;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Portnum = 0;
  PinCfg.Pinnum = 7;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 8;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 9;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Funcnum = 0;
  PinCfg.Portnum = 2;
  PinCfg.Pinnum = 2;
  PINSEL_ConfigPin(&PinCfg);

  SSP_ConfigStructInit(&SSP_ConfigStruct);

  // Initialize SSP peripheral with parameter given in structure above
  SSP_Init(LPC_SSP1, &SSP_ConfigStruct);

  // Enable SSP peripheral
  SSP_Cmd(LPC_SSP1, ENABLE);

}

void i2c2_init(void)
{
  PINSEL_CFG_Type PinCfg;

  /* Initialize I2C2 pin connect */
  PinCfg.Funcnum = 2;
  PinCfg.Pinnum = 10;
  PinCfg.Portnum = 0;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 11;
  PINSEL_ConfigPin(&PinCfg);

  // Initialize I2C peripheral
  I2C_Init(LPC_I2C2, 100000);

  /* Enable I2C1 operation */
  I2C_Cmd(LPC_I2C2, ENABLE);
}

