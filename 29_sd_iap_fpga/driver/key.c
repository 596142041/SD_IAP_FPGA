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
	GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_15;												//�������Ӱ�����IO�˿�
  GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_IN;											//���ö˿�Ϊ����ģʽ
  GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_100MHz;							//�����ٶ�Ϊ������
  GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;									//��������˿ڲ��仯 
  GPIO_Init(GPIOH, &GPIO_uInitStructure);														//�����õĲ����õ��ṹ��
	
	return 0;
}
