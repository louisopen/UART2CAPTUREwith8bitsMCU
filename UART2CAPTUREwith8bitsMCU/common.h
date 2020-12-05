//___________________________________________________________________
//___________________________________________________________________
// Description: This Application
//  Copyright@: 2019 BY Louis Huang / https://github.com/louisopen/
//   File Name: common.h
//Targer Board: MK8002D
//    MCU Body: HT66F317 HT66F318-28ssop
//      Author: Louis Huang
//        Date: 2019/05/18
//     Version: V00 on Hardware V10
//     History:
//___________________________________________________________________
//___________________________________________________________________
#ifndef _COMMON_H_
#define _COMMON_H_

#include "HT66F318.h"
#include "typedef.h"
#include "EEPROM.h"
#include "Sys_Init.h"
#include "Uart.h"
#include "Interrupt.h"
#include "Capture.h"

#define TB0_int_flag	interrupt_flag.bits.b0
#define TB1_int_flag	interrupt_flag.bits.b1
#define edge_int_flag	interrupt_flag.bits.b2
#define uart_rx_success interrupt_flag.bits.b3

#define toggle_led		system_flag.bits.b0
#define toggle_buzzer	system_flag.bits.b1
#define sleep_request	system_flag.bits.b2

#define Vbat_adc 	AN0		//binding _pb0 , AN0=0
#define IO_test 	_pb1
#define Buzzer	 	_pb2
#define LED_fast 	_pb5	//LED flash fast
#define PWMout		_pb3	//pb3 binding TP2(TM2) CTM already
#define Capture		_pa7	//pa7 binding TP1(TM1) PTM already
#define LED_slow 	_pa0	//pa0 not binding TP0(TM0) STM already


#endif
