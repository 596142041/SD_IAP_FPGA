 /*
 * FILE								: usb_mass.c
 * DESCRIPTION				: This file is usb_mass file.
 * Author							: XiaomaGee@Gmail.com
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
//---------------- Include files ------------------------//
#include "..\include\usb_mass.h"

//---------------- Function Prototype -------------------//
static int initialize(void);
extern void usb_enable(void);
extern void usb_otg_handle(void);
extern void ep1_in(void);
extern void ep1_out(void);

//---------------- Variable -----------------------------//
 USB_MASS_T usb_mass = {
	 .initialize = initialize
 };
 
//-----------------Function------------------------------//
/*
 * Name								: USB_HP_CAN1_TX_IRQHandler
 * Description				: ---
 * Author							: XiaomaGee.
 *
 * History
 * -------------------
 * Rev								: 0.00
 * Date								: 01/06/2016
 * 
 * create.
 * -------------------
 */
void OTG_HS_IRQHandler(void)
{
  usb_otg_handle();
}
/*
 * Name								: USB_LP_CAN1_RX0_IRQHandler
 * Description				: ---
 * Author							: XiaomaGee.
 *
 * History
 * -------------------
 * Rev								: 0.00
 * Date								: 01/06/2016
 * 
 * create.
 * -------------------
 */
void OTG_HS_EP1_IN_IRQHandler(void)
{
  ep1_in();
}
void OTG_HS_EP1_OUT_IRQHandler(void)
{
  ep1_out();
}
/*
 * Name								: initialize
 * Description				: ---
 * Author							: XiaomaGee.
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
    usb_enable();
	
		return 0;
}
