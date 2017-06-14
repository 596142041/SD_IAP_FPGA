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

#ifndef __led_h__
#define __led_h__

//-----------------define-------------------------------//
#define LED_RED_OFF GPIO_SetBits(GPIOI,GPIO_Pin_5)
#define LED_RED_ON  GPIO_ResetBits(GPIOI,GPIO_Pin_5)

#define LED_GREEN_OFF GPIO_SetBits(GPIOI,GPIO_Pin_6)
#define LED_GREEN_ON  GPIO_ResetBits(GPIOI,GPIO_Pin_6)

#define LED_BLUE_OFF GPIO_SetBits(GPIOI,GPIO_Pin_7)
#define LED_BLUE_ON  GPIO_ResetBits(GPIOI,GPIO_Pin_7)

//-----------------Include files-------------------------//

//----------------- Typedef------------------------------//
typedef struct {
	int (* initialize)(void);
}LED_T;

//----------------- Extern ------------------------------//
extern LED_T led;

#endif //__led_h__

