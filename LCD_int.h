/*
 * LCD_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_
#define _4BIT 0
#define _8BIT 1
/////////////////////////////////
#define LCD_MODE _4BIT
#define LCD_PORT PORT_C
#define LCD_CONTROL_PORT PORT_C
#define RS 1
#define RW 2
#define E 3
#define D7_PIN 7
#define D6_PIN 6
#define D5_PIN 5
#define D4_PIN 4
////////////////////////////////

////////////////////////////////
#if LCD_MODE == _8BIT
#define EM_INCREASE_ADD 0b00000110  //no shift
#define EM_DECREASE_ADD 0b00000100  //no shift
#define EM_SHIFTDISPLAY_RIGH  0b00000101
#define EM_SHIFTDISPLAY_LEFT  0b00000111
void LCD_vidIntialize8Bit(void);
void LCD_vidSendCommand(u8 u8CommandCPY);
void LCD_vidSendData(u8 u8DataCPY);
void LCD_vidClear_Display(void);
void LCD_vidReturn_home(void);
void LCD_vidSendString(u8 *u8StringCPY);
void LCD_vidSendNumber(u64 u8VariableCPY );
void LCD_vidGotoxy (u8 u8ROWCPY,u8 u8COLCPY);
u8   LCD_u8CheckBusy(void);
u8   LCD_u8ReadAC(void);
void LCD_vidEntryModeSet(u8 u8EnteryModeCPY);
void LCD_vidSetCGRAMAddress(u8 u8AddressCPY);
void LCD_vidSetDDRAMAddress(u8 u8AddressCPY);
void LCD_vidSetCustomChar(void);
#else
#define DISPLAY_OFF_CURSOR_OFF 0x08
#define DISPLAY_ON_CURSOR_ON 0x0E
#define DISPLAY_ON_CURSOR_OFF 0x0C
#define DISPLAY_ON_CURSOR_BLINK 0x0F
void LCD_vidSendCommand4Bit(u8 u8CommandCPY);
void LCD_vidIntialize4Bit(void);
void LCD_vidSendData4Bit(u8 u8DataCPY);
void LCD_vidClear_Display4Bit(void);
void LCD_vidReturn_home4Bit(void);
void LCD_vidSendString4Bit(u8* u8StringPtrCPY) ;//take address value of the string in pointer *str
void LCD_vidSendNumber4Bit(u32 u32NumberCPY);
void LCD_vidSetDisply_Cursor4Bit(u8 u8CommandCPY);
#endif









#endif /* LCD_INT_H_ */
