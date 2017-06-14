/*
 * --------------------
 * Company							: LUOYANG GINGKO TECHNOLOGY CO.,LTD.
 *                      : 洛阳银杏科技有限公司
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
	
	//初始化
	led.initialize();
	key.initialize();
	
	if(!KEY_INPUT)usb_mass.initialize();
	
	
	//判断SD卡是否初始化
	if(SD_Init() != SD_OK){
		
		//初始化失败红灯快闪
		while(1){
			LED_RED_ON;
			for(i = 0;i < 3000000;i++);
			LED_RED_OFF;
			for(i = 0;i < 3000000;i++);
		}
	}
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);              //时钟使能
	
	GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_uInitStructure.GPIO_OType = GPIO_OType_PP;  
	GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_100MHz;  // 100M
	
	GPIO_Init(GPIOG,&GPIO_uInitStructure);                            //GPIO初始化
	
	GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_15;					//设置连接按键的IO端口
  GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_IN;                     //设置端口为输入模式
  GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_100MHz;               //设置速度为第三级
  GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                 //设置输入端口不变化 
  GPIO_Init(GPIOG, &GPIO_uInitStructure);                           //把设置的参数用到结构体
	
	res = f_mount(&fatfs,"0:",1);                                     //挂载SD卡
	if(res != RES_OK){
		
		//挂载失败，绿灯快闪
		while(1){
			LED_GREEN_ON;
			for(i = 0;i < 3000000;i++);
			LED_GREEN_OFF;
			for(i = 0;i < 3000000;i++);
		}
	}
	res = f_open(&fil,"0:/system/sdram.rbf",FA_READ);                 //只读打开文件
	if(res != RES_OK){
		
		//打开失败，蓝灯快闪
		while(1){
			LED_BLUE_ON;
			for(i = 0;i < 3000000;i++);
			LED_BLUE_OFF;
			for(i = 0;i < 3000000;i++);
		}
	}
	res = f_lseek(&fil,0);                                            //将指针移动到第一个位置
	if(res != RES_OK){
		//白色
		LED_RED_ON;
		LED_BLUE_ON;
		LED_GREEN_ON;
		while(1){
		}
	}
	
	//开始升级FPGA程序
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
    res = f_read(&fil,buffer,1024,&counter);                        //读取数据  
		if(res != RES_OK){
			//读取失败，红灯慢闪
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
		 for(i = 0; i < 800; i++);                                       //延时 100us
		 DCLK_OFF;
		 for(i = 0; i < 800; i++);                                       //延时 100us
	}
	
	while(1);
	
}
