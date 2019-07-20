//___________________________________________________________________
//___________________________________________________________________
// Description: 系統初始化相關程序
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : sys_init.h
//Targer Board: 
//   MCU      : HT66F317 HT66F318
//   Author   : Louis Huang
//   Date     : 2019/07/20
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________
#ifndef SYS_INIT_H_
#define SYS_INIT_H_

void fun_PowerOnInit();
void fun_WDT_ResetInit();
void GPIO_Init();
void fun_RamInit();
void fun_PrepareToHalt();


//@@@@@@@@@@@@@@@@@@@@@@@@@@@ 系統基礎設定 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  HIRC可選頻率有(options HXT or HIRC)
//  4000000，8000000，120000  by hardware option if select HIRC
#define OSC_Frequency		8000000


//					@-------------SMOD config--------------@
//  ______________________________________________________________________________
// | Bit  |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
//  ______________________________________________________________________________
// | Name |  CKS2  |  CKS1  |  CKS0  |  FSTEN |  LTO   |  HTO   | IDLEN  | HLCLK  |
// |______________________________________________________________________________
// | POR  |   0    |   0    |   0    |   0    |   0    |   0    |   1    |   1    |
// |_______________________________________________________________________________
// Bit 7~5 CKS2~CKS0：
// 000: fSUB (fLXT or fLIRC) 001: fSUB (fLXT or fLIRC) 010: fH/64 011: fH/32 100: fH/16 101: fH/8 110: fH/4 111: fH/2
// Bit 3 LTO：
// 	0：Not ready  1：ready
// Bit 2 HTO：
// 	0：Not ready  1：ready
// Bit 1 IDLEN：IDEL mode control
// 	0：DISABLE  1：ENABLE
// Bit 0 HLCLK：system clock selection
// 	0：fH/2 ~ fH/64 or fSUB  1：fH
#define SMOD_Default		0b11110011  

#define SETHXT()	{_cks2 = 1;_cks1 = 1;_cks0 = 1;_fsten = 1;_idlen = 1;_hlclk = 1;}
   
//#define SETHIRC_8MHZ()	{_fhs = 0;_hirc1 = 0;_hirc0 = 0;_hircen = 1;}
//#define SETHIRC_12MHZ()	{_fhs = 0;_hirc1 = 0;_hirc0 = 1;_hircen = 1;}
//#define SETHIRC_16MHZ()	{_fhs = 0;_hirc1 = 1;_hirc0 = 0;_hircen = 1;}


//					@-------------WDT config--------------@
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



//					@-------------LVR config--------------@
//  ______________________________________________________________________________
// | Bit  |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
//  ______________________________________________________________________________
// | Name |  LVS7  |  LVS6  |  LVS5  |  LVS4  |  LVS3  |  LVS2  |  LVS1  |  LVS0  |
// |______________________________________________________________________________
// | POR  |   0    |   1    |   0    |   1    |   0    |   1    |   0    |   1    |
// |_______________________________________________________________________________
// BIT 7~0  LVS7~LVS0:LVR電壓選擇 (01100110 is default)
// 			01010101:  1.9V     00110011:  2.55V
//			10011001:  3.15V    10101010:  3.8V
//          其他值: MCU復位 ( set 11110000 is disable)
//___________________________________________________________________
#define SETLVR_Voltage1_7()		{	_lvrc = 0B01100110 ;	}	//default on reset
#define SETLVR_Voltage1_9()		{	_lvrc = 0B01010101 ;	}
#define SETLVR_Voltage2_55()	{	_lvrc = 0B00110011 ;	}
#define SETLVR_Voltage3_15()	{	_lvrc = 0B10011001 ; 	}
#define SETLVR_Voltage3_8()		{	_lvrc = 0B10101010 ;	}
#define SETLVR_Disable()		{	_lvrc = 0B11110000 ;	}

//					@-------------EEPROM config--------------@
//Setting in EEPROM.h

//					@-------------IO config--------------@
//Setting in Target.h

//					@-------------Timer config-----------@
//Setting in Timer.h


//TMnC0 (PTM, n=0 or n=1) for HT66F317 & HT66F318
//                  @---------------PTMnC0---------------@
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
#define TM0C0_Default		0b01000000   // CLOCK  fsub
#define TM1C0_Default		0b01000000

//TMnC1 (PTM, n=0 or n=1) for HT66F317 HT66F318
//                  @--------------PTMnC1---------------@
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
#define TM0C1_Default		0x00
#define TM1C1_Default		0x00

// #define TM0AL_Default		0xfa	
// #define TM0AH_Default		0x0      // = 0.000008*250 = 2ms
// #define TM0AL_Default		0x47	
// #define TM0AH_Default		0x1      // = 0.000008*250 = 2ms
#define TM0AL_Default		0x48	
#define TM0AH_Default		0x1       	// =  = 10ms
#define TM1AL_Default		0x48	
#define TM1AH_Default		0x1       	// =  = 10ms

#define PTM0AL_Default		767%256	
#define PTM0AH_Default		767/256    
#define PTM1AL_Default		767%256	
#define PTM1AH_Default		767/256	
#define PTM0RP_Default		0			//8bit ????????
#define PTM1RPL_Default		0			//10 bit
#define PTM1RPH_Default		0


//TMnC0 (STM, n=0) only for HT66F318
//                  @---------------STMnC0---------------@
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
#define TM0C0_Default		0b01000000   // CLOCK  fsub

//TMnC1 (STM, n=0) only for HT66F318
//                  @--------------STMnC1---------------@
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
#define TM0C1_Default		0x00

#define STM0A_MAX			1023      	
#define STM0AL_Default		767%256	
#define STM0AH_Default		767/256     // 
#define STM0RP_Default		4       	// =


//TM2 (CTM) only for HT66F318
//                  @------------TM2C0 16bit CTM-----------@
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
#define TM2C0_Default		0x00

//                  @------------TM2C1 16bit CTM-----------@
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
#define TM2C1_Default		0x00

#define TM2RP_Default		0x00
#define	SETPTM2_10MS()		{ _tm2c0 = 0b01000000; _tm2c1 = 0xC1; _tm2al = 0x48; _tm2ah = 0x1;}
#define TM2AL_bat_60		580%256	
#define TM2AH_bat_60		580/256  
#define TM2AL_bat_58		630%256	
#define TM2AH_bat_58		630/256    
#define TM2AL_bat_56		680%256
#define TM2AH_bat_56		680/256    
#define TM2AL_bat_54		730%256	
#define TM2AH_bat_54		730/256      
#define TM2AL_bat_52		780%256	
#define TM2AH_bat_52		780/256   
#define TM2AL_bat_50		830%256	
#define TM2AH_bat_50		830/256    
#define TM2AL_bat_48		880%256	
#define TM2AH_bat_48		880/256      
#define TM2AL_bat_46		930%256	
#define TM2AH_bat_46		930/256   
#define TM2AL_bat_44		980%256	
#define TM2AH_bat_44		980/256  


//					@-------Internal Power config--------@
//Setting in Others file  when need


//					@------------ADC config--------------@


//                  @--------------TBC---------------@
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
// BIT 5~4  TB11~TB10:TimeBase1溢出週期
// 			00:  2^12/ftb   01:  2^13/ftb
//			10:  2^14/ftb   11:  2^15/ftb
// BIT 3  LXTLP:LXT低功耗控制位
// 			0:  快速啟動模式
//			1:  低功耗模式
// BIT 2~0  TB02~TB00：TimeBase0溢出週期
// 			000:  2^8/ftb    001:  2^9/ftb    010:  2^10/ftb
// 			011:  2^11/ftb   100:  2^12/ftb   101:  2^13/ftb
// 			110:  2^14/ftb   111:  2^15/ftb
#define TimeBase_Default 	0B10110111	//TimeBase1 0.5S   TimeBase 0  7.8ms



//					@------------ADC config--------------@
//Setting in ADC.h

//					@-------Temperature config-----------@
//Setting in Others file  when need

//					@-------------SIM config-------------@
//Setting in SIM.h

//					@-------------UART config-------------@
//Setting in UART.h

#endif
