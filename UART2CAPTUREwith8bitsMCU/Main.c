//___________________________________________________________________
//___________________________________________________________________
// Description: Main program
//  Copyright@: 2019 BY Louis Huang / https://github.com/louisopen/
//   File Name: main of Capture
//Targer Board: MK8002D 
//    MCU Body: HT66F318-28ssop
//      Author: Louis Huang
//        Date: 2019/05/18
//     Version: V00 on Hardware V10
//     History:
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"

//___________________________________________________________________
//___________________________________________________________________
//___________________________________________________________________
void main()
{	//like Arduino setup();
	if(_to ==0 || _pdf ==0)		//power up or reset pin normal.
	{	//上電復位或者是正常情況下的非正常復位
		PowerOn_Init();	//第一次上電或正常reset pin 
		WDT_ResetInit();                          								
	}
	else//Watch dog reset 													
	{	//WDT造成溢出的復位
		WDT_ResetInit();	
	}
	//sleep_request=1;					//test sleep request
	TEST_EEPROM(EEPROM_BUFFER_MAX);		//test fill 0,1,2,3,~
	//Uart_TXD_Send(0xabcd);			//test for TXD single 
	Capture_test();						//test Capture
	while(1)	//like Arduino loop() for main loop
	{	
		//GCC_CLRWDT();		//Clear Watchdog
		_clrwdt();			//Clear Watchdog
		Uart_RXD_Manage();	//Received process/check
		if(sleep_request)	//Enter sleep mode ?
		{
 			ReadyToHalt();
		}
		else
		{
			Task_500ms();	//TimeBase Task process/check
			Key_Scan();		
		}
	}
}
