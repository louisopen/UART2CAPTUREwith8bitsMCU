//___________________________________________________________________
//___________________________________________________________________
// Description: EEPROM read/write/test operation
//  Copyright@: 2019 BY Louis Huang / https://github.com/louisopen/
//   File Name: EEPROM.h
//Targer Board: MK8002D
//    MCU Body: HT66F317 HT66F318-28ssop
//      Author: Louis Huang
//        Date: 2019/05/18
//     Version: V00 on Hardware V10
//     History:
//___________________________________________________________________
//___________________________________________________________________
#ifndef _EEPROM_H_
#define _EEPROM_H_

//EEPROM address define by user
#define	EEPROM_BUFFER_MAX	16
#define	EEPROM_START_ADDR	0x00
#define	EEPROM_year		EEPROM_START_ADDR+1
#define	EEPROM_month	EEPROM_START_ADDR+2
#define	EEPROM_day		EEPROM_START_ADDR+3
#define	EEPROM_hour		EEPROM_START_ADDR+4
#define	EEPROM_minute	EEPROM_START_ADDR+5
#define	EEPROM_second	EEPROM_START_ADDR+6
#define	EEPROM_code		EEPROM_START_ADDR+7

#define	__mkstr(x)	#x
#define _EEPROM_DATA(a,b,c,d,e,f,g,h) \
asm("eeprom_data 	.section	'eeprom'"); \
asm("db\t"	__mkstr(a)); \
asm("db\t"	__mkstr(b)); \
asm("db\t"	__mkstr(c)); \
asm("db\t"	__mkstr(d)); \
asm("db\t"	__mkstr(e)); \
asm("db\t"	__mkstr(f)); \
asm("db\t"	__mkstr(g)); \
asm("db\t"	__mkstr(h));

//___________________________________________________________________
//___________________________________________________________________
extern void Write_EEPROM(unsigned char addr,unsigned char data);
extern unsigned char Read_EEPROM(unsigned char addr);
extern void TEST_EEPROM(u8 eeprom_length);	//For test or Debug

static volatile	unsigned char databuffer[EEPROM_BUFFER_MAX] __attribute__ ((at(0x1F0)));

#endif
