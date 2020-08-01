//___________________________________________________________________
//___________________________________________________________________
// Description: 系統初始化相關程序
//  Copyright@: 2019 BY Louis Huang / https://github.com/louisopen/
//   File Name: Sys_Init.h
//Targer Board: MK8002D
//    MCU Body: HT66F317 HT66F318-28ssop
//      Author: Louis Huang
//        Date: 2019/05/18
//     Version: V00 on Hardware V10
//     History:
//___________________________________________________________________
//___________________________________________________________________
#ifndef _SYS_INIT_H_
#define _SYS_INIT_H_

#define Vbat_adc 	AN0		//binding _pb0 , AN0=0
#define IO_test 	_pb1
#define Buzzer	 	_pb2
#define LED_fast 	_pb5	//LED flash fast
#define PWMout		_pb3	//pb3 binding TP2(TM2) CTM already
#define Capture		_pa7	//pa7 binding TP1(TM1) PTM already
#define LED_slow 	_pa0	//pa0 not binding TP0(TM0) STM already

extern unsigned char  	count_2sec;
extern __byte_type		system_flag;
#define toggle_led		system_flag.bits.b0
#define toggle_buzzer	system_flag.bits.b1
#define sleep_request	system_flag.bits.b2



void PowerOn_Init(), WDT_ResetInit(), ReadyToHalt();
void GPIO_Init(), Ram_Init(), Task_500ms(), Key_Scan();

//___________________________________________________________________
//___________________________________________________________________
//  HIRC可選頻率有(options HXT or HIRC)
//  4000000，8000000，120000  by hardware option if select HIRC
#define OSC_Frequency		8000000


//-------------SMOD config--------------
//  ______________________________________________________________________________
// | Bit  |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
//  ______________________________________________________________________________
// | Name |  CKS2  |  CKS1  |  CKS0  |  FSTEN |  LTO   |  HTO   | IDLEN  | HLCLK  |
// |______________________________________________________________________________
// | POR  |   0    |   0    |   0    |   0    |   0    |   0    |   1    |   1    |
// |_______________________________________________________________________________
// Bit 7~5 CKS2~CKS0：
// 		000: fSUB (fLXT or fLIRC) 
//		001: fSUB (fLXT or fLIRC) 
//		010: fH/64 
//		011: fH/32 
//		100: fH/16 
//		101: fH/8 
//		110: fH/4 
//		111: fH/2
// Bit 3 LTO：
// 		0：Not ready  
//		1：ready
// Bit 2 HTO：
// 		0：Not ready  
//		1：ready
// Bit 1 IDLEN：IDEL mode control
// 		0：DISABLE  
//		1：ENABLE
// Bit 0 HLCLK：system clock selection
// 		0：fH/2 ~ fH/64 or fSUB  
//		1：fH
#define SMOD_Default	0b11110011  

//#define SETHIRC_8MHZ()	{_cks2 = 1;_cks1 = 1;_cks0 = 1;_fsten = 1;_idlen = 1;_hlclk = 1;}
//#define SETHIRC_12MHZ()	{_cks2 = 1;_cks1 = 1;_cks0 = 1;_fsten = 1;_idlen = 1;_hlclk = 1;}
//#define SETHIRC_16MHZ()	{_cks2 = 1;_cks1 = 1;_cks0 = 1;_fsten = 1;_idlen = 1;_hlclk = 1;}
#define SETHXT()		{_cks2 = 1;_cks1 = 1;_cks0 = 1;_fsten = 1;_idlen = 1;_hlclk = 1;}
//#define SETHXT()		{_fsten = 1;_idlen = 1;_hlclk = 1;}
//#define SETLIRC_32K()	{_cks0 = 0;_fsten = 1;_idlen = 1;_hlclk = 0;}
//#define SETLXT_32768(){_cks0 = 1;_fsten = 1;_idlen = 1;_hlclk = 0;}


//-------------WDT config---------------
//___________________________________________________________________
//Please in Option select WDT clock Source
//if WDT clock Source fs =fsub
//WDT time計算方式:
//WDT time =  2^18/fsub
//example:(max time 周期最長2^18，Source fs=32768) or fs=32K (LIRC)
//WDT time = 2^18/32768= 8s
#define SETWDT_Disable()			{ 	_wdtc =	0B10101000	;	}
#define SETWDTtime8ms()				{	_wdtc =	0B01010000 	;	}// 2^8 /Fs =    8ms
#define SETWDTtime32ms()			{	_wdtc =	0B01010001	;	}// 2^10/Fs =   32ms
#define SETWDTtime128ms()			{	_wdtc =	0B01010010 	;	}// 2^12/Fs =  128ms
#define SETWDTtime512ms()			{	_wdtc =	0B01010011	;	}// 2^14/Fs =  512ms
#define SETWDTtime1024ms()			{	_wdtc =	0B01010100 	;	}// 2^15/Fs = 1024ms
#define SETWDTtime2048ms()			{	_wdtc =	0B01010101	;	}// 2^16/Fs = 2048ms
#define SETWDTtime4096ms()			{	_wdtc =	0B01010110	;	}// 2^17/Fs = 4096ms
#define SETWDTtime8192ms()			{	_wdtc =	0B01010111	;	}// 2^18/Fs = 8192ms



//-------------LVR config---------------
//  ______________________________________________________________________________
// | Bit  |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
//  ______________________________________________________________________________
// | Name |  LVS7  |  LVS6  |  LVS5  |  LVS4  |  LVS3  |  LVS2  |  LVS1  |  LVS0  |
// |______________________________________________________________________________
// | POR  |   0    |   1    |   0    |   1    |   0    |   1    |   0    |   1    |
// |_______________________________________________________________________________
// BIT 7~0  LVS7~LVS0:LVR電壓選擇 (01100110 is default)
// 			01010101:  1.9V     
//			00110011:  2.55V
//			10011001:  3.15V    
//			10101010:  3.8V
//		其他值: MCU復位 ( set 11110000 is disable)
//___________________________________________________________________
#define SETLVR_Voltage1_7()		{	_lvrc = 0B01100110 ;	}	//default on reset
#define SETLVR_Voltage1_9()		{	_lvrc = 0B01010101 ;	}
#define SETLVR_Voltage2_55()	{	_lvrc = 0B00110011 ;	}
#define SETLVR_Voltage3_15()	{	_lvrc = 0B10011001 ; 	}
#define SETLVR_Voltage3_8()		{	_lvrc = 0B10101010 ;	}
#define SETLVR_Disable()		{	_lvrc = 0B11110000 ;	}

//-------------EEPROM config------------
//Setting in EEPROM.h

//-------------Timer config-------------
//Setting in Timer.h


//----------------TBC-------------------
//  ______________________________________________________________________________
// | Bit  |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
//  ______________________________________________________________________________
// | Name |  TBON  |  TBCK  |  TB11  |  TB10  | LXTLP  |  TB02  |  TB01  |  TB00  |
// |______________________________________________________________________________
// | POR  |   0    |   0    |   1    |   1    |   0    |   1    |   1    |   1    |
// |_______________________________________________________________________________
// BIT 7  TBON:TB0和TB1控制位
// 			0:  Disable
//			1:  Enable
// BIT 6  TBCK:選擇ftb時鐘位
// 			0:  fsub
//			1:  fsys/4
// BIT 5~4  TB11~TB10:TimeBase"1"溢出週期
// 			00:  2^12/ftb   01:  2^13/ftb
//			10:  2^14/ftb   11:  2^15/ftb
// BIT 3  LXTLP:LXT低功耗控制位
// 			0:  快速啟動模式
//			1:  低功耗模式
// BIT 2~0  TB02~TB00：TimeBase"0"溢出週期
// 			000:  2^8/ftb    001:  2^9/ftb    010:  2^10/ftb
// 			011:  2^11/ftb   100:  2^12/ftb   101:  2^13/ftb
// 			110:  2^14/ftb   111:  2^15/ftb
#define TimeBase_500ms	0B10100110	//TimeBase0 0.5S, TimeBase1 0.5S
#define TimeBase_1000ms	0B10110111	//TimeBase0 1.0S, TimeBase1 1.0S
#define TimeBase_init()	{	_tbc=TimeBase_500ms; _tb1e=1;	}	//enable TB1 interrupt.
//#define TimeBase_init()	{	_tbc=TimeBase_500ms; _tb0e=1; _tb1e=1;	}	//enable TB0/TB1 interrupt.

//------------Timer module--------------
//---------------PTMnC0-----------------
//TMnC0 (PTM, n=0 or n=1) 10bit for HT66F317 & 10bit HT66F318
//  ______________________________________________________________________________
// | Bit  |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
//  ______________________________________________________________________________
// | Name |  TnPAU |  TnCK2 |  TnCK1 |  TnCK0 |  TnON  |    -   |    -   |    -   |
// |______________________________________________________________________________
// | POR  |   0    |   0    |   0    |   0    |   0    |   0    |   0    |   0    |
// |_______________________________________________________________________________
// BIT 7  TnPAU:TMn計數器暫停控制位
// 			0:  運行
//			1:  暫停
// Bit 6~4 TnCK2~TnCK0: Select TMn Counter clock
//			000: fSYS/4
//			001: fSYS
//			010: fH/16
//			011: fH/64
//			100: fTBC
//			101: fH
//			110: TCKn rising edge clock
//			111: TCKn falling edge clock
// Bit 3 TnON: TMn Counter On/Off Control
//			0: Off
//			1: On
#define TM0C0_Default	0b00110000  //fsub, off

#define TM1C0_Default	0b00110000	//fsub, off

//--------------PTMnC1------------------
//TMnC1 (PTM, n=0 or n=1) for HT66F317 HT66F318
//  ______________________________________________________________________________
// | Bit  |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
//  ______________________________________________________________________________
// | Name |  TnM1  |  TnM0  |  TnIO1 |  TnIO0 |  TnOC  |  TnPOL | TnCAPTS| TnCCLR |
// |______________________________________________________________________________
// | POR  |   0    |   0    |   0    |   0    |   0    |   0    |   0    |   0    |
// |_______________________________________________________________________________
// BIT 7~6  TnM1~TnM0:選擇TMn工作模式位
// 			00:  比較器匹配輸出模式   01:未定義模式
//			10:  PWM模式              11:定時/計數器模式
// BIT 5~4  TnIO1~TnIO0:選擇TPn_0，TPn_1輸出功能位
//			比較匹配輸出模式
// 			00:  無變化          01:  輸出低
//			10:  輸出高          11:  輸出翻轉
//			PWM模式
// 			00:  強制無效狀態    01:  強制有效狀態
//			10:  PWM輸出         11:  未定義
//			計數器/定時模式: 未定義
// BIT 3  TnOC
// 			比較匹配輸出模式     PWM模式
// 			0:  初始低           0:  低有效
//			1:  初始高           1:  高有效
// BIT 2  TnPOL:TPn_0,TPn_1輸出極性控制位
// 			0:  同相
//			1:  反相
// Bit 1 TnCAPTS: TMn capture trigger source select
//			0: From TPn pin
//			1: From TCKn pin
// BIT 0  TnCCLR:選擇TMn計數器清零條件位
// 			0:  TMn比較器P匹配
//			1:  TMn比較器A匹配
#define TM0C1_Default	0b11000001	//working mode for PTM
#define TM0AL_Default	0x48		//CCRP CCRA 10bit
#define TM0AH_Default	0x01       	//10ms
#define TM0RP_Default	0x00		//hi 8bit for ht66f318

#define TM1C1_Default	0b11000001	//working mode for PTM
#define TM1AL_Default	0x48	
#define TM1AH_Default	0x1       	//10ms
#define TM1RPL_Default	0x00		//10bit for ht66f317 318
#define TM1RPH_Default	0x00


//---------------STMnC0-----------------
//TMnC0 (STM, n=0) only for HT66F318
//  ______________________________________________________________________________
// | Bit  |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
//  ______________________________________________________________________________
// | Name |  TnPAU |  TnCK2 |  TnCK1 |  TnCK0 |  TnON  |    -   |    -   |    -   |
// |______________________________________________________________________________
// | POR  |   0    |   0    |   0    |   0    |   0    |   0    |   0    |   0    |
// |_______________________________________________________________________________
// BIT 7  TnPAU:TMn計數器暫停控制位
// 			0:  運行
//			1:  暫停
// Bit 6~4 TnCK2~TnCK0: Select TMn Counter clock
//			000: fSYS/4
//			001: fSYS
//			010: fH/16
//			011: fH/64
//			100: fTBC
//			101: fH
//			110: TCKn rising edge clock
//			111: TCKn falling edge clock
// Bit 3 TnON: TMn Counter On/Off Control
//			0: Off
//			1: On
//#define TM0C0_Default	0b00110000   //fsub,off

//--------------STMnC1---------------
//TMnC1 (STM, n=0) only for HT66F318
//  ______________________________________________________________________________
// | Bit  |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
//  ______________________________________________________________________________
// | Name |  TnM1  |  TnM0  |  TnIO1 |  TnIO0 |  TnOC  |  TnPOL | TnDPX  | TnCCLR |
// |______________________________________________________________________________
// | POR  |   0    |   0    |   0    |   0    |   0    |   0    |   0    |   0    |
// |_______________________________________________________________________________
// BIT 7~6  TnM1~TnM0:選擇TMn工作模式位
// 			00:  比較器匹配輸出模式   01:未定義模式
//			10:  PWM模式              11:定時/計數器模式
// BIT 5~4  TnIO1~TnIO0:選擇TPn_0，TPn_1輸出功能位
//			比較匹配輸出模式
// 			00:  無變化          01:  輸出低
//			10:  輸出高          11:  輸出翻轉
//			PWM模式
// 			00:  強制無效狀態    01:  強制有效狀態
//			10:  PWM輸出         11:  未定義
//			計數器/定時模式: 未定義
// BIT 3  TnOC
// 			比較匹配輸出模式     PWM模式
// 			0:  初始低           0:  低有效
//			1:  初始高           1:  高有效
// BIT 2  TnPOL:TPn_0,TPn_1輸出極性控制位
// 			0:  同相
//			1:  反相
// Bit 1 TnDPX: TMn PWM period/duty Control
//			0: CCRP - period; CCRA - duty
//			1: CCRP - duty; CCRA - period
// BIT 0  TnCCLR:選擇TMn計數器清零條件位
// 			0:  TMn比較器P匹配
//			1:  TMn比較器A匹配
//#define TM0C1_Default	0b11000001	//STM mode
//#define TM0AL_Default	0x48
//#define TM0AH_Default	0x01
//#define TM0RP_Default	0x00


//--------------CTMnC0---------------
//TMnC0 (CTM, n=2) only for HT66F318
//  ______________________________________________________________________________
// | Bit  |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
//  ______________________________________________________________________________
// | Name |  TnPAU |  TnCK2 |  TnCK1 |  TnCK0 |  TnON  |   -    |   -    |   -    |
// |______________________________________________________________________________
// | POR  |   0    |   0    |   0    |   0    |   0    |   -    |   -    |   -    |
// |_______________________________________________________________________________
// Bit 7 TnPAU: TMn Counter Pause Control
//			0: Run
//			1: Pause
// Bit 6~4 TnCK2~TnCK0: Select TMn Counter clock
//			000: fSYS/4
//			001: fSYS
//			010: fH/16
//			011: fH/64
//			100: fTBC
//			101: fH/8
//			110: TCKn rising edge clock
//			111: TCKn falling edge clock
// Bit 3 TnON: TMn Counter On/Off Control
//			0: Off
//			1: On
#define TM2C0_Default	0b00100000	//TM2 off

//------------TM2C1 16bit CTM-----------
//TMnC1 (CTM, n=2) only for HT66F318
//  ______________________________________________________________________________
// | Bit  |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
//  ______________________________________________________________________________
// | Name |  TnM1  |  TnM0  |  TnIO1 |  TnIO0 |  TnOC  |  TnPOL |  TnDPX | TnCCLR |
// |______________________________________________________________________________
// | POR  |   0    |   0    |   0    |   0    |   0    |   0    |   0    |   0    |
// |_______________________________________________________________________________
// Bit 7~6 TnM1, TnM0: Select TMn Operating Mode
//			00: Compare Match Output Mode
//			01: Undefined
//			10: PWM Mode
//			11: Timer/Counter Mode
// Bit 5~4 TnIO1, TnIO0: Select TPn output function
//			Compare Match Output Mode
//			00: No change
//			01: Output low
//			10: Output high
//			11: Toggle output
//			PWM Mode
//			00: PWM Output inactive state
//			01: PWM Output active state
//			10: PWM output
//			11: Undefined
//			Timer/Counter Mode
//			Unused
// Bit 3 TnOC: TPn Output control bit
//			Compare Match Output Mode
//			0: Initial low
//			1: Initial high
//			PWM Mode
//			0: Active low
//			1: Active high
// Bit 2 TnPOL: TPn Output polarity Control
//			0: Non-invert
//			1: Invert
// Bit 1 TnDPX: TMn PWM period/duty Control
//			0: CCRP - period; CCRA - duty
//			1: CCRP - duty; CCRA - period
// Bit 0 TnCCLR: Select TMn Counter clear condition
//			0: TMn Comparatror P match
//			1: TMn Comparatror A match
#define TM2C1_Default	0xC1	//CTM mode
#define TM2AL_Default	0x48
#define TM2AH_Default	0x01
#define TM2RP_Default	0x00
/*
#define	TM0STM_10MS()	{ 	_tm0c0=TM0C0_Default;\
							_tm0c1=TM0C1_Default;\ 
							_tm0al=TM0AL_Default;\ 
							_tm0ah=TM0AH_Default;\ 
							_t0ae=1;\ 
							_tm0rp=TM0RP_Default;\ 
							_t0pe=0;\ 	
						}
*/
/*												
#define	TM0PTM_10MS()	{ 	_tm1c0=TM1C0_Default;\
							_tm1c1=TM1C1_Default;\
							_tm1al=TM1AL_Default;\ 
							_tm1ah=TM1AH_Default;\
							_t1ae=1;\
							_tm1rpl=TM1RPL_Default;\
							_tm1rph=TM1RPH_Default;\	
							_t1pe=0;\	
						}
*/	
/*				
#define	TM1PTM_10MS()	{ 	_tm1c0=TM1C0_Default;\
							_tm1c1=TM1C1_Default;\
							_tm1al=TM1AL_Default;\ 
							_tm1ah=TM1AH_Default;\
							_t1ae=1;\
							_tm1rpl=TM1RPL_Default;\
							_tm1rph=TM1RPH_Default;\	
							_t1pe=0;\	
						}

#define	TM2CTM_10MS()	{ 	_tm2c0=TM2C0_Default;\
							_tm2c1=TM2C1_Default;\
							_tm2al=TM2AL_Default;\
							_tm2ah=TM2AH_Default;\
							_t2ae=1;\
							_tm2rp=TM2RP_Default;\
							_t2pe=0;\	
						}
*/

#endif
