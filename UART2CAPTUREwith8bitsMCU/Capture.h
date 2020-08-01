//___________________________________________________________________
//___________________________________________________________________
// Description: Get ADC value (10bit internal)
//  Copyright@: 2019 BY Louis Huang / https://github.com/louisopen/
//   File Name: Capture.h
//Targer Board: MK8002D
//    MCU Body: HT66F317 HT66F318-28ssop
//      Author: Louis Huang
//        Date: 2019/05/18
//     Version: V00 on Hardware V10
//     History:
//___________________________________________________________________
//___________________________________________________________________
#ifndef _CAPTURE_H_
#define _CAPTURE_H_

extern __16_type 	counting;
extern __32_type	capture_val;

extern void Capture_init(), Capture_test();

#endif