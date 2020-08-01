//___________________________________________________________________
//___________________________________________________________________
// Description: Internal EEPROM read/write operation
//  Copyright@: 2019 BY Louis Huang / https://github.com/louisopen/
//   File Name: EEPROM.c
//Targer Board: MK8002D
//    MCU Body: HT66F317 HT66F318-28ssop
//      Author: Louis Huang
//        Date: 2019/05/18
//     Version: V00 on Hardware V10
//     History: Inedx used iar1(mp1), bank1
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"


//___________________________________________________________________
//Function: Read from EEPROM internal
//   INPUT: address
//  OUTPUT: data
//	  NOTE:   
//___________________________________________________________________
unsigned char Read_EEPROM(unsigned char addr)
{
	u8 rdata,tm_emi;
	tm_emi = _emi;
	_emi = 0;
	_eea = addr;				//EEPROM address b5~b0 internal
	_bp = 1;
	_mp1 = 0x40;
	//_mp1h = 1;
	//_mp1l = 0x40;
	
	_iar1 |=0x2;				//enable RDEN (read enable)
	_iar1 |=0x1;				//active READ 
	while((_iar1 & 0x01) !=0);	//wait read end
	rdata = _eed;				//EEPROM data
	
	_iar1 &= 0xfD;				//disable RDEN	

	_bp = 0;		//important 
	_emi = tm_emi;
	return (rdata);
}
//___________________________________________________________________
//Function: Write to EEPROM internal
//   INPUT: address/data
//  OUTPUT: none
//	  NOTE:   
//___________________________________________________________________
void Write_EEPROM(unsigned char addr,unsigned char data)
{
	u8 tm_emi;
	tm_emi = _emi;
	_emi = 0;	
	_eea = addr;				//EEPROM address bit 5 ~ bit 0 internal
	_eed = data;				//EEPROM data bit 7 ~ bit 0 internal
	_bp = 1;					//bank 1
	_mp1 = 0x40;				//index mp1
	//_mp1h = 1;
	//_mp1l = 0x40;

	_iar1	|=	0x8;			//enable WREN (write enable)
	_iar1	|=	0x4;			//active write 
	//GCC_NOP();
	_nop();
	while((_iar1 & 0x04) !=0);	//wait write end
	
	_iar1 &= 0xf7;				//disable WREN	
   
	_bp = 0;		//important
	_emi = tm_emi;	
}
//___________________________________________________________________
//Function: Test Read/Write with internal EEPROM
//   INPUT: eeprom_length buffer length
//  OUTPUT: none
//	  NOTE: Demo Read / Write internal EEPROM only 
//___________________________________________________________________
//volatile	unsigned char databuffer[EEPROM_BUFFER_MAX] __attribute__ ((at(0x1F0)));
//static volatile	unsigned char databuffer[EEPROM_BUFFER_MAX] __attribute__ ((at(0x1F0)));
void TEST_EEPROM(u8 eeprom_length)	//auto fill all it
{
	//volatile	u8	datatemp[64],i;
	volatile u8 i;
	//_bp = 1;
	for(i=0;i<eeprom_length;i++)
	{
		Write_EEPROM(i,i);		//write to EEPROM address/data 0,1,2,3,~,15
	}
	for(i=0;i<eeprom_length;i++)
	{
		databuffer[i] = Read_EEPROM(i);	//Read back from EEPROM
		//array_uart_txbuff[i]=Read_EEPROM(i);
	}	
	GCC_NOP();		//Break here for debug-watch
	//_bp = 0;		//important
}
