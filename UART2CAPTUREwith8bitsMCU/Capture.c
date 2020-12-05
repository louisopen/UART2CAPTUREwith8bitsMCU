//___________________________________________________________________
//___________________________________________________________________
// Description: Analog input (10bit)
//  Copyright@: 2019 BY Louis Huang / https://github.com/louisopen/
//   File Name: Capture.c
//Targer Board: MK8002D
//    MCU Body: HT66F317 HT66F318-28ssop
//      Author: Louis Huang
//        Date: 2019/05/18
//     Version: V00 on Hardware V10
//     History:
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"

__16_type 	counting;
__32_type	capture_val;


//___________________________________________________________________
//Function: MuFunction1 ISR
//NOTE	  : PTM1 & PTM2  
//___________________________________________________________________
//#pragma vector MuFunction1_ISR @ 0x10				//for V2 of compiler
//void MuFunction1_ISR(void)
void __attribute((interrupt(0x10)))  MuFunction1_ISR()	//for V3 of compiler
{			
	if(_t1af)	//Capture will get from CCRA
	{
		capture_val.byte.byte0 = _tm1al;	
		capture_val.byte.byte1 = _tm1ah;	//tm1al,h 1024(10bit)
		capture_val.byte.byte2 = counting.byte.byte0;
		capture_val.byte.byte3 = counting.byte.byte1;
		counting.u16=0;

		if(edge_int_flag)	//觀察轉態情形
		{
			edge_int_flag=0;
			IO_test=0;
		}
		else
		{
			edge_int_flag=1;
			IO_test=1;
		}
			
		_t1af = 0;
	}
	if(_t1pf)	//Capture will get from CCRP (每10bit overflow interrupt)
	{
		counting.u16++;		//CCRP count overflow 1024(10bit)
		_t1pf = 0;
	}
}

//___________________________________________________________________
//Function: Initial Capture
//   INPUT: P
//  OUTPUT: 
//	  NOTE:   
//___________________________________________________________________
void Capture_init()
{
	//_pac0=1;
	//_pac4=1;
	//_pac7=1;
	/*
	//Multifunction 0 interrupt, PA0/TP0 input.
	//Timer1 can using STM 16bits (ht66f318 only)
	_tm0c0 = 0B00010000;  	//0001 0000	TM0 Clock = fsys, PT0ON=Off state
	_tm0c1 = 0B01000001;	//0100 0001 Capture mode, P(period) A(duty) match都會產生中斷,input=TP0
	_tm0al = 0x00;			//CCRA比較值設置16bits
	_tm0ah = 0x00;
	_tm0rp = 0x00;				//CCRP有8bit ht66f317/ht66f318
	_t0ae = 1;					//interrupt for CCRA
	_t0pe = 1;					//interrupt for CCRP
	_mf0e = 1;					//Multifunction 0 interrupt enable
	_t0on = 1;
	_t0cp = 1;				//enable PA0 TP0(TMPC.0=1) binding
	*/
	//Multifunction 1 interrupt, PA4/TCK1 input or PA7/TP1 input.
	//Timer1 can using PTM 10bits (ht66f317,ht66f318)
	_tm1c0 = 0B00010000;  	//0001 0000	TM Clock = fsys, PT1ON=Off state
	_tm1c1 = 0B01000001;	//0100 0001 Capture mode, P A match都會產生中斷,input=TP1
	_tm1al = 0x00;			//CCRA比較值設置10bits
	_tm1ah = 0x00;
	_tm1rpl = 0x00;				//CCRP有10bit ht66f317/ht66f318
	_tm1rph = 0x00;				//CCRP有10bit ht66f317/ht66f318
	_t1ae = 1;					//interrupt for CCRA
	_t1pe = 1;					//interrupt for CCRP
	_mf1e = 1;					//Multifunction 1 interrupt enable
	_t1on = 1;
	_t1cp = 1;				//enable PA7 TP1(TMPC.1=1) binding
	//_t1capts = 1;			//select PA4 TCK1 binding,input=TCK1
	//TM2 no Capture
}
//___________________________________________________________________
//Function: Test the Capture
//   INPUT: P
//  OUTPUT: 
//	  NOTE:   
//___________________________________________________________________
void Capture_test()
{
	Capture_init();

}