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
extern	u8	rx_guide;
extern	u8	tx_guide;
extern	u8	array_uart_txbuff[TX_DATA_MAX];
extern	u8	array_uart_rxbuff[RX_DATA_MAX];

//___________________________________________________________________
//___________________________________________________________________
extern void Uart_Init(void);
extern void	Uart_off(void);
extern void	Uart_RXD_Manage(void);
extern void	Uart_TXD_Send(u16 tx_data);
extern void	Buffer_Send03(u8 count), Buffer_Send06(u8 count);
extern u16 	calc_crc(u8 *pointer, u8 length);

#endif


