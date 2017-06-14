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
#include "..\include\key.h"
#include "..\fwlib\inc\stm32f4xx_gpio.h"

//------------------ Function Prototype -------------------//
static int initialize(void);

//-----------------------variable--------------------------//
KEY_T key = {
	.initialize = initialize
};
//--------------------Function-----------------------------//

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
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_15;												//设置连接按键的IO端口
  GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_IN;											//设置端口为输入模式
  GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_100MHz;							//设置速度为第三级
  GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;									//设置输入端口不变化 
  GPIO_Init(GPIOH, &GPIO_uInitStructure);														//把设置的参数用到结构体
	
	return 0;
}
