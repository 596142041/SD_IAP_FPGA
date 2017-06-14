 /*
 * FILE								: usb_mass.h
 * DESCRIPTION				: This file is iHMI43 usb_mass driver file header.
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
#ifndef __usb_mass_h__
#define __usb_mass_h__

//-----------------Include files-------------------------//
 

//----------------- Define ------------------------------//
 

//----------------- Typedef -----------------------------//
typedef struct{
	int (* initialize)(void);
	 
}USB_MASS_T;

//---------------- Extern -------------------------------//

extern USB_MASS_T usb_mass;

#endif //__usb_mass_h__
