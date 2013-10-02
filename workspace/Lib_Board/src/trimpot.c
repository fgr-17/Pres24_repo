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

#include "lpc17xx_gpio.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "trimpot.h"

/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/

/******************************************************************************
 * External global variables
 *****************************************************************************/

/******************************************************************************
 * Local variables
 *****************************************************************************/

/******************************************************************************
 * Local Functions
 *****************************************************************************/

/******************************************************************************
 * Public Functions
 *****************************************************************************/

/******************************************************************************
 *
 * Description:
 *    Initialize trimming potentiometer
 *
 *****************************************************************************/
void trimpot_init (void)
{
  PINSEL_CFG_Type PinCfg;

  /*
   * Init ADC pin connect
   * AD0.0 on P0.23
   */
  PinCfg.Funcnum = 1;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Pinnum = 23;
  PinCfg.Portnum = 0;
  PINSEL_ConfigPin(&PinCfg);

  /* Configuration for ADC :
   *  Frequency at 0.2Mhz
   *  ADC channel 0, no Interrupt
   */
  ADC_Init(LPC_ADC, 200000);
  ADC_IntConfig(LPC_ADC,ADC_CHANNEL_0,DISABLE);
  ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_0,ENABLE);
}


/******************************************************************************
 *
 * Description:
 *    Read value from the trimpot
 *
 *****************************************************************************/
uint16_t trimpot_read (void)
{

  ADC_StartCmd(LPC_ADC,ADC_START_NOW);
  //Wait conversion complete
  while (!(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_0,ADC_DATA_DONE)));

  return ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0);
}
