//___________________________________________________________________
//___________________________________________________________________
// Description: 系統初始化相關程序
//  Copyright@: 2019 BY Louis Huang / https://github.com/louisopen/
//   File Name: Interrupt.h
//Targer Board: MK8002D
//    MCU Body: HT66F317 HT66F318-28ssop
//      Author: Louis Huang
//        Date: 2019/05/18
//     Version: V00 on Hardware V10
//     History:
//___________________________________________________________________
//___________________________________________________________________
#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

extern	volatile	__byte_type	interrupt_flag;
#define TB0_int_flag	interrupt_flag.bits.b0
#define TB1_int_flag	interrupt_flag.bits.b1
#define edge_int_flag	interrupt_flag.bits.b2

extern u8	isr_temp0;

#endif
