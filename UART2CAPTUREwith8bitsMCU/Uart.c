//___________________________________________________________________
//___________________________________________________________________
// Description: UART and RS-485
//  Copyright@: 2019 BY Louis Huang / https://github.com/louisopen/
//  File Name : Uart.c
//Targer Board: MK8002D
//    MCU Body: HT66F317 HT66F318-28ssop
//      Author: Louis Huang
//        Date: 2019/05/18
//     Version: V00 on Hardware V10
//     History:
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"

#define		UCR1_8_N_1     				0x80      //8bits-Data  NONE-Parity 1bit-Stop Format
#define 	UCR1_7_O_1     				0x0B0     //7bits-Data  Odd-Parity  1bit-Stop Format
#define		UCR1_7_E_1     				0x0A0     //7bits-Data  Even-Parity 1bit-Stop Format
#define		UCR1_9_N_1     				0x0C0     //9bits-Data  NONE-Parity 1bit-Stop Format
#define		UCR1_8_O_1    				0x0F0     //8bits-Data  Odd-Parity  1bit-Stop Format
#define		UCR1_8_E_1     				0x0E0     //8bits-Data  Even-Parity 1bit-Stop Format
#define		UCR1_8_N_2     				0x88      //8bits-Data  NONE-Parity 2bits-Stop Format
#define		UCR1_7_O_2     				0x0B8     //7bits-Data  Odd-Parity  2bits-Stop Format
#define		UCR1_7_E_2     				0x0A8     //7bits-Data  Even-Parity 2bits-Stop Format
#define		UCR1_9_N_2     				0x0C8     //9bits-Data  NONE-Parity 2bits-Stop Format
#define		UCR1_8_O_2     				0x0F8     //8bits-Data  Odd-Parity  2bits-Stop Format
#define		UCR1_8_E_2     				0x0E8     //8bits-Data  Even-Parity 2bits-Stop Format
#define		UCR2Data       				0x0E4     //Enable TXEN RXEN BRGH RIE 
#define		UCR2Data1       			0x0Ef     //Enable TXEN RXEN BRGH RIE (TX一直發)
#define		UCR2Data2       			0x0E5     //Enable TXEN RXEN BRGH RIE
//#define		BRGData        				38		  //12Mhz  Baud=19200,BRGH=1,N=38 
//#define		BRGData        				38		  //12Mhz  Baud=9600,BRGH=1,N=38 
//#define		BRGData        				25		  //8Mhz  Baud=19200,BRGH=1,N=25 
#define		BRGData        				51		  //8Mhz  Baud=9600,BRGH=1,N=51 

unsigned char	rx_watchdog;
unsigned char	tx_index;
u8	rx_guide;
u8	tx_guide;
u8	array_uart_txbuff[TX_DATA_MAX];
u8	array_uart_rxbuff[RX_DATA_MAX];

__16_type reg_crc;
u16 calc_crc(u8 *pointer, u8 length);

//___________________________________________________________________
//Function: UART initial
//   INPUT: 
//	  NOTE: TXD RXD enable & initial  
//___________________________________________________________________
void Uart_Init(void)
{
	_pcc2 = 0;	//set tx_enable(RS-485) pin output	
	_pc2 = 0;	//set tx_enable(RS-485) receiver mode
	
	_pcc3 = 0;	//set tx pin output		
	_pcc4 = 1;	//set rx pin intput	(default is input)
	_pc3 = 1;	//set level high TXD (default)
	_pc4 = 1;	//set level high RXD (default)
	_pcpu3 = 1;	//set pull-high for TXD
	_pcpu4 = 1;	//set pull-high for RXD
		
    _ucr1 = UCR1_8_N_1;	//enable UART function,8bits-Data  NONE-Parity 1bit-Stop Format
    _ucr2 = UCR2Data2;  //enable TXEN,RXEN,Hige Speed Baud Rate, Receiver interrupt enable 
	_rie = 1;			//enable RXD
	#ifndef	Debug
   		_brg = BRGData;	//9600 Baud Rate	
	#else
   		_brg = 38;		//9600 Baud Rate	
	#endif
	rx_guide=0;	
	tx_guide=0;	
	_uarte = 1;		//UART interrupt enable
	//_emi  = 1;	//Global enable interrupt 
}
//___________________________________________________________________
//Function: UART PORT DISABLE
//   INPUT: 
//	  NOTE: Disable all function & GPIO  
//___________________________________________________________________
void Uart_off(void)
{
	_rie = 0;	//disable RXD
	//_pcc2 = 1;	//set tx_enable(RS-485) pin input (default)	
	//_pc2 = 1;	//set tx_enable(RS-485) hi level
	
	//_pcc3 = 1;	//set tx pin input (default)
	_pc3 = 1;
	_pcc4 = 1;	//set rx pin input (default)
	//_pc4 = 1;		
}
//___________________________________________________________________
//Function: UART ISR (Only for HT66F318)
//NOTE	  : Data send and receive
//___________________________________________________________________
//#pragma vector UART_ISR @ 0x2C					//for V2 of compiler
//void UART_ISR(void)
void __attribute((interrupt(0x2C)))  UART_ISR()		//for V3 of compiler
{	
	//clear urf flag
	if(_perr || _nf || _ferr || _oerr)	// error found?
	{
	   _acc = _usr;				//read USR to clear error flag 
	   _acc = _txr_rxr;			//read USR to clear error flag
	   rx_guide = 0; 	   	       
	}
	else	// no error found
	{
	    if(_rxif)	//RXD data register is empty (available data)
	    {
			if(rx_guide>=RX_DATA_MAX)	//Check the margin of buffer
			{
				rx_guide = RX_DATA_MAX;	//may be need a time out				
			}
			else
			{
				array_uart_rxbuff[rx_guide] = _txr_rxr; 
				rx_guide++;
				if(rx_guide==RX_DATA_MAX && array_uart_rxbuff[rx_guide-1]==0x0A)	
				{
					uart_rx_success=1;		//Finished for application
				}											
				//if(rx_guide==RX_DATA_MAX || array_uart_rxbuff[2]==(rx_guide-4))	//length of the Modbus slave
				//{
				//	rx_success=1;		//Finished for application
				//}
			}
	   	  	//GCC_NOP();
	   	  	_nop();
	    }
	    else	// half TXD/RXD
	    {
	   		if(_txif)	//TXD data register is empty
	   		{	
	   			if(tx_guide>0)
	 	   		{
	   	   			tx_guide--;
		   			tx_index++;
	   				_txr_rxr = array_uart_txbuff[tx_index];	
	   			}
	   			else
	   			{	
	   				_ucr2 = UCR2Data2;	//Why ?
	   	   			//_rxen=1;
	   	   			//_rie=1;	//enable RXD
	   	   			rx_guide=0;	
		   			_pc2 = 0;	//set tx_enable pin if you need(RS-485)
	   			}
	   			//GCC_NOP();
	   	  		//_nop();
	   		}
	    }
	}	
}
//___________________________________________________________________
//Function: UART RXD main process
//   INPUT: 
//	  NOTE:   
//___________________________________________________________________
void Uart_RXD_Manage(void)
{
	u8 i;
	if(uart_rx_success == 1)	//Is't finished ?
	{
		uart_rx_success = 0;
		if(array_uart_rxbuff[0] == 0x44 && array_uart_rxbuff[RX_DATA_MAX-1]==0x0A)
		{
			switch(array_uart_rxbuff[1])	//functions
			{
				case 0x01:	//if request: 44 01 00 00 00 08 A0 0A
					/*
					for(i=0;i<8;i++)
					{
						array_uart_txbuff[i+3] = Read_EEPROM(i);
					}
					Buffer_Send(8);
					*/
					break;
				case 0x02:	//if request: 44 02 00 01 00 01 A0 0A

					break;
				case 0x03:	//if request: 44 03 01 00 00 01 A0 0A 	ModBus Read ADC
					if(array_uart_rxbuff[2]==0x03)	//Get Capture 
					{	//if request: 44 03 03 00 00 02 A0 0A 	ModBus Read Capture date
						//array_uart_txbuff[3] = 4;
						array_uart_txbuff[4] = capture_val.byte.byte3;
						array_uart_txbuff[5] = capture_val.byte.byte2;
						array_uart_txbuff[6] = capture_val.byte.byte1;	//_tm1ah或許少了兩個bit
						array_uart_txbuff[7] = capture_val.byte.byte0;	//_tm1al
						Buffer_Send03(2*2);
					}
					else
					{	//if request: 44 03 00 00 00 03 A0 0A 	ModBus Read EEPROM
						//for(i=0;i<EEPROM_BUFFER_MAX;i++)
						for(i=0;i<(array_uart_rxbuff[5]*2);i++)
						{
							array_uart_txbuff[i+3] = Read_EEPROM(array_uart_rxbuff[3]+i);
							array_uart_txbuff[i+4] = Read_EEPROM(array_uart_rxbuff[3]+i+1);
							i++;
						}
						Buffer_Send03(array_uart_rxbuff[5]*2);
					}
					break;				
				case 0x06:
					//if request: 44 06 00 00 EE FF A0 0A	ModBus Write EEPROM
					Write_EEPROM(array_uart_rxbuff[3],array_uart_rxbuff[4]);
					Write_EEPROM(array_uart_rxbuff[3]+1,array_uart_rxbuff[5]);
					for(i=0;i<4;i++)
					{
						array_uart_txbuff[i+2] = array_uart_rxbuff[i+2];
					}
					Buffer_Send06(4);
					break;							
				default:	
			
					break;											
			}					
		}
		rx_guide = 0;
	}
	else
	{
		if(rx_watchdog>150)		//50ms ~ 200ms/base on 3KHz
		{
			rx_watchdog=0;
			rx_guide = 0;
			//_ucr2 = UCR2Data2;	//Why ?
		}
	}
}
//___________________________________________________________________
//Function: UART send with the 16 bits data
//   INPUT: 16 bit data 
//	  NOTE: test for demo only
//___________________________________________________________________
void Uart_TXD_Send(u16 tx_data)
{
	tx_guide=9;	//TXD count <= TX_DATA_MAX
	tx_index=0;	//TXD buffer index
	_pc2 = 1;		//set tx_enable pin if you need(RS-485)	
	//_rxen=0;
	//_rie=0;		//disable RXD
	//rx_guide = 0;
	array_uart_txbuff[0]	= 0x44;		//slave ID 'U' is 0x55,'D' is 0x44
	array_uart_txbuff[1]	= 0x01;		//function or command
	array_uart_txbuff[2]	= 0x04;		//length
	array_uart_txbuff[3]	= tx_data/256;	//H byte
	array_uart_txbuff[4]	= tx_data%256;	//L byte
	array_uart_txbuff[5]	= tx_data/256;	//H byte
	array_uart_txbuff[6]	= tx_data%256;	//L byte

	calc_crc(array_uart_txbuff, 7);			//CRC-16 calculation in Modbus
	
	array_uart_txbuff[7]	= reg_crc.u16%256;	//L byte in Modbus
	array_uart_txbuff[8]	= reg_crc.u16/256;	//H byte in Modbus

	_txr_rxr = array_uart_txbuff[0];		//TXR data register is empty				
	tx_guide--;
}
//___________________________________________________________________
//Function: UART send for response of Host.
//   INPUT: function=6
//	  NOTE: follow Modbus & CRC-16
//___________________________________________________________________
void Buffer_Send06(u8 count)
{
	//u8 i;
	if(count>TX_DATA_MAX-4) 
	{	//maybe return error code by Modbus
		return;	
	}
	//tx_guide=9;		//TXD send count <= TX_DATA_MAX
	tx_guide=count+4;	//TXD send count
	tx_index=0;			//TXD buffer index
	_pc2 = 1;			//set tx_enable pin if you need(RS-485)	
	//_rxen=0;
	//_rie=0;			//disable RXD
	//rx_guide = 0;
	array_uart_txbuff[0]	= 0x44;		//slave ID 'U' is 0x55,'D' is 0x44
	array_uart_txbuff[1]	= array_uart_rxbuff[1];		//function or command
	//array_uart_txbuff[2]	= count;	//length

	calc_crc(array_uart_txbuff, count+2);	//CRC-16 calculation in Modbus
	
	array_uart_txbuff[count+2]=reg_crc.u16%256;	//L byte in Modbus
	array_uart_txbuff[count+3]=reg_crc.u16/256;	//H byte in Modbus
		
	_txr_rxr = array_uart_txbuff[0];	//TXR data register is empty				
	tx_guide--;
}
//___________________________________________________________________
//Function: UART send for response of Host.
//   INPUT: function=3
//	  NOTE: follow Modbus & CRC-16
//___________________________________________________________________
void Buffer_Send03(u8 count)
{
	//u8 i;
	if(count>TX_DATA_MAX-5) 
	{
		return;
	}
	//tx_guide=9;		//TXD send count <= TX_DATA_MAX
	tx_guide=count+5;	//TXD send count
	tx_index=0;			//TXD buffer index
	_pc2 = 1;			//set tx_enable pin if you need(RS-485)	
	//_rxen=0;
	//_rie=0;			//disable RXD
	//rx_guide = 0;
	array_uart_txbuff[0]	= 0x44;		//slave ID 'U' is 0x55,'D' is 0x44
	array_uart_txbuff[1]	= array_uart_rxbuff[1];		//function or command
	array_uart_txbuff[2]	= count;	//length

	calc_crc(array_uart_txbuff, count+3);	//CRC-16 calculation in Modbus
	
	array_uart_txbuff[count+3]=reg_crc.u16%256;	//L byte in Modbus
	array_uart_txbuff[count+4]=reg_crc.u16/256;	//H byte in Modbus
		
	_txr_rxr = array_uart_txbuff[0];	//TXR data register is empty				
	tx_guide--;
}
//___________________________________________________________________
//Function: Calculation CRC-16
//   INPUT: buffer, number of counting
//	  NOTE: also Modbus standar.
//___________________________________________________________________
u16 calc_crc(u8 *pointer,u8 length)
{
	u8 i,j;
	reg_crc.u16 = 0xFFFF;
 	for (i = 0; i < length; i++) 
 	{
  		//reg_crc ^= array_uart_txbuff[i];	//array buffer		OK
  		//reg_crc ^= *(pointer+i);			//pointer buffer	OK
  		reg_crc.u16 ^= *pointer++;				//pointer buffer	OK
  		for (j = 0; j < 8; j++) 
  		{
   			if (reg_crc.u16 & 1) 
   			{
   				reg_crc.u16 = reg_crc.u16 >> 1;
    			reg_crc.u16 ^= 0xA001;
   			}
   			else
   			{
   				reg_crc.u16 = reg_crc.u16 >> 1;
   			}
  		}
 	}
 	return reg_crc.u16;
 	//return ((reg_crc & 0xFF00) >> 8)|((reg_crc & 0x0FF) << 8 );	
}