/*
 * SRAM_init.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */

#ifndef SRAM_INIT_H_
#define SRAM_INIT_H_

#define WE_CTR_PORT PORT_D
#define WE_CTR_PIN  PIN_1
#define OE_CTR_PORT PORT_D
#define OE_CTR_PIN PIN_0

#define LOW_BYTE_ADDRESS_PORT   PORT_C
#define LOW_NIBBLE_ADDRESS_PORT PORT_D
#define HIGH_NIBBLE_ADDRESS_PORT PORT_A
#define SRAM_DATA_PORT PORT_B

extern u16 Address;

u16 SRAM_u16WriteData(u8 u8DataCPY);
u16 SRAM_u16WriteByteData(u16 u16AdressCPY,u8 u8DataCPY);
u8  SRAM_u8ReadData(void);
u8 SRAM_u8ReadByteData(u16 u16AdressCPY);





#endif /* SRAM_INIT_H_ */
