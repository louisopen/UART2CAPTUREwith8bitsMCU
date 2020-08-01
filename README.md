### UART2CAPTUREwith8bitsMCU
HT-IDE3000 V8.02  HT66F318 28ssop

Project Option�i���:HXT,HIRC8M,HIRC12M,HIRC16M,LXT,LIRC 

Useing HT66F318 UART access to GPIO, LED matrix, EEPROM, ADC, I2C...(Same RS-485 driver)
���M�קQ��PC�n��U�F���O�H�s��MCU������EEPROM(64bytes), ADC(8ch 10bits), PWM output(10bit), Capture... 
�����٥i�H����W�[I2C(Hi resolution adc), SPI(OLED display) ���z�LUART 9600,N,8,1 ��ĳ�榡�ѷ�RS-485�q�T��ĳ�榡.

ADC�]�m�����z�LAN0~AN7Ū���~����J,��AVDD,AVDD1/2,AVDD1/4Ū��������J.

Capture(HT66F317)�]�mTP1���J����16bit+16bit counting
Capture(HT66F318)�]�mTP1���J����10bit+16bit counting

* HT-IDE3000 V8.02
![Image](HT-IDE3000_version.jpg)
* HOLTEK C Compiler V3/Assembly
![Image](ProjectCompiler.jpg)
* HT66F318 Config, used 8Mhz X'tal external, VDD/VDDA binding
![Image](ProjectOption1.jpg)
![Image](ProjectOption2.jpg)
![Image](ProjectOption3.jpg)
![Image](ProjectOption4.jpg)
* HT66F318 28ssop Diagram
![Image](CircuitDiagram.jpg)


#### How to test or used:
�Q��PC�q�T�n�󰵬��D�ʤu��, ��ĳ(9600,n,8,1), �榡���RS-485�榡(PC���OCRC�� A0 0A�N��, MCU���X����CRC-16)

* For Example: 
* UART Formate(Get from MCU): 44 03 00 00 00 04 A0 0A   #Ū��EEPROM��}0x0000,4��(�@�p8��bytes)
MCU return�]�p�̤j�C��Ū���|��(8byte) �ҥH���X��: 44 03 08 00 01 02 03 04 05 06 07 CRC CRC

* UART Formate(Write to MCU): 44 06 00 0A EE FF A0 0A   #�g�JEEPROM��}0x000A,��Ƭ�0xEEFF
MCU return: 44 06 00 0A EE FF CRC CRC

* UART Formate(Get from MCU): 44 03 03 00 00 02 A0 0A   #Ū��Capture�q�D0, 1��4��bytes
MCU return Capture: 44 03 04 03 FF FF FF CRC CRC
MCU return Capture: 44 03 04 08 00 00 00 EC 97


#### Other applications:
* UART access to ADC converter(HY3118 24bit ADC) via I2C bus.
* UART access to OLED 16x2 display driver via SPI bus.

