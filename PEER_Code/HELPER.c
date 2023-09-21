#include "main.h"

void HELPER_voidOptions(u8 Copy_u8RcvData, u8 *Copy_ptru8Room)
{
    switch (Copy_u8RcvData)
    {
        case '1':
            *Copy_ptru8Room = 1;
            break;
        case '2':
            *Copy_ptru8Room = 2;
            break;
        case '3':
            *Copy_ptru8Room = 3;
            break;
        case '4': //AC
            *Copy_ptru8Room = 4;
            break;
        case '5':
            if(*Copy_ptru8Room == 1)
            {
                DIO_voidSetPinValue(DIO_PORTC, PIN0, DIO_HIGH);
            }
            else if(*Copy_ptru8Room == 2)
            {
                DIO_voidSetPinValue(DIO_PORTC, PIN1, DIO_HIGH);
            }
            else if(*Copy_ptru8Room == 3)
            {
                DIO_voidSetPinValue(DIO_PORTC, PIN2, DIO_HIGH);
            }
            break;
        case '6':
            if(*Copy_ptru8Room == 1)
            {
                DIO_voidSetPinValue(DIO_PORTC, PIN0, DIO_LOW);
            }
            else if(*Copy_ptru8Room == 2)
            {
                DIO_voidSetPinValue(DIO_PORTC, PIN1, DIO_LOW);
            }
            else if(*Copy_ptru8Room == 3)
            {
                DIO_voidSetPinValue(DIO_PORTC, PIN2, DIO_LOW);
            }
            break;
    }
}

void HELPER_voidACOperation(u8 Copy_u8RcvData, u8 *Copy_ptru8Room, u8 *Copy_ptru8SetTemp, u16 Copy_u16ValueTemp)
{
    if (Copy_u8RcvData < Copy_u16ValueTemp)
	{
		*Copy_ptru8SetTemp = Copy_u8RcvData;
		DIO_voidSetPinValue(DIO_PORTD, PIN2, DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTD, PIN2, DIO_LOW);
	}
	*Copy_ptru8Room = 0;
}

void HELPER_voidBuzzerOperation(u16 Copy_u16ValueTemp)
{
    if(Copy_u16ValueTemp > 50)
    {
        DIO_voidSetPinValue(DIO_PORTD, DIO_PIN3, DIO_HIGH);
    }
    else
    {
        DIO_voidSetPinValue(DIO_PORTD, DIO_PIN3, DIO_LOW);
    }
}

void HELPER_voidLDROperation(u16 Copy_u16AnalogValueTorch)
{
    if(Copy_u16AnalogValueTorch > 2000)
    {
        DIO_voidSetPinValue(DIO_PORTC, DIO_PIN4, DIO_HIGH);
    }
    else
    {
        DIO_voidSetPinValue(DIO_PORTC, DIO_PIN4, DIO_LOW);
    }
}

void HELPER_voidUSOperation(u16 *Copy_u16TimerOverflow)
{
	s32 HELPER_u32Count;
	f64 HELPER_f64Distance;

	/* Give 10us trigger pulse on trigger pin to HC-SR04 */
	DIO_voidSetPinValue(DIO_PORTD, Trigger_pin, DIO_HIGH);
	_delay_us(10);
	DIO_voidSetPinValue(DIO_PORTD, Trigger_pin, DIO_LOW);

	/* Clear Timer counter */
	TCNT1 = 0;

	/* Capture on rising edge, No prescaler*/
	TCCR1B = 0x41;

	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<ICF1;

	/* Clear Timer Overflow flag */
	TIFR = 1<<TOV1;

	/*Calculate width of Echo by Input Capture (ICP) */

	/* 1- Wait for rising edge */
	while ((TIFR & (1 << ICF1)) == 0);

	/* 2- Clear Timer counter */
	TCNT1 = 0;

	/* 3- Capture on falling edge, No prescaler */
	TCCR1B = 0x01;

	/* 4- Clear ICP flag (Input Capture flag) */
	TIFR = 1<<ICF1;

	/* 5- Clear Timer Overflow flag */
	TIFR = 1<<TOV1;

	/* 6- Clear Timer overflow count */
	(*Copy_u16TimerOverflow) = 0;

	while ((TIFR & (1 << ICF1)) == 0);/* Wait for falling edge */
	HELPER_u32Count = ICR1 + (65535 * (*Copy_u16TimerOverflow));	/* Take count /   /((2 to the power 16)-1) from 0 to 65535 16-bit register*/
	/* 8MHz Timer freq, sound speed =343 m/s */
	HELPER_f64Distance = (f64)HELPER_u32Count / 466.47;

	if (HELPER_f64Distance>=80)
	{
		DIO_voidSetPinValue(DIO_PORTA, DIO_PIN3, DIO_LOW);
		_delay_ms(500);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA, DIO_PIN3, DIO_HIGH);
		_delay_ms(500);
	}
}
