 /*
 * FILE								: led.c
 * DESCRIPTION				: This file is evc8021 exit driver.
 * Author							: ysloveivy
 * Copyright					:
 *
 * History
 * -------------------
 * Rev								: 0.00
 * Date								: 01/06/2016
 *
 * create.
 * -------------------
 */
 
//----------------------include----------------------------//
#include "..\include\led.h"
#include "..\fwlib\inc\stm32f4xx_gpio.h"

//------------------ Function Prototype ------------------//
static int initialize(void);

//----------------------variable--------------------------//
LED_T led = {
	.initialize = initialize
};
//-------------------Function-----------------------------//

/*
 * Name								: initialize
 * Description				: ---
 * Author							: ysloveivy.
 *
 * History
 * -------------------
 * Rev								: 0.00
 * Date								: 01/06/2016
 * 
 * create.
 * -------------------
 */

static int initialize(void)
{
	GPIO_InitTypeDef   GPIO_uInitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
	GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_uInitStructure.GPIO_OType = GPIO_OType_PP;  
	GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_100MHz;  // 100M
	
	GPIO_Init(GPIOI,&GPIO_uInitStructure);
	
	GPIO_SetBits(GPIOI,GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
	
	return 0;
}
