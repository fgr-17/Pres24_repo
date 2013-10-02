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

#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_can.h"
#include <string.h>
#include <stdio.h>

#include "board.h"
#include "time.h"
#include "oled.h"
#include "rgb.h"
#include "trimpot.h"
#include "pca9532.h"
#include "light.h"
#include "rfpt.h"


/******************************************************************************
 * Typedefs and defines
 *****************************************************************************/

static rfpt_callb_t callbacks = {
    NULL,
    NULL,
    NULL,
    NULL
};

/******************************************************************************
 * Local variables
 *****************************************************************************/

static uint32_t msTicks = 0;


/******************************************************************************
 * Local functions
 *****************************************************************************/

/******************************************************************************
 * Public functions
 *****************************************************************************/


uint32_t getMsTicks(void)
{
  return msTicks;
}

void SysTick_Handler(void) {
  msTicks++;
}

/****************************************************************
 * 							main()								*
 ****************************************************************/
int main (void)
{

  SysTick_Config(SystemCoreClock / 1000);

  time_init();
  // ssp1_init();
  //i2c2_init();

  //oled_init();
  //pca9532_init();
  //rgb_init();
  // trimpot_init();

//  light_init();
//  light_enable();
//  light_setRange(LIGHT_RANGE_4000);

  // oled_clearScreen(OLED_COLOR_WHITE);

  // oled_putString(1, 1, (uint8_t*)"XBee Node", OLED_COLOR_BLACK, OLED_COLOR_WHITE);

  rf_uart_init();

  Timer0_Wait(2000);
  rf_init(0, &callbacks);


  while(1) {
    rf_task();
  }

}


void check_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while(1);
}

