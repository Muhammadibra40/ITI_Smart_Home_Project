#ifndef HELPER_H
#define HELPER_H

void HELPER_voidOptions(u8 Copy_u8RcvData, u8 *Copy_ptru8Room);
void HELPER_voidACOperation(u8 Copy_u8RcvData, u8 *Copy_ptru8Room,
							u8 *Copy_ptru8SetTemp, u16 Copy_u16ValueTemp);
void HELPER_voidBuzzerOperation(u16 Copy_u16ValueTemp);
void HELPER_voidLDROperation(u16 Copy_u16AnalogValueTorch);
void HELPER_voidUSOperation(u16 *Copy_u16TimerOverflow);

#endif
