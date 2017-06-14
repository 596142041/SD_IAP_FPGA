/*
 * FILE								: led.h
 * DESCRIPTION				: this file is for led.c
 * Author							: ysloveivy
 * Copyright					:
 *
 * History
 * --------------------
 * Rev								: 0.00
 * Date								: 01/06/2016
 *
 * create.
 * --------------------
 */

#ifndef __key_h__
#define __key_h__

//------------------define-------------------------------//

#define KEY_INPUT  GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_15)

//-----------------Include files-------------------------//

//----------------- Typedef------------------------------//
typedef struct {
	int (* initialize)(void);
}KEY_T;

//----------------- Extern ------------------------------//
extern KEY_T key;

#endif //__led_h__


