/*
 * --------------------
 * Company							: LUOYANG GINGKO TECHNOLOGY CO.,LTD.
 *                      : �������ӿƼ����޹�˾
 * --------------------
 * Project Name					: iCore3
 * Description					: iCore3_sd_iap_fpga
 * --------------------
 * Tool Versions				: uVision V5.17.0.0
 * Target Device				: STM32F407IGT6
 * --------------------
 * Engineer							: ysloveivy.
 * Revision							: 1.0
 * Created Date					: 2016.01.06
 * --------------------
 * Engineer							:
 * Revision							:
 * Modified Date				:
 * --------------------
 * Additional Comments	:
 *
 * --------------------
 */
//-----------------------include--------------------------//
#include "..\fwlib\inc\stm32f4xx_gpio.h"
#include "..\fwlib\inc\stm32f4xx_rcc.h"
#include "..\include\led.h"
#include "..\include\key.h"
#include "..\include\main.h"
#include "stm324xg_eval_sdio_sd.h"
#include "..\fatfs\ff.h"
#include "..\fatfs\diskio.h"
#include "..\include\usb_mass.h"

#include <string.h>

//------------------------define--------------------------//

//-----------------------variable-------------------------//

//------------------Function Prototype--------------------//

//-----------------------Function-------------------------//
/*
 * Name					: main
 * Description	: ---
 * Author				: ysloveivy.
 *
 * History
 * --------------------
 * Rev					: 0.00
 * Date					: 01/06/2016
 * 
 * create.
 * --------------------
 */
int main(void)
{
	int i;
	int k;
	unsigned int counter;
	unsigned long int ncounter = 0;
	unsigned char buffer[1024];
	FIL fil;
	FATFS fatfs;
  static FRESULT res;
	GPIO_InitTypeDef   GPIO_uInitStructure;
	
	for(i = 0;i < 10000000;i++);
	
	//��ʼ��
	led.initialize();
	key.initialize();
	
	if(!KEY_INPUT)usb_mass.initialize();
	
	
	//�ж�SD���Ƿ��ʼ��
	if(SD_Init() != SD_OK){
		
		//��ʼ��ʧ�ܺ�ƿ���
		while(1){
			LED_RED_ON;
			for(i = 0;i < 3000000;i++);
			LED_RED_OFF;
			for(i = 0;i < 3000000;i++);
		}
	}
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);              //ʱ��ʹ��
	
	GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_uInitStructure.GPIO_OType = GPIO_OType_PP;  
	GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_100MHz;  // 100M
	
	GPIO_Init(GPIOG,&GPIO_uInitStructure);                            //GPIO��ʼ��
	
	GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_15;					//�������Ӱ�����IO�˿�
  GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_IN;                     //���ö˿�Ϊ����ģʽ
  GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_100MHz;               //�����ٶ�Ϊ������
  GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                 //��������˿ڲ��仯 
  GPIO_Init(GPIOG, &GPIO_uInitStructure);                           //�����õĲ����õ��ṹ��
	
	res = f_mount(&fatfs,"0:",1);                                     //����SD��
	if(res != RES_OK){
		
		//����ʧ�ܣ��̵ƿ���
		while(1){
			LED_GREEN_ON;
			for(i = 0;i < 3000000;i++);
			LED_GREEN_OFF;
			for(i = 0;i < 3000000;i++);
		}
	}
	res = f_open(&fil,"0:/system/sdram.rbf",FA_READ);                 //ֻ�����ļ�
	if(res != RES_OK){
		
		//��ʧ�ܣ����ƿ���
		while(1){
			LED_BLUE_ON;
			for(i = 0;i < 3000000;i++);
			LED_BLUE_OFF;
			for(i = 0;i < 3000000;i++);
		}
	}
	res = f_lseek(&fil,0);                                            //��ָ���ƶ�����һ��λ��
	if(res != RES_OK){
		//��ɫ
		LED_RED_ON;
		LED_BLUE_ON;
		LED_GREEN_ON;
		while(1){
		}
	}
	
	//��ʼ����FPGA����
	NCONFIG_OFF;
	DCLK_OFF;
	for(i = 0; i < 5000; i++);
	if(NSTATUS == 1)
	{
		LED_RED_ON;
		return 0;       
	}
	for(i = 0;i < 40;i++);
	NCONFIG_ON;
	for(i = 0; i < 40; i++);

	while(ncounter < fil.fsize)
	{
    res = f_read(&fil,buffer,1024,&counter);                        //��ȡ����  
		if(res != RES_OK){
			//��ȡʧ�ܣ��������
			while(1){
				LED_RED_ON;
				for(i = 0;i < 10000000;i++);
				LED_RED_OFF;
				for(i = 0;i < 10000000;i++);
			}
		}
		for(k = 0; k < counter; k++)
		{
		  for(i = 0; i < 8; i++)
		  {
	      if(buffer[k]&0x01)DATA0_ON;
				else DATA0_OFF;
				DCLK_ON;
				buffer[k] >>= 1;
			  DCLK_OFF;
	    }
		  ncounter++;
	  }
  }	
	if(CONFIG_DONE == 1){
		LED_GREEN_ON;
	}else {
		LED_BLUE_ON;
	}
	
	for(i = 0; i < 40; i++)
	{
     DCLK_ON;
		 for(i = 0; i < 800; i++);                                       //��ʱ 100us
		 DCLK_OFF;
		 for(i = 0; i < 800; i++);                                       //��ʱ 100us
	}
	
	while(1);
	
}
