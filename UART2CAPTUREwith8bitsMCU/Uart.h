//___________________________________________________________________
//___________________________________________________________________
// Description: UART TXD/RXD 
//  Copyright@: 2019 BY Louis Huang / https://github.com/louisopen/
//   File Name: uart.h
//Targer Board: MK8002D
//    MCU Body: HT66F317 HT66F318-28ssop
//      Author: Louis Huang
//        Date: 2019/05/18
//     Version: V00 on Hardware V10
//     History:
//___________________________________________________________________
//___________________________________________________________________
#ifndef _UART_H_
#define _UART_H_

#define	RX_DATA_MAX		8
#define	TX_DATA_MAX		16

extern 	unsigned char 	rx_watchdog;
extern	unsigned char 	tx_index;
extern	volatile	u8	rx_guide;
extern	volatile	u8	tx_guide;
extern	volatile	u8	array_uart_txbuff[TX_DATA_MAX];
extern	volatile	u8	array_uart_rxbuff[RX_DATA_MAX];
extern	volatile	__byte_type	uart_flag;
#define rx_success		uart_flag.bits.b0
//#define tx_success		uart_flag.bits.b1
//#define uart_flag2 		uart_flag.bits.b2
//#define uart_flag3 		uart_flag.bits.b3
//#define uart_flag4		uart_flag.bits.b4
//#define uart_flag5	 	uart_flag.bits.b5
//#define uart_flag6		uart_flag.bits.b6
//#define uart_flag7		uart_flag.bits.b7

extern 	u8	isr_temp0;
//___________________________________________________________________
//___________________________________________________________________
void 	Uart_Init(void);
void	Uart_off(void);
void	Uart_RXD_Manage(void);
void	Uart_TXD_Send(u16 tx_data);
void	Buffer_Send03(u8 count), Buffer_Send06(u8 count);
u16 	calc_crc(volatile u8* pointer, u8 length);

#endif


